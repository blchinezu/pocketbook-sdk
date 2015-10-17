/*
 * Copyright 2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU Lesser General
 * Public License.  You may obtain a copy of the GNU Lesser General
 * Public License Version 2.1 or later at the following locations:
 *
 * http://www.opensource.org/licenses/lgpl-license.html
 * http://www.gnu.org/copyleft/lgpl.html
 */

#ifndef __ASM_ARCH_MXC_PMIC_RTC_H__
#define __ASM_ARCH_MXC_PMIC_RTC_H__

/*!
 * @defgroup PMIC_RTC PMIC RTC Driver
 * @ingroup PMIC_DRVRS
 */

/*!
 * @file arch-mxc/pmic_rtc.h
 * @brief This is the header of PMIC RTC driver.
 *
 * @ingroup PMIC_RTC
 */

/*
 * Includes
 */
#include <linux/ioctl.h>
#include <linux/pmic_status.h>
#include <linux/pmic_external.h>

#define         PMIC_RTC_SET_TIME                    _IOWR('p', 0xd1, int)
#define         PMIC_RTC_GET_TIME                    _IOWR('p', 0xd2, int)
#define         PMIC_RTC_SET_ALARM		     _IOWR('p', 0xd3, int)
#define         PMIC_RTC_GET_ALARM		     _IOWR('p', 0xd4, int)
#define         PMIC_RTC_WAIT_ALARM		     _IOWR('p', 0xd5, int)
#define         PMIC_RTC_ALARM_REGISTER              _IOWR('p', 0xd6, int)
#define         PMIC_RTC_ALARM_UNREGISTER            _IOWR('p', 0xd7, int)

/*!
 * This enumeration define all RTC interrupt
 */
typedef enum {
	/*!
	 * Time of day alarm
	 */
	RTC_IT_ALARM,
	/*!
	 * 1 Hz timetick
	 */
	RTC_IT_1HZ,
	/*!
	 * RTC reset occurred
	 */
	RTC_IT_RST,
} t_rtc_int;

/*
 * RTC PMIC API
 */

/* EXPORTED FUNCTIONS */

#endif				/* __ASM_ARCH_MXC_PMIC_RTC_H__ */
