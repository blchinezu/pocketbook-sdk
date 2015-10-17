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
#ifndef __ASM_ARCH_MXC_PMIC_LIGHT_H__
#define __ASM_ARCH_MXC_PMIC_LIGHT_H__

/*!
 * @defgroup PMIC_LIGHT PMIC Light Driver
 * @ingroup PMIC_DRVRS
 */

/*!
 * @file arch-mxc/pmic_light.h
 * @brief This is the header of PMIC Light driver.
 *
 * @ingroup PMIC_LIGHT
 */

#include <linux/ioctl.h>
#include <linux/pmic_status.h>
#include <linux/pmic_external.h>

/*!
 * @name IOCTL user space interface
 */

/*! @{ */
/*!
 * Enable Backlight.
 * Argument type: none.
 */
#define PMIC_BKLIT_ENABLE                   _IO('p', 0xe0)
/*!
 * Disable Backlight.
 * Argument type: none.
 */
#define PMIC_BKLIT_DISABLE                  _IO('p', 0xe1)
/*!
 * Set backlight configuration.
 * Argument type: pointer to t_bklit_setting_param
 */
#define PMIC_SET_BKLIT                      _IOW('p', 0xe2, int)
/*!
 * Get backlight configuration.
 * Argument type: pointer to t_bklit_setting_param
 */
#define PMIC_GET_BKLIT                      _IOWR('p', 0xe3, int)
/*!
 * Ramp up configuration.
 * Argument type: t_bklit_channel
 */
#define PMIC_RAMPUP_BKLIT                   _IOW('p', 0xe4, int)
/*!
 * Ramp down configuration.
 * Argument type: t_bklit_channel
 */
#define PMIC_RAMPDOWN_BKLIT                 _IOW('p', 0xe5, int)
/*!
 * Enable Tri-color LED.
 * Argument type: t_tcled_enable_param
 */
#define PMIC_TCLED_ENABLE                   _IOW('p', 0xe6, int)
/*!
 * Disable Tri-color LED.
 * Argument type: t_funlight_bank
 */
#define PMIC_TCLED_DISABLE                  _IOW('p', 0xe7, int)
/*!
 * Start Tri-color LED pattern.
 * Argument type: t_fun_param
 */
#define PMIC_TCLED_PATTERN                  _IOW('p', 0xe8, int)
/*!
 * Enable Backlight & tcled.
 * Argument type: none.
 */
#define PMIC_BKLIT_TCLED_ENABLE             _IO('p', 0xe9)
/*!
 * Disable Backlight & tcled.
 * Argument type: none.
 */
#define PMIC_BKLIT_TCLED_DISABLE            _IO('p', 0xea)
/*!
 * Reset ramp up configuration.
 * Argument type: t_bklit_channel
 */
#define PMIC_OFF_RAMPUP_BKLIT               _IOW('p', 0xeb, int)
/*!
 * Reset ramp down configuration.
 * Argument type: t_bklit_channel
 */
#define PMIC_OFF_RAMPDOWN_BKLIT             _IOW('p', 0xec, int)
/*!
 * Set tcled ind configuration.
 * Argument type: t_tcled_ind_param
 */
#define PMIC_SET_TCLED			    _IOW('p', 0xed, int)
/*!
 * Get tcled ind configuration.
 * Argument type: t_tcled_ind_param
 */
#define PMIC_GET_TCLED			    _IOWR('p', 0xee, int)
/*! @} */
/*!
 * @enum t_bklit_mode
 * @brief Backlight modes.
 */
typedef enum {
	BACKLIGHT_CURRENT_CTRL_MODE,	/*! < Current control mode */
	BACKLIGHT_TRIODE_MODE	/*! < Triode mode */
} t_bklit_mode;

/*!
 * @enum t_bklit_channel
 * @brief Backlight channels.
 */
typedef enum {
	BACKLIGHT_LED1,		/*! < Backlight channel 1 */
	BACKLIGHT_LED2,		/*! < Backlight channel 2 */
	BACKLIGHT_LED3		/*! < Backlight channel 3 */
} t_bklit_channel;

/*!
 * @enum t_bklit_strobe_mode
 * @brief Backlight Strobe Light Pulsing modes.
 */
