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

#include <linux/delay.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/power_supply.h>
#include <linux/reboot.h>
#include <linux/workqueue.h>

#include <mt-plat/charger_type.h>
#include <mt-plat/mtk_boot.h>
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>

#ifdef CONFIG_MTK_USB2JTAG_SUPPORT
#include <mt-plat/mtk_usb2jtag.h>
#endif

/* #define __FORCE_USB_TYPE__ */
#ifndef CONFIG_TCPC_CLASS
#define __SW_CHRDET_IN_PROBE_PHASE__
#endif

static enum charger_type g_chr_type;
static bool thub_connect_ta = false;
#ifdef __SW_CHRDET_IN_PROBE_PHASE__
static struct work_struct chr_work;
#endif
static DEFINE_MUTEX(chrdet_lock);
static struct power_supply *chrdet_psy;

#if !defined(CONFIG_FPGA_EARLY_PORTING)
static bool first_connect = true;
#endif

#ifdef CONFIG_POGO_CHARGER
extern int pogo_get_state(void);
#endif

typedef enum {
   ACA_UNKNOWN = 0,
   ACA_DOCK, //has external power source
   ACA_A,     //B device on accessory port
   ACA_B,     //only for charging
   ACA_C,    // A device on accessory port
   ACA_UNCONFIG = 0x8, // Unconfig State
} ACA_TYPE;

extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata);
extern int IMM_IsAdcInitReady(void);

#define voltage_threshold 850//mv
#define voltage_otg 200

static int g_aca_detection = 0xF;

#ifdef CONFIG_TCPC_CLASS
bool ignore_usb_check = 0;
#endif

void hw_otg_reset_aca_type(void)
{
	g_aca_detection = 0xF;
	pr_debug("%s!\n", __func__);
}

int hw_otg_get_aca_type_detection(void)
{
	int ADC_voltage, data[4], i, ret_value = 0;
	int times=1, IDDIG_CHANNEL_NUM = 3; //(AUXIN3)
	if( IMM_IsAdcInitReady() == 0 )
	{
		pr_err("[%s]: AUXADC is not ready\n", __func__);
		return ACA_UNCONFIG;
	}

	i = times;
	while (i--)
	{
		ret_value = IMM_GetOneChannelValue(IDDIG_CHANNEL_NUM, data, &ADC_voltage);
		ADC_voltage = ADC_voltage * 1500 / 4096;
		if (ret_value == -1) // AUXADC is busy
		{
			pr_err("IMM_GetOneChannelValue wrong, AUXADC is busy");
			ADC_voltage = 0;
		}
		pr_debug("[%s]: AUXADC Channel %d, ADC_voltage %d\n, voltage_threshold %d",
				__func__, IDDIG_CHANNEL_NUM, ADC_voltage, voltage_threshold);
	}

	if (ADC_voltage > voltage_threshold)
		return ACA_UNCONFIG;
	else if (ADC_voltage < voltage_threshold && ADC_voltage > voltage_otg)
		return ACA_C;
	else
		return ACA_UNKNOWN;
}

int hw_otg_get_aca_type(void)
{
 	/* need otg type detection */
	if(0xF == g_aca_detection)
		g_aca_detection = hw_otg_get_aca_type_detection();

	return g_aca_detection;
}


