/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/workqueue.h>
#include <linux/power_supply.h>
#if (CONFIG_MTK_GAUGE_VERSION == 30)
#include <mt-plat/charger_type.h>
#include <mt-plat/mtk_charger.h>
#include <mt-plat/mtk_battery.h>
#else
#include <tmp_battery.h>
#include <charging.h>
#endif

#include <linux/pm_wakeup.h>

#if (CONFIG_MTK_GAUGE_VERSION == 30)
static struct charger_consumer *pogo_consumer;
#endif

#ifdef CONFIG_TCPC_CLASS
#define POGO_IRQ_WAKE_TIME 500 //ms
#define FORCE_DETECT_POGO
#endif

#ifdef FORCE_DETECT_POGO
static struct work_struct chr_work;
#endif

struct pogo_charger_info {
	struct device *dev;
	struct mutex gpio_access_lock;
	atomic_t is_chip_en;
	atomic_t is_otg_en;
	atomic_t is_wrx_en;
	int otg_gpio;
	int en_gpio;
	int wrx_gpio;
	int pogo_intr_0;
	int pogo_intr_1;
	int irq;
	int irq_pogo0;
	int irq_pogo1;
	struct delayed_work work;
	struct power_supply_desc pogo_desc;
	struct power_supply_config pogo_cfg;
	struct power_supply *pogo_psy;
#ifdef CONFIG_TCPC_CLASS
	struct semaphore suspend_lock;
	struct wakeup_source pogo_wake_lock;
#endif
};

struct pogo_charger_info *g_ri;

unsigned int wrx_on_delay  =  10;
unsigned int wrx_off_delay = 310;
unsigned int otg_on_delay  = 130;
unsigned int otg_off_delay = 0;

int pogo_enable_otg(bool en);
int pogo_enable_chip(bool en);
int pogo_enable_wrx(bool en);
static bool is_lenovo_anna(void);
/* otg_off_delay */
static ssize_t show_otg_off_delay(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    pr_info("otg_off_delay = %d\n", otg_off_delay);
    return sprintf(buf, "%u\n", otg_off_delay);
}

static ssize_t store_otg_off_delay(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    int rv;

    rv = kstrtouint(buf, 0, &otg_off_delay);
    if (rv != 0)
        return -EINVAL;
    pr_info("otg_off_delay = %d\n", otg_off_delay);
    return size;
}

static DEVICE_ATTR(otg_off_delay, 0664, show_otg_off_delay, store_otg_off_delay);

/* otg_on_delay */
static ssize_t show_otg_on_delay(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    pr_info("otg_on_delay = %d\n", otg_on_delay);
    return sprintf(buf, "%u\n", otg_on_delay);
}

static ssize_t store_otg_on_delay(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    int rv;

    rv = kstrtouint(buf, 0, &otg_on_delay);
    if (rv != 0)
        return -EINVAL;
    pr_info("otg_on_delay = %d\n", otg_on_delay);
    return size;
}

static DEVICE_ATTR(otg_on_delay, 0664, show_otg_on_delay, store_otg_on_delay);

/* wrx_off_delay */
static ssize_t show_wrx_off_delay(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    pr_info("wrx_off_delay = %d\n", wrx_off_delay);
    return sprintf(buf, "%u\n", wrx_off_delay);
}

static ssize_t store_wrx_off_delay(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    int rv;

    rv = kstrtouint(buf, 0, &wrx_off_delay);
    if (rv != 0)
        return -EINVAL;
    pr_info("wrx_off_delay = %d\n", wrx_off_delay);
    return size;
}

static DEVICE_ATTR(wrx_off_delay, 0664, show_wrx_off_delay, store_wrx_off_delay);

/* wrx_on_delay */
static ssize_t show_wrx_on_delay(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    pr_info("wrx_on_delay = %d\n", wrx_on_delay);
    return sprintf(buf, "%u\n", wrx_on_delay);
}