typedef enum {
	/*!
	 * No Strobe Light Pulsing
	 */
	BACKLIGHT_STROBE_NONE,
	/*!
	 * Strobe Light Pulsing at 3.3% duty cycle over 300msec (Driver goes
	 * into Triode Mode with pulses constrained to 10msec.)
	 */
	BACKLIGHT_STROBE_FAST,
	/*!
	 * Strobe Light Pulsing at 10% duty cycle over 100msec (Driver goes
	 * into Triode Mode with pulses constrained to 10msec.)
	 */
	BACKLIGHT_STROBE_SLOW
} t_bklit_strobe_mode;

/*!
 * @struct t_bklit_setting_param
 * @brief Backlight setting.
 */

typedef struct {
	t_bklit_channel channel;	/*!< Channel */
	t_bklit_mode mode;	/*!< Mode */
	t_bklit_strobe_mode strobe;	/*!< Strobe mode */
	unsigned char current_level;	/*!< Current level */
	unsigned char duty_cycle;	/*!< Duty cycle */
	unsigned char cycle_time;	/*!< Cycle time */
	bool edge_slow;		/*!< Edge Slow */
	bool en_dis;		/*!< Enable disable boost mode */
	unsigned int abms;	/*!< Adaptive boost
				 *   mode selection */
	unsigned int abr;	/*!< Adaptive
				 *   boost reference */
} t_bklit_setting_param;

/*!
 * @enum t_funlight_bank
 * @brief Tri-color LED fun light banks.
 */
typedef enum {
	TCLED_FUN_BANK1 = 0,	/*! < Fun light bank 1 */
	TCLED_FUN_BANK2,	/*! < Fun light bank 2 */
	TCLED_FUN_BANK3		/*! < Fun light bank 3 */
} t_funlight_bank;

/*!
 * @enum t_tcled_mode
 * @brief Tri-color LED operation modes.
 *
 * The Tri-Color LED Driver circuitry includes 2 modes of operation. In LED
 * Indicator Mode, this circuitry operates as Red and Green LED Drivers with
 * flasher timing to indicate GSM network status. In Fun Light Mode, this
 * circuitry provides expanded capability for current control and distribution
 * that supplements the three channels.
 */
typedef enum {
	TCLED_IND_MODE = 0,	/*! < LED Indicator Mode */
	TCLED_FUN_MODE		/*! < Fun Light Mode */
} t_tcled_mode;

/*!
 * @struct t_tcled_enable_param
 * @brief enable setting.
 */
typedef struct {
	t_funlight_bank bank;	/*!< Bank */
	t_tcled_mode mode;	/*!< Mode */
} t_tcled_enable_param;

/*!
 * @enum t_ind_channel
 * @brief Tri-color LED indicator mode channels.
 *
 */

typedef enum {
	TCLED_IND_RED = 0,	/*! < Red LED */
	TCLED_IND_GREEN,	/*! < Green LED */
	TCLED_IND_BLUE		/*! < Blue LED */
} t_ind_channel;

/*!
 * @enum t_funlight_channel
 * @brief Tri-color LED fun light mode channels.
 *
 */
typedef enum {
	TCLED_FUN_CHANNEL1 = 0,	/*! < Fun light channel 1 (Red) */
	TCLED_FUN_CHANNEL2,	/*! < Fun light channel 2 (Green) */
	TCLED_FUN_CHANNEL3	/*! < Fun light channel 3 (Blue) */
} t_funlight_channel;

/*!
 * @enum t_tcled_ind_blink_pattern
 * @brief Tri-color LED Indicator Mode blinking mode.
 */
