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
#ifndef __ASM_ARCH_MXC_PMIC_BATTERY_H__
#define __ASM_ARCH_MXC_PMIC_BATTERY_H__

/*!
 * @defgroup PMIC_BATTERY PMIC Battery Driver
 * @ingroup PMIC_DRVRS
 */

/*!
 * @file arch-mxc/pmic_battery.h
 * @brief This is the header of PMIC Battery driver.
 *
 * @ingroup PMIC_BATTERY
 */

#include <linux/ioctl.h>
#include <linux/pmic_status.h>
#include <linux/pmic_external.h>

/*!
 * @name IOCTL user space interface
 */

/*! @{ */
/*!
 * Enable and disable charger.
 * Argument type: pointer to t_charger_setting
 */
#define PMIC_BATT_CHARGER_CONTROL              _IOW('p', 0xc0, int)
/*!
 * Set charger configuration.
 * Argument type: pointer to t_charger_setting
 */
#define PMIC_BATT_SET_CHARGER                  _IOW('p', 0xc1, int)
/*!
 * Get charger configuration.
 * Argument type: pointer to t_charger_setting
 */
#define PMIC_BATT_GET_CHARGER                  _IOR('p', 0xc2, int)
/*!
 * Get charger current.
 * Argument type: pointer to t_charger_setting
 */
#define PMIC_BATT_GET_CHARGER_CURRENT          _IOR('p', 0xc3, int)
/*!
 * Set EOL control
 * Argument type: pointer to t_eol_setting
 */
#define PMIC_BATT_EOL_CONTROL                   _IOW('p', 0xc4, int)
/*!
 * Enable and disable charging LED.
 * Argument type: bool
 */
#define PMIC_BATT_LED_CONTROL                   _IOW('p', 0xc5, int)
/*!
 * Enable and disable reverse supply.
 * Argument type: bool
 */
#define PMIC_BATT_REV_SUPP_CONTROL              _IOW('p', 0xc6, int)
/*!
 * Enable and disable unregulated charging mode.
 * Argument type: bool
 */
#define PMIC_BATT_UNREG_CONTROL                 _IOW('p', 0xc7, int)

/*!
 * Set the output controls.
 * Argument type: t_control
 */
#define PMIC_BATT_SET_OUT_CONTROL                _IOW('p', 0xc8, int)
/*!
 * Set the over voltage threshold.
 * Argument type: int
 */
#define PMIC_BATT_SET_THRESHOLD	                 _IOW('p', 0xc9, int)

/*!
 * Get the charger voltage.
 * Argument type: int
 */
#define PMIC_BATT_GET_CHARGER_VOLTAGE		_IOR('p', 0xca, int)
/*!
 * Get the battery voltage.
 * Argument type: int
 */
#define PMIC_BATT_GET_BATTERY_VOLTAGE		_IOR('p', 0xcb, int)
/*!
 * Get the battery current.
 * Argument type: int
 */
#define PMIC_BATT_GET_BATTERY_CURRENT		_IOR('p', 0xcc, int)
/*!
 * Get the charger sensor.
 * Argument type: int
 */
#define PMIC_BATT_GET_CHARGER_SENSOR		_IOR('p', 0xcd, int)
/*!
 * Get the battery temperature.
 * Argument type: int
 */
#define PMIC_BATT_GET_BATTERY_TEMPERATURE	_IOR('p', 0xce, int)
/*! @} */


#define ADAPTER_THIRDPARTY_INSERT 0x3

#define USB_OFFLINE 4
/*!
 * This enumeration defines battery chargers.
 */
typedef enum {
	BATT_MAIN_CHGR = 0,	/*!< Main battery charger */
	BATT_CELL_CHGR,		/*!< Cell battery charger */
	BATT_TRCKLE_CHGR	/*!< Trickle charger (only available on mc13783) */
} t_batt_charger;

/*!
 * This enumeration defines the bp threshold.
 */
typedef enum {
	BATT_BP_0 = 0,		/*!< LOBATL UVDET + 0.2 */
	BATT_BP_1,		/*!< LOBATL UVDET + 0.3 */
	BATT_BP_2,		/*!< LOBATL UVDET + 0.4 */
	BATT_BP_3		/*!< LOBATL UVDET + 0.5 */
} t_bp_threshold;

/*!
 * This enumeration of all types of output controls
 */
typedef enum {
	/*!
	 * controlled hardware
	 */
	CONTROL_HARDWARE = 0,
	/*!
	 * BPFET is driven low, BATTFET is driven high
	 */
	CONTROL_BPFET_LOW,
	/*!
	 * BPFET is driven high, BATTFET is driven low
	 */
	CONTROL_BPFET_HIGH,
} t_control;

/*!
 * This enumeration define all battery interrupt
 */
typedef enum {
	/*!
	 * Charge detection interrupt
	 */
	BAT_IT_CHG_DET,
	/*!
	 * Charge over voltage detection it
	 */
	BAT_IT_CHG_OVERVOLT,
	/*!
	 * Charge path reverse current it
	 */
	BAT_IT_CHG_REVERSE,
	/*!
	 * Charge path short circuitin revers supply mode it
	 */
	BAT_IT_CHG_SHORT_CIRCUIT,
	/*!
	 * Charger has switched its mode (CC to CV or CV to CC)
	 */
	BAT_IT_CCCV,
	/*!
	 * Charge current has dropped below its threshold
	 */
	BAT_IT_BELOW_THRESHOLD,
} t_batt_event;

/*!
 * This structure is used for the following battery changer control
 * IOCTLs:
 * - PMIC_BATT_CHARGER_CONTROL
 * - PMIC_BATT_SET_CHARGER
 * - PMIC_BATT_GET_CHARGER
 */
typedef struct {
	/*!
	 * Charger
	 */
	t_batt_charger chgr;
	/*!
	 * Turn on charger
	 */
	bool on;
	/*!
	 * Charging voltage
	 */
	unsigned char c_voltage;
	/*!
	 * Charging current
	 */
	unsigned char c_current;
} t_charger_setting;

/*!
 * This structure is used for EOL setting IOCTL PMIC_BATT_EOL_CONTROL
 */
typedef struct {
	/*!
	 * Enable EOL comparator
	 */
	bool enable;
	/*!
	 * c_voltage threshold - Used on SC55112
	 */
	unsigned char threshold;
	/*!
	 * bp threshold - Used on mc13783
	 */
	t_bp_threshold typical;
} t_eol_setting;

/* EXPORTED FUNCTIONS */


#endif				/* __ASM_ARCH_MXC_PMIC_BATTERY_H__ */
