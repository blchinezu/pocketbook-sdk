/*
 * Copyright 2004-2011 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#ifndef __ASM_ARCH_MXC_PMIC_ADC_H__
#define __ASM_ARCH_MXC_PMIC_ADC_H__

/*!
 * @defgroup PMIC_ADC PMIC Digitizer Driver
 * @ingroup PMIC_DRVRS
 */

/*!
 * @file arch-mxc/pmic_adc.h
 * @brief This is the header of PMIC ADC driver.
 *
 * @ingroup PMIC_ADC
 */

#include <linux/ioctl.h>
#include <linux/pmic_status.h>
#include <linux/pmic_external.h>

/*!
 * @name IOCTL user space interface
 */

/*! @{ */
/*!
 * Initialize ADC.
 * Argument type: none.
 */
#define PMIC_ADC_INIT                   _IO('p', 0xb0)
/*!
 * De-initialize ADC.
 * Argument type: none.
 */
#define PMIC_ADC_DEINIT                 _IO('p', 0xb1)
/*!
 * Convert one channel.
 * Argument type: pointer to t_adc_convert_param.
 */
#define PMIC_ADC_CONVERT                _IOWR('p', 0xb2, int)
/*!
 * Convert one channel eight samples.
 * Argument type: pointer to t_adc_convert_param.
 */
#define PMIC_ADC_CONVERT_8X             _IOWR('p', 0xb3, int)
/*!
 * Convert multiple channels.
 * Argument type: pointer to t_adc_convert_param.
 */
#define PMIC_ADC_CONVERT_MULTICHANNEL   _IOWR('p', 0xb4, int)
/*!
 * Set touch screen operation mode.
 * Argument type: t_touch_mode.
 */
#define PMIC_ADC_SET_TOUCH_MODE         _IOW('p', 0xb5, int)
/*!
 * Get touch screen operation mode.
 * Argument type: pointer to t_touch_mode.
 */
#define PMIC_ADC_GET_TOUCH_MODE         _IOR('p', 0xb6, int)
/*!
 * Get touch screen sample.
 * Argument type: pointer to t_touch_sample.
 */
#define PMIC_ADC_GET_TOUCH_SAMPLE       _IOWR('p', 0xb7, int)
/*!
 * Get battery current.
 * Argument type: pointer to unsigned short.
 */
#define PMIC_ADC_GET_BATTERY_CURRENT    _IOR('p', 0xb8, int)
/*!
 * Activate comparator.
 * Argument type: pointer to t_adc_comp_param.
 */
#define PMIC_ADC_ACTIVATE_COMPARATOR    _IOW('p', 0xb9, int)
/*!
 * De-active comparator.
 * Argument type: none.
 */
#define PMIC_ADC_DEACTIVE_COMPARATOR    _IOW('p', 0xba, int)

/*!
 * Install touch screen read interface.
 */
#define TOUCH_SCREEN_READ_INSTALL       _IOWR('D', 4, int)
/*!
 * Remove touch screen read interface.
 */
#define TOUCH_SCREEN_READ_UNINSTALL     _IOWR('D', 5, int)

/*! @{ */
/*!
 * @name Touch Screen minimum and maximum values
 */
#define TS_X_MIN                80	/*! < Minimum X */
#define TS_Y_MIN                80	/*! < Minimum Y */

#define TS_X_MAX                1000	/*! < Maximum X */
#define TS_Y_MAX                1000	/*! < Maximum Y */
/*! @} */
/*!
 * This enumeration defines input channels for PMIC ADC
 */

typedef enum {
	BATTERY_VOLTAGE,
	BATTERY_CURRENT,
	CHARGE_VOLTAGE,
	CHARGE_CURRENT,
	APPLICATION_SUPPLY,
	TS_X_POS1,
	TS_X_POS2,
	TS_Y_POS1,
	TS_Y_POS2,
	GEN_PURPOSE_AD4,
	GEN_PURPOSE_AD5,
	GEN_PURPOSE_AD6,
	GEN_PURPOSE_AD7,
	GEN_PURPOSE_AD8,
	GEN_PURPOSE_AD9,
	GEN_PURPOSE_AD10,
	GEN_PURPOSE_AD11,
	USB_ID,
	LICELL,
	RAWEXTBPLUSSENSE,
	MPBSENSE,
	BATSENSE,
	GND,
	THERMISTOR,
	DIE_TEMP
} t_channel;