typedef enum {
	TCLED_IND_OFF = 0,	/*! < Continuous off */
	TCLED_IND_BLINK_1,	/*! < 1 / 31 */
	TCLED_IND_BLINK_2,	/*! < 2 / 31 */
	TCLED_IND_BLINK_3,	/*! < 3 / 31  */
	TCLED_IND_BLINK_4,	/*! < 4 / 31  */
	TCLED_IND_BLINK_5,	/*! < 5 / 31  */
	TCLED_IND_BLINK_6,	/*! < 6 / 31  */
	TCLED_IND_BLINK_7,	/*! < 7 / 31  */
	TCLED_IND_BLINK_8,	/*! < 8 / 31  */
	TCLED_IND_BLINK_9,	/*! < 9 / 31  */
	TCLED_IND_BLINK_10,	/*! < 10 / 31  */
	TCLED_IND_BLINK_11,	/*! < 11 / 31  */
	TCLED_IND_BLINK_12,	/*! < 12 / 31  */
	TCLED_IND_BLINK_13,	/*! < 13 / 31  */
	TCLED_IND_BLINK_14,	/*! < 14 / 31  */
	TCLED_IND_BLINK_15,	/*! < 15 / 31  */
	TCLED_IND_BLINK_16,	/*! < 16 / 31  */
	TCLED_IND_BLINK_17,	/*! < 17 / 31  */
	TCLED_IND_BLINK_18,	/*! < 18 / 31  */
	TCLED_IND_BLINK_19,	/*! < 19 / 31  */
	TCLED_IND_BLINK_20,	/*! < 20 / 31  */
	TCLED_IND_BLINK_21,	/*! < 21 / 31  */
	TCLED_IND_BLINK_22,	/*! < 22 / 31  */
	TCLED_IND_BLINK_23,	/*! < 23 / 31  */
	TCLED_IND_BLINK_24,	/*! < 24 / 31  */
	TCLED_IND_BLINK_25,	/*! < 25 / 31  */
	TCLED_IND_BLINK_26,	/*! < 26 / 31  */
	TCLED_IND_BLINK_27,	/*! < 27 / 31  */
	TCLED_IND_BLINK_28,	/*! < 28 / 31  */
	TCLED_IND_BLINK_29,	/*! < 29 / 31  */
	TCLED_IND_BLINK_30,	/*! < 30 / 31  */
	TCLED_IND_ON		/*! < Continuous on */
} t_tcled_ind_blink_pattern;

/*!
 * @enum t_tcled_cur_level
 * @brief Tri-color LED current levels.
 */
typedef enum {
	TCLED_CUR_LEVEL_1 = 0,	/*! < Tri-Color LED current level 1 */
	TCLED_CUR_LEVEL_2,	/*! < Tri-Color LED current level 2 */
	TCLED_CUR_LEVEL_3,	/*! < Tri-Color LED current level 3 */
	TCLED_CUR_LEVEL_4	/*! < Tri-Color LED current level 4 */
} t_tcled_cur_level;

/*!
 * @enum t_tcled_fun_cycle_time
 * @brief Tri-color LED fun light mode cycle time.
 */
typedef enum {
	TC_CYCLE_TIME_1 = 0,	/*! < Tri-Color LED cycle time 1 */
	TC_CYCLE_TIME_2,	/*! < Tri-Color LED cycle time 2 */
	TC_CYCLE_TIME_3,	/*! < Tri-Color LED cycle time 3 */
	TC_CYCLE_TIME_4		/*! < Tri-Color LED cycle time 4 */
} t_tcled_fun_cycle_time;

/*!
 * @enum t_tcled_fun_speed
 * @brief Tri-color LED fun light mode pattern speed.
 */
typedef enum {
	TC_OFF = 0,		/*! < Tri-Color pattern off */
	TC_SLOW,		/*! < Tri-Color slow pattern */
	TC_FAST			/*! < Tri-Color fast pattern */
} t_tcled_fun_speed;

/*!
 * @enum t_tcled_fun_speed
 * @brief Tri-color LED fun light mode pattern speed.
 */
typedef enum {
	TC_STROBE_OFF = 0,	/*! < No strobe */
	TC_STROBE_SLOW,		/*! < Slow strobe pattern */
	TC_STROBE_FAST		/*! < fast strobe pattern */
} t_tcled_fun_strobe_speed;

/*!
 * @enum t_chaselight_pattern
 * @brief Tri-color LED fun light mode chasing light patterns.
 */
typedef enum {
	PMIC_RGB = 0,		/*!< R -> G -> B */
	BGR			/*!< B -> G -> R */
} t_chaselight_pattern;

/*!
 * This enumeration of Fun Light Pattern.
 */