static ssize_t store_wrx_on_delay(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    int rv;

    rv = kstrtouint(buf, 0, &wrx_on_delay);
    if (rv != 0)
        return -EINVAL;
    pr_info("wrx_on_delay = %d\n", wrx_on_delay);
    return size;
}

static DEVICE_ATTR(wrx_on_delay, 0664, show_wrx_on_delay, store_wrx_on_delay);

static inline bool __pogo_is_otg_en(struct pogo_charger_info *info)
{
	int en = 0;

	en = gpio_get_value(info->otg_gpio);
	if ((en && !atomic_read(&info->is_otg_en)) ||
			(!en && atomic_read(&info->is_otg_en)))
		dev_err(info->dev, "%s: en not sync(%d, %d)\n", __func__, en,
				atomic_read(&info->is_otg_en));

	return en;
}

static int __pogo_enable_wrx(struct pogo_charger_info *info, bool en)
{
	dev_info(info->dev, "%s: en = %d\n", __func__, en);

	mutex_lock(&info->gpio_access_lock);

	gpio_set_value(info->wrx_gpio, en);
	atomic_set(&info->is_wrx_en, en);
	dev_err(info->dev, "%s: set wrx %d\n", __func__, en);

	mutex_unlock(&info->gpio_access_lock);
	return 0;
}

static int __pogo_enable_otg(struct pogo_charger_info *info, bool en)
{
	bool is_otg_en = false;
	dev_info(info->dev, "%s: en = %d\n", __func__, en);

	mutex_lock(&info->gpio_access_lock);

	is_otg_en = __pogo_is_otg_en(info);
	if (en && !is_otg_en) {
		gpio_set_value(info->otg_gpio, 1);
		dev_err(info->dev, "%s: set gpio high\n", __func__);
	} else if (!en && is_otg_en) {
		gpio_set_value(info->otg_gpio, 0);
		dev_err(info->dev, "%s: set gpio low\n", __func__);
	}
	atomic_set(&info->is_otg_en, en);

	mutex_unlock(&info->gpio_access_lock);
	return 0;
}

static inline bool __pogo_is_chip_en(struct pogo_charger_info *info)
{
	int en = 0;

	en = gpio_get_value(info->en_gpio);
	if ((en && !atomic_read(&info->is_chip_en)) ||
			(!en && atomic_read(&info->is_chip_en)))
		dev_err(info->dev, "%s: en not sync(%d, %d)\n", __func__, en,
				atomic_read(&info->is_chip_en));

	return en;
}

static int __pogo_enable_chip(struct pogo_charger_info *info, bool en)
{
	bool is_chip_en = false;
	dev_info(info->dev, "%s: en = %d\n", __func__, en);

	mutex_lock(&info->gpio_access_lock);

	is_chip_en = __pogo_is_chip_en(info);
	if (en && !is_chip_en) {
		gpio_set_value(info->en_gpio, 1);
		dev_info(info->dev, "%s: set gpio high\n", __func__);
	} else if (!en && is_chip_en) {
		gpio_set_value(info->en_gpio, 0);
		dev_info(info->dev, "%s: set gpio low\n", __func__);
	}
	atomic_set(&info->is_chip_en, en);

	mutex_unlock(&info->gpio_access_lock);
	return 0;
}

int pogo_enable_otg(bool en)
{
	struct pogo_charger_info *info = g_ri;

	if(!is_lenovo_anna()){
		return 0;	
	}
	__pogo_enable_otg(info, en);

	return 0;
}

int pogo_enable_chip(bool en)
{
	struct pogo_charger_info *info = g_ri;
	
	if(!is_lenovo_anna()){
		return 0;	
	}

	__pogo_enable_chip(info, en);

	return 0;
}

int pogo_enable_wrx(bool en)
{
	struct pogo_charger_info *info = g_ri;

	if(!is_lenovo_anna()){
		return 0;	
	}

   	 __pogo_enable_wrx(info, en);

    return 0;
}

