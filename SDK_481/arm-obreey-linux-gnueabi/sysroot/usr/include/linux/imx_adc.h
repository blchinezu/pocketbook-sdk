/*
 * Copyright 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU Lesser General
 * Public License.  You may obtain a copy of the GNU Lesser General
 * Public License Version 2.1 or later at the following locations:
 *
 * http://www.opensource.org/licenses/lgpl-license.html
 * http://www.gnu.org/copyleft/lgpl.html
 */

#ifndef __ASM_ARCH_IMX_ADC_H__
#define __ASM_ARCH_IMX_ADC_H__

/*!
 * @defgroup IMX_ADC Digitizer Driver
 * @ingroup IMX_DRVRS
 */

/*!
 * @file arch-mxc/imx_adc.h
 * @brief This is the header of IMX ADC driver.
 *
 * @ingroup IMX_ADC
 */

#include <linux/ioctl.h>

/*!
 * @enum IMX_ADC_STATUS
 * @brief Define return values for all IMX_ADC APIs.
 *
 * These return values are used by all of the IMX_ADC APIs.
 *
 * @ingroup IMX_ADC
 */
enum IMX_ADC_STATUS {
	/*! The requested operation was successfully completed. */
	IMX_ADC_SUCCESS = 0,
	/*! The requested operation could not be completed due to an error. */
	IMX_ADC_ERROR = -1,
	/*!
	 * The requested operation failed because one or more of the
	 * parameters was invalid.
	 */
	IMX_ADC_PARAMETER_ERROR = -2,
	/*!
	 * The requested operation could not be completed because the ADC
	 * hardware does not support it.
	 */
	IMX_ADC_NOT_SUPPORTED = -3,
	/*! Error in malloc function */
	IMX_ADC_MALLOC_ERROR = -5,
	/*! Error in un-subscribe event */
	IMX_ADC_UNSUBSCRIBE_ERROR = -6,
	/*! Event occur and not subscribed */
	IMX_ADC_EVENT_NOT_SUBSCRIBED = -7,
	/*! Error - bad call back */
	IMX_ADC_EVENT_CALL_BACK = -8,
	/*!
	 * The requested operation could not be completed because there
	 * are too many ADC client requests
	 */
	IMX_ADC_CLIENT_NBOVERFLOW = -9,
};

/*
 * Macros implementing error handling
 */
#define CHECK_ERROR(a)			\
do {					\
		int ret = (a); 			\
		if (ret != IMX_ADC_SUCCESS)	\
	return ret; 			\
} while (0)

#define CHECK_ERROR_KFREE(func, freeptrs) \
do { \
	int ret = (func); \
	if (ret != IMX_ADC_SUCCESS) { \
		freeptrs;	\
		return ret;	\
	}	\
} while (0)

#define MOD_NAME  "mxcadc"

/*!
 * @name IOCTL user space interface
 */

/*!
 * Initialize ADC.
 * Argument type: none.
 */
#define IMX_ADC_INIT                   _IO('p', 0xb0)
/*!
 * De-initialize ADC.
 * Argument type: none.
 */
#define IMX_ADC_DEINIT                 _IO('p', 0xb1)
/*!
 * Convert one channel.
 * Argument type: pointer to t_adc_convert_param.
 */
#define IMX_ADC_CONVERT                _IOWR('p', 0xb2, int)
/*!
 * Convert multiple channels.
 * Argument type: pointer to t_adc_convert_param.
 */
#define IMX_ADC_CONVERT_MULTICHANNEL   _IOWR('p', 0xb4, int)

/*! @{ */
/*!
 * @name Touch Screen minimum and maximum values
 */
#define IMX_ADC_DEVICE "/dev/imx_adc"

/*
 * Maximun allowed variation in the three X/Y co-ordinates acquired from
 * touch screen
 */
#define DELTA_Y_MAX             100
#define DELTA_X_MAX             100

/* Upon clearing the filter, this is the delay in restarting the filter */
#define FILTER_MIN_DELAY        4

/* Length of X and Y touch screen filters */
#define FILTLEN                 3

#define TS_X_MAX                1000
#define TS_Y_MAX                1000

#define TS_X_MIN                80
#define TS_Y_MIN                80

/*! @} */
/*!
 * This enumeration defines input channels for IMX ADC
 */

enum t_channel {
	TS_X_POS,
	TS_Y_POS,
	GER_PURPOSE_ADC0,
	GER_PURPOSE_ADC1,
	GER_PURPOSE_ADC2,
	GER_PURPOSE_MULTICHNNEL,
};

/*!
 * This structure is used to report touch screen value.
 */
struct t_touch_screen {
	/* Touch Screen X position */
	unsigned int x_position;
	/* Touch Screen X position1 */
	unsigned int x_position1;
	/* Touch Screen X position2 */
	unsigned int x_position2;
	/* Touch Screen X position3 */
	unsigned int x_position3;
	/* Touch Screen Y position */
	unsigned int y_position;
	/* Touch Screen Y position1 */
	unsigned int y_position1;
	/* Touch Screen Y position2 */
	unsigned int y_position2;
	/* Touch Screen Y position3 */
	unsigned int y_position3;
	/* Touch Screen contact value */
	unsigned int contact_resistance;
	/* Flag indicate the data usability */
	unsigned int valid_flag;
};

/*!
 * This structure is used with IOCTL code \a IMX_ADC_CONVERT,
 * \a IMX_ADC_CONVERT_8X and \a IMX_ADC_CONVERT_MULTICHANNEL.
 */

struct t_adc_convert_param {
	/* channel or channels to be sampled.  */
	enum t_channel channel;
	/* holds up to 16 sampling results */
	unsigned short result[16];
};

/* EXPORTED FUNCTIONS */

#endif				/* __ASM_ARCH_IMX_ADC_H__ */