static int chrdet_inform_psy_changed(enum charger_type chg_type,
				bool chg_online)
{
	int ret = 0;
	union power_supply_propval propval;

	pr_info("charger type: %s: online = %d, type = %d\n", __func__,
		chg_online, chg_type);

	/* Inform chg det power supply */
	if (chg_online) {
		propval.intval = chg_online;
		ret = power_supply_set_property(chrdet_psy,
				POWER_SUPPLY_PROP_ONLINE, &propval);
		if (ret < 0)
			pr_notice("%s: psy online failed, ret = %d\n",
				__func__, ret);

		propval.intval = chg_type;
		ret = power_supply_set_property(chrdet_psy,
				POWER_SUPPLY_PROP_CHARGE_TYPE, &propval);
		if (ret < 0)
			pr_notice("%s: psy type failed, ret = %d\n",
				__func__, ret);

		return ret;
	}

	propval.intval = chg_type;
	ret = power_supply_set_property(chrdet_psy,
				POWER_SUPPLY_PROP_CHARGE_TYPE, &propval);
	if (ret < 0)
		pr_notice("%s: psy type failed, ret(%d)\n", __func__, ret);

	propval.intval = chg_online;
	ret = power_supply_set_property(chrdet_psy, POWER_SUPPLY_PROP_ONLINE,
				&propval);
	if (ret < 0)
		pr_notice("%s: psy online failed, ret(%d)\n", __func__, ret);
	return ret;
}

#if defined(CONFIG_FPGA_EARLY_PORTING)
/* FPGA */
int hw_charging_get_charger_type(void)
{
	/* Force Standard USB Host */
	g_chr_type = STANDARD_HOST;
	chrdet_inform_psy_changed(g_chr_type, 1);
	return g_chr_type;
}

#else
/* EVB / Phone */
static void hw_bc11_init(void)
{
	int timeout = 200;

	msleep(200);

	if (first_connect == true) {
		/* add make sure USB Ready */
		if (is_usb_rdy() == false) {
			pr_info("CDP, block\n");
			while (is_usb_rdy() == false && timeout > 0) {
				msleep(100);
				timeout--;
			}
			if (timeout == 0)
				pr_info("CDP, timeout\n");
			else
				pr_info("CDP, free\n");
		} else
			pr_info("CDP, PASS\n");
		first_connect = false;
	}

	/* RG_bc11_BIAS_EN=1 */
	bc11_set_register_value(PMIC_RG_BC11_BIAS_EN, 1);
	/* RG_bc11_VSRC_EN[1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0);
	/* RG_bc11_VREF_VTH = [1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0);
	/* RG_bc11_CMP_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0);
	/* RG_bc11_IPU_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPU_EN, 0);
	/* RG_bc11_IPD_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0);
	/* bc11_RST=1 */
	bc11_set_register_value(PMIC_RG_BC11_RST, 1);
	/* bc11_BB_CTRL=1 */
	bc11_set_register_value(PMIC_RG_BC11_BB_CTRL, 1);
	/* add pull down to prevent PMIC leakage */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x1);
	msleep(50);

	Charger_Detect_Init();
}

static unsigned int hw_bc11_DCD(void)
{
	unsigned int wChargerAvail = 0;
	/* RG_bc11_IPU_EN[1.0] = 10 */
	bc11_set_register_value(PMIC_RG_BC11_IPU_EN, 0x2);
	/* RG_bc11_IPD_EN[1.0] = 01 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x1);
	/* RG_bc11_VREF_VTH = [1:0]=01 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x1);
	/* RG_bc11_CMP_EN[1.0] = 10 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x2);
	msleep(80);
	/* mdelay(80); */
	wChargerAvail = bc11_get_register_value(PMIC_RGS_BC11_CMP_OUT);

	/* RG_bc11_IPU_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPU_EN, 0x0);
	/* RG_bc11_IPD_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x0);
	/* RG_bc11_VREF_VTH = [1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x0);
	return wChargerAvail;
}

static unsigned int hw_bc11_stepA1(void)
{
	unsigned int wChargerAvail = 0;
	/* RG_bc11_IPD_EN[1.0] = 01 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x1);
	/* RG_bc11_VREF_VTH = [1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 01 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x1);
	msleep(80);
	/* mdelay(80); */
	wChargerAvail = bc11_get_register_value(PMIC_RGS_BC11_CMP_OUT);

	/* RG_bc11_IPD_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x0);
	return wChargerAvail;
}

static unsigned int hw_bc11_stepA2(void)
{
	unsigned int wChargerAvail = 0;
	/* RG_bc11_VSRC_EN[1.0] = 10 */
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x2);
	/* RG_bc11_IPD_EN[1:0] = 01 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x1);
	/* RG_bc11_VREF_VTH = [1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 01 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x1);
	msleep(80);
	/* mdelay(80); */
	wChargerAvail = bc11_get_register_value(PMIC_RGS_BC11_CMP_OUT);

	/* RG_bc11_VSRC_EN[1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x0);
	/* RG_bc11_IPD_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x0);
	return wChargerAvail;
}

static unsigned int hw_bc11_stepB2(void)
{
	unsigned int wChargerAvail = 0;

	/*enable the voltage source to DM*/
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x1);
	/* enable the pull-down current to DP */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x2);
	/* VREF threshold voltage for comparator  =0.325V */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x0);
	/* enable the comparator to DP */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x2);
	msleep(80);
	wChargerAvail = bc11_get_register_value(PMIC_RGS_BC11_CMP_OUT);
	/*reset to default value*/
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x0);
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x0);
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x0);
	if (wChargerAvail == 1) {
		bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x2);
		pr_info("charger type: DCP, keep DM voltage source in stepB2\n");
	}
	return wChargerAvail;

}