typedef enum {
	/*!
	 * Blended ramps slow
	 */
	BLENDED_RAMPS_SLOW,
	/*!
	 * Blended ramps fast
	 */
	BLENDED_RAMPS_FAST,
	/*!
	 * Saw ramps slow
	 */
	SAW_RAMPS_SLOW,
	/*!
	 * Saw ramps fast
	 */
	SAW_RAMPS_FAST,
	/*!
	 * Blended bowtie slow
	 */
	BLENDED_BOWTIE_SLOW,
	/*!
	 * Blended bowtie fast
	 */
	BLENDED_BOWTIE_FAST,
	/*!
	 * Strobe slow
	 */
	STROBE_SLOW,
	/*!
	 * Strobe fast
	 */
	STROBE_FAST,
	/*!
	 * Chasing Light RGB Slow
	 */
	CHASING_LIGHT_RGB_SLOW,
	/*!
	 * Chasing Light RGB fast
	 */
	CHASING_LIGHT_RGB_FAST,
	/*!
	 * Chasing Light BGR Slow
	 */
	CHASING_LIGHT_BGR_SLOW,
	/*!
	 * Chasing Light BGR fast
	 */
	CHASING_LIGHT_BGR_FAST,
} t_fun_pattern;

/*!
 * @struct t_fun_param
 * @brief LED fun pattern IOCTL parameter
 */
typedef struct {
	t_funlight_bank bank;	/*!< TCLED bank */
	t_funlight_channel channel;	/*!< TCLED channel */
	t_fun_pattern pattern;	/*!< Fun pattern */
} t_fun_param;

/*!
 * @enum t_led_channel
 * @brief LED channels including backlight and tri-color LEDs.
 */
typedef enum {
	AUDIO_LED1,		/*! < Backlight channel 1 */
	AUDIO_LED2,		/*! < Backlight channel 2 */
	AUDIO_LEDR,		/*! < Fun light channel 1 (Red) */
	AUDIO_LEDG,		/*! < Fun light channel 2 (Green) */
	AUDIO_LEDB		/*! < Fun light channel 3 (Blue) */
} t_led_channel;

/*!
 * @enum t_aud_path
 * @brief LED audio modulation in-out audio channels
 */
typedef enum {
	MIXED_RX = 0,		/*!<  Mixed L & R Channel RX audio */
	TX			/*!<  TX path */
} t_aud_path;

/*!
 * @enum t_aud_gain
 * @brief LED audio modulation in-out audio channels
 */
typedef enum {
	GAIN_MINUS6DB = 0,	/*!< -6 dB */
	GAIN_0DB,		/*!< 0 dB */
	GAIN_6DB,		/*!< 6 dB */
	GAIN_12DB		/*!< 12 dB */
} t_aud_gain;

/*!
 * @struct t_tcled_ind_param
 * @brief LED parameter
 */
typedef struct {
	t_funlight_bank bank;	/*! < tcled bank */
	t_ind_channel channel;	/*! < tcled channel */
	t_tcled_cur_level level;	/*! < tcled current level */
	t_tcled_ind_blink_pattern pattern;	/*! < tcled dutty cycle */
	bool skip;		/*! < tcled skip */
	bool rampup;		/*! < tcled rampup */
	bool rampdown;		/*! < tcled rampdown */
	bool half_current;	/*! < tcled half current */
} t_tcled_ind_param;

#if defined(CONFIG_MXC_PMIC_MC13892)

enum curr_level {
	LIT_CURR_0 = 0,
	LIT_CURR_3,
	LIT_CURR_6,
	LIT_CURR_9,
	LIT_CURR_12,
	LIT_CURR_15,
	LIT_CURR_18,
	LIT_CURR_21,
	/* below setting only used for main/aux/keypad */
	LIT_CURR_HI_0,
	LIT_CURR_HI_6,
	LIT_CURR_HI_12,
	LIT_CURR_HI_18,
	LIT_CURR_HI_24,
	LIT_CURR_HI_30,
	LIT_CURR_HI_36,
	LIT_CURR_HI_42,
};

enum lit_channel {
	LIT_MAIN = 0,
	LIT_AUX,
	LIT_KEY,
	LIT_RED,
	LIT_GREEN,
	LIT_BLUE,
};

#endif

/* EXPORTED FUNCTIONS */

#endif				/* __ASM_ARCH_MXC_PMIC_LIGHT_H__ */
