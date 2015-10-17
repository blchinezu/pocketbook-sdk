/*
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

/*!
 * @file mx35_asrc.h
 *
 * @brief MX35 Asynchronous Sample Rate Converter
 *
 * @ingroup ??
 */

#ifndef __MXC_ASRC_H__
#define __MXC_ASRC_H__

#define ASRC_IOC_MAGIC	'C'

#define ASRC_REQ_PAIR	_IOWR(ASRC_IOC_MAGIC, 0, struct asrc_req)
#define ASRC_CONFIG_PAIR	_IOWR(ASRC_IOC_MAGIC, 1, struct asrc_config)
#define ASRC_RELEASE_PAIR	_IOW(ASRC_IOC_MAGIC, 2, enum asrc_pair_index)
#define ASRC_QUERYBUF	_IOWR(ASRC_IOC_MAGIC, 3, struct asrc_buffer)
#define ASRC_Q_INBUF	_IOW(ASRC_IOC_MAGIC, 4, struct asrc_buffer)
#define ASRC_DQ_INBUF	_IOW(ASRC_IOC_MAGIC, 5, struct asrc_buffer)
#define ASRC_Q_OUTBUF	_IOW(ASRC_IOC_MAGIC, 6, struct asrc_buffer)
#define ASRC_DQ_OUTBUF	_IOW(ASRC_IOC_MAGIC, 7, struct asrc_buffer)
#define ASRC_START_CONV	_IOW(ASRC_IOC_MAGIC, 8, enum asrc_pair_index)
#define ASRC_STOP_CONV	_IOW(ASRC_IOC_MAGIC, 9, enum asrc_pair_index)
#define ASRC_STATUS	_IOW(ASRC_IOC_MAGIC, 10, struct asrc_status_flags)
#define ASRC_FLUSH	_IOW(ASRC_IOC_MAGIC, 11, enum asrc_pair_index)

enum asrc_pair_index {
	ASRC_PAIR_A,
	ASRC_PAIR_B,
	ASRC_PAIR_C
};

enum asrc_inclk {
	INCLK_NONE = 0x03,
	INCLK_ESAI_RX = 0x00,
	INCLK_SSI1_RX = 0x01,
	INCLK_SSI2_RX = 0x02,
	INCLK_SPDIF_RX = 0x04,
	INCLK_MLB_CLK = 0x05,
	INCLK_ESAI_TX = 0x08,
	INCLK_SSI1_TX = 0x09,
	INCLK_SSI2_TX = 0x0a,
	INCLK_SPDIF_TX = 0x0c,
	INCLK_ASRCK1_CLK = 0x0f,
};

enum asrc_outclk {
	OUTCLK_NONE = 0x03,
	OUTCLK_ESAI_TX = 0x00,
	OUTCLK_SSI1_TX = 0x01,
	OUTCLK_SSI2_TX = 0x02,
	OUTCLK_SPDIF_TX = 0x04,
	OUTCLK_MLB_CLK = 0x05,
	OUTCLK_ESAI_RX = 0x08,
	OUTCLK_SSI1_RX = 0x09,
	OUTCLK_SSI2_RX = 0x0a,
	OUTCLK_SPDIF_RX = 0x0c,
	OUTCLK_ASRCK1_CLK = 0x0f,
};

struct asrc_config {
	enum asrc_pair_index pair;
	unsigned int channel_num;
	unsigned int buffer_num;
	unsigned int dma_buffer_size;
	unsigned int input_sample_rate;
	unsigned int output_sample_rate;
	unsigned int word_width;
	enum asrc_inclk inclk;
	enum asrc_outclk outclk;
};

struct asrc_pair {
	unsigned int start_channel;
	unsigned int chn_num;
	unsigned int chn_max;
	unsigned int active;
	unsigned int overload_error;
};

struct asrc_req {
	unsigned int chn_num;
	enum asrc_pair_index index;
};

struct asrc_querybuf {
	unsigned int buffer_index;
	unsigned int input_length;
	unsigned int output_length;
	unsigned long input_offset;
	unsigned long output_offset;
};

struct asrc_buffer {
	unsigned int index;
	unsigned int length;
	int buf_valid;
};

struct asrc_status_flags {
	enum asrc_pair_index index;
	unsigned int overload_error;
};

#define ASRC_BUF_NA	    -35	/* ASRC DQ's buffer is NOT available */
#define ASRC_BUF_AV	    35	/* ASRC DQ's buffer is available */
enum asrc_error_status {
	ASRC_TASK_Q_OVERLOAD = 0x01,
	ASRC_OUTPUT_TASK_OVERLOAD = 0x02,
	ASRC_INPUT_TASK_OVERLOAD = 0x04,
	ASRC_OUTPUT_BUFFER_OVERFLOW = 0x08,
	ASRC_INPUT_BUFFER_UNDERRUN = 0x10,
};


#endif				/* __MXC_ASRC_H__ */