static void hw_bc11_done(void)
{
	/* RG_bc11_VSRC_EN[1:0]=00 */
	bc11_set_register_value(PMIC_RG_BC11_VSRC_EN, 0x0);
	/* RG_bc11_VREF_VTH = [1:0]=0 */
	bc11_set_register_value(PMIC_RG_BC11_VREF_VTH, 0x0);
	/* RG_bc11_CMP_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_CMP_EN, 0x0);
	/* RG_bc11_IPU_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPU_EN, 0x0);
	/* RG_bc11_IPD_EN[1.0] = 00 */
	bc11_set_register_value(PMIC_RG_BC11_IPD_EN, 0x0);
	/* RG_bc11_BIAS_EN=0 */
	bc11_set_register_value(PMIC_RG_BC11_BIAS_EN, 0x0);
	Charger_Detect_Release();
}

static void dump_charger_name(enum charger_type type)
{
	switch (type) {
	case CHARGER_UNKNOWN:
		pr_info("charger type: %d, CHARGER_UNKNOWN\n", type);
		break;
	case STANDARD_HOST:
		pr_info("charger type: %d, Standard USB Host\n", type);
		break;
	case CHARGING_HOST:
		pr_info("charger type: %d, Charging USB Host\n", type);
		break;
	case NONSTANDARD_CHARGER:
		pr_info("charger type: %d, Non-standard Charger\n", type);
		break;
	case STANDARD_CHARGER:
		pr_info("charger type: %d, Standard Charger\n", type);
		break;
	case APPLE_2_1A_CHARGER:
		pr_info("charger type: %d, APPLE_2_1A_CHARGER\n", type);
		break;
	case APPLE_1_0A_CHARGER:
		pr_info("charger type: %d, APPLE_1_0A_CHARGER\n", type);
		break;
	case APPLE_0_5A_CHARGER:
		pr_info("charger type: %d, APPLE_0_5A_CHARGER\n", type);
		break;
	case POGO_CHARGER:
		pr_info("charger type: %d, Pogo Charger\n", type);
		break;
	default:
		pr_info("charger type: %d, Not Defined!!!\n", type);
		break;
	}
}

