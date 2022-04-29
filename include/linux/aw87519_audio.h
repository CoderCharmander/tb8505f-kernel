#ifndef __AW87519_H__
#define __AW87519_H__

/******************************************************
 *
 *Load config function
 *
 *****************************************************/
#define AWINIC_CFG_UPDATE_DELAY
#define AW_I2C_RETRIES			5
#define AW_I2C_RETRY_DELAY		2
#define AW_READ_CHIPID_RETRIES		5
#define AW_READ_CHIPID_RETRY_DELAY	2

#define AW87519_REG_CHIPID		0x00
#define AW87519_REG_SYSCTRL		0x01
#define AW87519_REG_BATSAFE		0x02
#define AW87519_REG_BSTOVR		0x03
#define AW87519_REG_BSTVPR		0x04
#define AW87519_REG_PAGR		0x05
#define AW87519_REG_PAGC3OPR		0x06
#define AW87519_REG_PAGC3PR		0x07
#define AW87519_REG_PAGC2OPR		0x08
#define AW87519_REG_PAGC2PR		0x09
#define AW87519_REG_PAGC1PR		0x0A

#define AW87519_CHIPID			0x59
#define AW87519_REG_MAX			11

#define REG_NONE_ACCESS			0
#define REG_RD_ACCESS			(1 << 0)
#define REG_WR_ACCESS			(1 << 1)
#endif