/*!
 * This enumeration defines reason of ADC Comparator interrupt.
 */
typedef enum {
	/*!
	 * Greater than WHIGH
	 */
	GTWHIGH,
	/*!
	 * Less than WLOW
	 */
	LTWLOW,
} t_comp_exception;

/*!
 * ADC comparator callback function type
 */
typedef void (*t_comparator_cb) (t_comp_exception reason);

/*!
 * This enumeration defines the touch screen operation modes.
 */
typedef enum {
	/*!
	 * Touch Screen X position
	 */
	TS_X_POSITION = 0,
	/*!
	 * Touch Screen Y position
	 */
	TS_Y_POSITION = 1,
	/*!
	 * Pressure
	 */
	TS_PRESSURE = 2,
	/*!
	 * Plate X
	 */
	TS_PLATE_X = 3,
	/*!
	 * Plate Y
	 */
	TS_PLATE_Y = 4,
	/*!
	 * Standby
	 */
	TS_STANDBY = 5,
	/*!
	 * No touch screen, TSX1, TSX2, TSY1 and TSY2 are used as  general
	 * purpose A/D inputs.
	 */
	TS_NONE = 6,
} t_touch_mode;
/*!
 * This structure is used to report touch screen value.
 */
typedef struct {
/*!
	 * Touch Screen X position
	 */
	unsigned int x_position;
	/*!
	 * Touch Screen X position1
	 */
	unsigned int x_position1;
	/*!
	 * Touch Screen X position2
	 */
	unsigned int x_position2;
	/*!
	 * Touch Screen X position3
	 */
	unsigned int x_position3;
	/*!
	 * Touch Screen Y position
	 */
	unsigned int y_position;
	/*!
	 * Touch Screen Y position1
	 */
	unsigned int y_position1;
	/*!
	 * Touch Screen Y position2
	 */
	unsigned int y_position2;
	/*!
	 * Touch Screen Y position3
	 */
	unsigned int y_position3;
	/*!
	 * Touch Screen contact value
	 */
	unsigned int contact_resistance;
} t_touch_screen;

/*!
 * This enumeration defines ADC conversion modes.
 */
typedef enum {
	/*!
	 * Sample 8 channels, 1 sample per channel
	 */
	ADC_8CHAN_1X = 0,
	/*!
	 * Sample 1 channel 8 times
	 */
	ADC_1CHAN_8X,
} t_conversion_mode;

/*!
 * This structure is used with IOCTL code \a PMIC_ADC_CONVERT,
 * \a PMIC_ADC_CONVERT_8X and \a PMIC_ADC_CONVERT_MULTICHANNEL.
 */

typedef struct {
	/*!
	 * channel or channels to be sampled.
	 */
	t_channel channel;
	/*!
	 * holds up to 16 sampling results
	 */
	unsigned short result[16];
} t_adc_convert_param;

/*!
 * This structure is used to activate/deactivate ADC comparator.
 */
typedef struct {
	/*!
	 * wlow.
	 */
	unsigned char wlow;
	/*!
	 * whigh.
	 */
	unsigned char whigh;
	/*!
	 * channel to monitor
	 */
	t_channel channel;
	/*!
	 * callback function.
	 */
	t_comparator_cb callback;
} t_adc_comp_param;

struct pmic_adc_api {
	int (*is_pmic_adc_ready)(void);
	PMIC_STATUS (*pmic_adc_convert)(t_channel, unsigned short *);
	PMIC_STATUS (*pmic_adc_get_touch_sample)(t_touch_screen *, int);
};

/* EXPORTED FUNCTIONS */

#endif				/* __ASM_ARCH_MXC_PMIC_ADC_H__ */