int hw_charging_get_charger_type(void)
{
	enum charger_type CHR_Type_num = CHARGER_UNKNOWN;

#ifdef CONFIG_MTK_USB2JTAG_SUPPORT
	if (usb2jtag_mode()) {
		pr_info("[USB2JTAG] in usb2jtag mode, skip charger detection\n");
		return STANDARD_HOST;
	}
#endif

	hw_bc11_init();

	if (hw_bc11_DCD()) {
		if (hw_bc11_stepA1())
			CHR_Type_num = APPLE_2_1A_CHARGER;
		else
			CHR_Type_num = NONSTANDARD_CHARGER;
	} else {
		if (hw_bc11_stepA2()) {
			if (hw_bc11_stepB2())
				CHR_Type_num = STANDARD_CHARGER;
			else
				CHR_Type_num = CHARGING_HOST;
		} else
			CHR_Type_num = STANDARD_HOST;
	}

	if (CHR_Type_num != STANDARD_CHARGER)
		hw_bc11_done();
	else
		pr_info("charger type: skip bc11 release for BC12 DCP SPEC\n");

	dump_charger_name(CHR_Type_num);


#ifdef __FORCE_USB_TYPE__
	CHR_Type_num = STANDARD_HOST;
	pr_info("charger type: Froce to STANDARD_HOST\n");
#endif

	return CHR_Type_num;
}

#ifdef CONFIG_TCPC_CLASS
void mtk_pmic_set_charger_type_by_pogo(bool en)
{
		mutex_lock(&chrdet_lock);

		if(en){
			g_chr_type = POGO_CHARGER;
			chrdet_inform_psy_changed(g_chr_type, 1);
		}else{
			g_chr_type = CHARGER_UNKNOWN;
			chrdet_inform_psy_changed(g_chr_type, 0);
		}

				mutex_unlock(&chrdet_lock);
}
#endif

void mtk_pmic_set_charger_type_by_thub(bool en)
{
	if(en){
		g_chr_type = STANDARD_CHARGER;
		thub_connect_ta = true;
		chrdet_inform_psy_changed(g_chr_type, 1);
        }else{
		thub_connect_ta = false;		
		chrdet_inform_psy_changed(g_chr_type, 0); 
	}
}