int pogo_get_state(void)
{
	if(!is_lenovo_anna()){
		return -1;	
	}

	return (gpio_get_value(g_ri->pogo_intr_0) |
		(gpio_get_value(g_ri->pogo_intr_1) << 1));
}

static enum power_supply_property mt_pogo_properties[] = {
	POWER_SUPPLY_PROP_ONLINE,
};

static int mt_pogo_get_property(struct power_supply *psy,
	enum power_supply_property psp, union power_supply_propval *val)
{
	struct pogo_charger_info *info = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = 1;
		if (gpio_get_value(info->pogo_intr_0))
			val->intval = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static void pogo_work(struct work_struct *work)
{
	int pogo_in_0, pogo_in_1;
	struct pogo_charger_info *info =
		container_of(work, struct pogo_charger_info, work.work);
#ifdef CONFIG_TCPC_CLASS
	down(&info->suspend_lock);
#endif
	dev_info(info->dev, "%s\n", __func__);

	pogo_in_1 = gpio_get_value(info->pogo_intr_1);
	pogo_in_0 = gpio_get_value(info->pogo_intr_0);

	if (info->irq == info->irq_pogo0) {
		dev_info(info->dev, "%s: intr gpio %d value = %d  vbus = %d\n",
				__func__, info->pogo_intr_0, pogo_in_0, battery_get_vbus());
		//chr type dect has been done in pmic interrupt
		//if (pogo_in_1 == 1 &&  pogo_in_0 == 0)
		//	mtk_pmic_enable_chr_type_det(1);
#ifdef CONFIG_TCPC_CLASS
                if (pogo_in_1 == 1 && pogo_in_0 == 0)
                        mtk_pmic_set_charger_type_by_pogo(1);
		if (pogo_in_0 == 1 && mt_get_charger_type() == POGO_CHARGER)
			mtk_pmic_set_charger_type_by_pogo(0);
#endif /*CONFIG_TCPC_CLASS*/

		if(info->pogo_psy)
			power_supply_changed(info->pogo_psy);
	}
	else if (info->irq == info->irq_pogo1) {
		dev_info(info->dev, "%s: intr gpio %d value = %d\n",
				__func__, info->pogo_intr_1, pogo_in_1);
#ifndef CONFIG_TCPC_CLASS	
		if (pogo_in_1 == 0 &&  pogo_in_0 == 0)
			mtk_pmic_enable_chr_type_det(1);
#else
                if (pogo_in_1 == 0 &&  pogo_in_0 == 0 && !mt_usb_is_device())
			mtk_pmic_set_charger_type_by_pogo(0);

                if (pogo_in_1 == 1 && pogo_in_0 == 0)
                         mtk_pmic_set_charger_type_by_pogo(1);
#endif /*CONFIG_TCPC_CLASS*/

                if(info->pogo_psy)
                        power_supply_changed(info->pogo_psy);

	}
#ifdef CONFIG_TCPC_CLASS
	up(&info->suspend_lock);
#endif
}

irqreturn_t pogo_irq_handler(int irq, void *data)
{
	struct pogo_charger_info *info = (struct pogo_charger_info *)data;

	dev_dbg(info->dev, "%s\n", __func__);

#ifdef CONFIG_TCPC_CLASS
        __pm_wakeup_event(&info->pogo_wake_lock, POGO_IRQ_WAKE_TIME);
#endif
	info->irq = irq;
	schedule_delayed_work(&info->work, HZ/10);

	return IRQ_HANDLED;
}

static int pogo_parse_dt(struct pogo_charger_info *info, struct device *dev)
{
	int ret = 0;
	struct device_node *np = dev->of_node;

	ret = of_get_named_gpio(np, "pogo,en_gpio", 0);
	if (ret < 0)
		return ret;
	info->en_gpio = ret;
	gpio_request(info->en_gpio, "en_pin");
	gpio_direction_output(info->en_gpio, 0);
	pr_info("[%s]%d en_gpio = 0x%x\n", __func__, __LINE__, info->en_gpio);

	ret = of_get_named_gpio(np, "pogo,otg_gpio", 0);
	if (ret < 0)
		return ret;
	info->otg_gpio = ret;
	gpio_request(info->otg_gpio, "otg_pin");
	gpio_direction_output(info->otg_gpio, 1);
	dev_info(info->dev, "%s: otg gpio = %d\n", __func__, info->otg_gpio);
#ifndef CONFIG_TCPC_CLASS 
	ret = of_get_named_gpio(np, "pogo,wrx_gpio", 0);
#else
	ret = of_get_named_gpio(np, "pogo,wrx_gpio_na", 0);
#endif
	if (ret < 0)
		return ret;
	info->wrx_gpio = ret;
	gpio_request(info->wrx_gpio, "wrx_pin");
	gpio_direction_output(info->wrx_gpio, 0);
	pr_info("[%s]%d wrx_gpio = 0x%x\n", __func__, __LINE__, info->wrx_gpio);

	ret = of_get_named_gpio(np, "pogo,intr_pogo_0", 0);
	if (ret < 0)
		return ret;
	info->pogo_intr_0 = ret;
	gpio_request(info->pogo_intr_0, "intr_pin_0");
	gpio_direction_input(info->pogo_intr_0);
	pr_info("[%s]%d intr_pin_0 = 0x%x\n", __func__, __LINE__, info->pogo_intr_0);

	ret = of_get_named_gpio(np, "pogo,intr_pogo_1", 0);
	if (ret < 0)
		return ret;
	info->pogo_intr_1 = ret;
	gpio_request(info->pogo_intr_1, "intr_pin_0");
	gpio_direction_input(info->pogo_intr_1);
	pr_info("[%s]%d intr_pin_1 = 0x%x\n", __func__, __LINE__, info->pogo_intr_1);

	return 0;
}

static char get_board[10];
static int get_board_id(void)
{
	char* s1= "";

	s1 = strstr(saved_command_line, "board_id=");
	if(!s1) {
		pr_info("hw_id not found in cmdline\n");
		return -1;
	}
	s1 += strlen("board_id=");
	strncpy(get_board, s1, 4);
	get_board[4]='\0';
	pr_info("board_id found in cmdline : %s\n", get_board);

	return 0;
}

static bool is_lenovo_anna(void)
{
	if (!strcmp(get_board, "Anna")){
		pr_info("anan enable pogo\n");
		return 1;	
	}else{
		pr_info("not anan disable pogo\n");
		return 0;
	}	
}

#ifdef FORCE_DETECT_POGO
static void do_pogo_detection_work(struct work_struct *data)
{
	int pogo_in_0, pogo_in_1;
	struct pogo_charger_info *info = g_ri;

        pogo_in_1 = gpio_get_value(info->pogo_intr_1);
        pogo_in_0 = gpio_get_value(info->pogo_intr_0);

	pr_info("%s pogo_in_0:%d pogo_in_1:%d\n", __func__, pogo_in_0, pogo_in_1);
        if(pogo_in_1 == 1 && pogo_in_0 == 0)
                mtk_pmic_enable_chr_type_det(1);

        if(info->pogo_psy)
                power_supply_changed(info->pogo_psy);

}
#endif

static int pogo_charger_probe(struct platform_device *pdev)
{
	int ret = 0;
	int ret_device_file = 0;
	unsigned long flags;
	struct pogo_charger_info *info = NULL;

	pr_info("[%s]\n", __func__);

	get_board_id();
	if(!is_lenovo_anna()){
		return 0;	
	}

	info = devm_kzalloc(&pdev->dev, sizeof(struct pogo_charger_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;
	ret = pogo_parse_dt(info, &pdev->dev);
	if (ret < 0)
		return ret;

	g_ri = info;
	mutex_init(&info->gpio_access_lock);
	atomic_set(&info->is_chip_en, 0);
	atomic_set(&info->is_otg_en, 0);
	atomic_set(&info->is_wrx_en, 0);
#ifdef CONFIG_TCPC_CLASS
	sema_init(&info->suspend_lock, 1);
	wakeup_source_init(&info->pogo_wake_lock, "pogo_irq_wakelock");
	platform_set_drvdata(pdev, info);
#endif

	INIT_DELAYED_WORK(&info->work, pogo_work);

	flags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT;

	info->irq_pogo0 = gpio_to_irq(info->pogo_intr_0);
	ret = devm_request_irq(info->dev,info->irq_pogo0,
					pogo_irq_handler, flags,
					"pogo_irq0", info);
	if (ret < 0) {
		dev_err(info->dev, "Failed to request irq0 %d\n", ret);
		return ret;
	}

	info->irq_pogo1 = gpio_to_irq(info->pogo_intr_1);
	ret = devm_request_irq(info->dev, info->irq_pogo1,
					pogo_irq_handler, flags,
					"pogo_irq1", info);
	if (ret < 0) {
		dev_err(info->dev, "Failed to request irq1: %d\n", ret);
		return ret;
	}

	__pogo_enable_chip(info, 0);
	__pogo_enable_otg(info, 0);
	__pogo_enable_wrx(info, 0);

	pogo_consumer = charger_manager_get_by_name(&pdev->dev, "charger");

	info->pogo_desc.name = "pogo";
	info->pogo_desc.type = POWER_SUPPLY_TYPE_MAINS;
	info->pogo_desc.properties = mt_pogo_properties;
	info->pogo_desc.num_properties = ARRAY_SIZE(mt_pogo_properties);
	info->pogo_desc.get_property = mt_pogo_get_property;
	info->pogo_cfg.drv_data = info;

	info->pogo_psy = power_supply_register(&pdev->dev, &info->pogo_desc,
		&info->pogo_cfg);

#ifdef FORCE_DETECT_POGO
        /* do charger detect here to prevent HW miss interrupt*/
        INIT_WORK(&chr_work, do_pogo_detection_work);
        schedule_work(&chr_work);
#endif

	pr_info("[%s] check pogo status: %d \n", __func__, pogo_get_state());

	ret_device_file = device_create_file(&(pdev->dev), &dev_attr_wrx_on_delay);
	ret_device_file = device_create_file(&(pdev->dev), &dev_attr_wrx_off_delay);
	ret_device_file = device_create_file(&(pdev->dev), &dev_attr_otg_on_delay);
	ret_device_file = device_create_file(&(pdev->dev), &dev_attr_otg_off_delay);	
	return 0;
}

#ifdef CONFIG_TCPC_CLASS
static int pogo_charger_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct pogo_charger_info *info = platform_get_drvdata(pdev);

	pr_info("pogo_charger_suspend\n");
	if(!IS_ERR_OR_NULL(info))
		down(&info->suspend_lock);
	return 0;
}

static int pogo_charger_resume(struct platform_device *pdev)
{
        struct pogo_charger_info *info = platform_get_drvdata(pdev);

	pr_info("pogo_charger_resume\n");
        if(!IS_ERR_OR_NULL(info))
                up(&info->suspend_lock);
        return 0;
}
#endif

static int pogo_charger_remove(struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id pogo_charger_match[] = {
	{ .compatible = "mediatek,pogo-charger" },
	{ }
};
MODULE_DEVICE_TABLE(of, pogo_charger_match);

static struct platform_driver pogo_charger_driver = {
	.probe = pogo_charger_probe,
	.remove = pogo_charger_remove,
#ifdef CONFIG_TCPC_CLASS
	.suspend = pogo_charger_suspend,
	.resume = pogo_charger_resume,
#endif
	.driver = {
		.name = "pogo-charger",
		.of_match_table = pogo_charger_match,
	},
};

module_platform_driver(pogo_charger_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wentao.he <wentao.he@mediatek.com>");
MODULE_DESCRIPTION("POGO_Pin Charger Driver");