void mtk_pmic_enable_chr_type_det(bool en)
{
	int boot_mode = 0;
	int detect_times=3;
	
#ifndef CONFIG_TCPC_CLASS
	int i_ACA_type = 0;
#endif
	if (!mt_usb_is_device()) {
		g_chr_type = CHARGER_UNKNOWN;
		pr_info("charger type: UNKNOWN, Now is usb host mode. Skip detection\n");
		return;
	}

	mutex_lock(&chrdet_lock);

	if (en) {
		if (is_meta_mode()) {
			/* Skip charger type detection to speed up meta boot */
			pr_notice("charger type: force Standard USB Host in meta\n");
			g_chr_type = STANDARD_HOST;
			chrdet_inform_psy_changed(g_chr_type, 1);
		} else {
			pr_info("charger type: charger IN\n");
			g_chr_type = hw_charging_get_charger_type();
#ifdef CONFIG_POGO_CHARGER
			/* check pogo status, if pogo only set chr type to pogo */
			pr_info("check pogo status: %d \n", pogo_get_state());
			if (g_chr_type == NONSTANDARD_CHARGER) {
				if (0x02 == pogo_get_state()) {
					g_chr_type = POGO_CHARGER;
					pr_info("force chr type for pogo \n");
				}				  
			}
#ifdef CONFIG_TCPC_CLASS
			if (g_chr_type == NONSTANDARD_CHARGER && !ignore_usb_check) {
#else		
			if (g_chr_type == NONSTANDARD_CHARGER) {
#endif
				while(detect_times--){
					pr_info("NONSTANDARD CHARGER detect:%d\n",detect_times);
					g_chr_type = hw_charging_get_charger_type();
					if(NONSTANDARD_CHARGER!=g_chr_type){
						break;
					}
				}	
			}
			
			if (g_chr_type == STANDARD_HOST) {
				boot_mode = get_boot_mode();
				if (boot_mode == KERNEL_POWER_OFF_CHARGING_BOOT
				        || boot_mode == LOW_POWER_OFF_CHARGING_BOOT) {
#ifndef CONFIG_TCPC_CLASS
				    i_ACA_type = hw_otg_get_aca_type_detection();
				    if (0x0 == i_ACA_type)
#endif /* CONFIG_TCPC_CLASS */ 
				    {
				        if (0x02 == pogo_get_state()) {
				            g_chr_type = POGO_CHARGER;
				            pr_info("force chr type for pogo \n");
				        }
				    }
				}
			}
#ifndef CONFIG_TCPC_CLASS
			if (g_chr_type == NONSTANDARD_CHARGER) {
				boot_mode = get_boot_mode();
				if (boot_mode == KERNEL_POWER_OFF_CHARGING_BOOT
					|| boot_mode == LOW_POWER_OFF_CHARGING_BOOT) {
					i_ACA_type = hw_otg_get_aca_type_detection();
					if (0x4 == i_ACA_type) {
						g_chr_type = STANDARD_CHARGER;
						pr_info("force chr type for ac\n");
					}
				}
			}


			if(thub_connect_ta && (g_chr_type == NONSTANDARD_CHARGER)) {
				g_chr_type = STANDARD_CHARGER;
				pr_info("force chr type for ac\n");
			}
#endif /* CONFIG_TCPC_CLASS */
#endif
			chrdet_inform_psy_changed(g_chr_type, 1);
		}
	} else {
		hw_otg_reset_aca_type();
		pr_info("charger type: charger OUT\n");
		g_chr_type = CHARGER_UNKNOWN;
		thub_connect_ta = false;
		chrdet_inform_psy_changed(g_chr_type, 0);
	}

	mutex_unlock(&chrdet_lock);
}

/* Charger Detection */
void do_charger_detect(void)
{
	if (pmic_get_register_value(PMIC_RGS_CHRDET))
		mtk_pmic_enable_chr_type_det(true);
	else
		mtk_pmic_enable_chr_type_det(false);
}

/* PMIC Int Handler */
void chrdet_int_handler(void)
{
	/*
	 * pr_notice("[chrdet_int_handler]CHRDET status = %d....\n",
	 *	pmic_get_register_value(PMIC_RGS_CHRDET));
	 */
	if (!pmic_get_register_value(PMIC_RGS_CHRDET)) {
		int boot_mode = 0;

		hw_bc11_done();
		boot_mode = get_boot_mode();

		if (boot_mode == KERNEL_POWER_OFF_CHARGING_BOOT
		    || boot_mode == LOW_POWER_OFF_CHARGING_BOOT) {
			pr_info("[chrdet_int_handler] Unplug Charger/USB\n");
#ifndef CONFIG_TCPC_CLASS
			//msleep(3000);
			//orderly_poweroff(true);
#else
			return;
#endif
		}
	}
	do_charger_detect();
}


/* Charger Probe Related */
#ifdef __SW_CHRDET_IN_PROBE_PHASE__
static void do_charger_detection_work(struct work_struct *data)
{
	if (pmic_get_register_value(PMIC_RGS_CHRDET))
		do_charger_detect();
}
#endif

static int __init pmic_chrdet_init(void)
{
	mutex_init(&chrdet_lock);
	chrdet_psy = power_supply_get_by_name("charger");
	if (!chrdet_psy) {
		pr_notice("%s: get power supply failed\n", __func__);
		return -EINVAL;
	}

#ifdef __SW_CHRDET_IN_PROBE_PHASE__
	/* do charger detect here to prevent HW miss interrupt*/
	INIT_WORK(&chr_work, do_charger_detection_work);
	schedule_work(&chr_work);
#endif

#ifndef CONFIG_TCPC_CLASS
	pmic_register_interrupt_callback(INT_CHRDET_EDGE, chrdet_int_handler);
	pmic_enable_interrupt(INT_CHRDET_EDGE, 1, "PMIC");
#endif

	return 0;
}

late_initcall(pmic_chrdet_init);

#endif /* CONFIG_FPGA_EARLY_PORTING */
