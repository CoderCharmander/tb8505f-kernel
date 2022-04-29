/*
 * dbmdx-usecase-config-melon.h  --  Preset USE CASE configurations
 *
 * Copyright (C) 2014 DSP Group
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifdef DBMDX_MELON_USECASES_SUPPORTED

#ifndef _DBMDX_USECASE_CONFIG_MELON_H
#define _DBMDX_USECASE_CONFIG_MELON_H

#include "dbmdx-interface.h"
#include "dbmdx-usecase-config-def.h"

/* Melon Low Power Mode Usecase */
/* Mango NR Usecase*/
static struct usecase_config config_uc_melon_low_power = {
	.usecase_name = "uc_melon_low_power",
	.id	= (DBMDX_USECASE_ID_UC_IDX_00 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = false,
	.va_asrp_params_file_name = "",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = "",
	.change_clock_src = false,
	.tdm_clock_freq = TDM_CLK_FREQ_48,
	.number_of_bits = 16,
	.usecase_requires_amodel = true,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = true,
	.usecase_supports_us_buffering = true,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,
	.asrp_output_gain_type = (ASRP_TX_OUT_GAIN |
					ASRP_VCPF_OUT_GAIN |
					ASRP_RX_OUT_GAIN),

	.va_cfg_values = (u32 []){
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K),
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_VT_CP0 |
			DBMDX_REGV_VT_PROC_EN),
		(DBMDX_VA_USLEEP | 0x1500),
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_STREAM_CH_1_CP_0)},
	.num_of_va_cfg_values = 4,

	.config_mics = MIC_CONFIG_BY_USECASE,
	.mic_config = {
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO6_DM1_GPIO12 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO5_DM1_GPIO11 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_DM1),
		0x0000,
		0x0000,
		0x0000},

	.num_of_va_ve_cfg_values = 0,

	.audio_routing_config = {
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,
		DBMDX_UNDEFINED_REGISTER,},

	.num_of_tdm_configs = 0,
	.va_start_cmd_type = START_CMD_TYPE_OPMODE,
	.send_va_start_cmd = true,
	.va_start_cmd = (DBMDX_DETECTION),

	.va_ve_start_cmd_type = START_CMD_TYPE_OPMODE,
	.send_va_ve_start_cmd = false,
	.va_ve_start_cmd = (DBMDX_IDLE),
};


/* Melon NR Dual Mic Usecase*/
static struct usecase_config config_uc_melon_nr_dual_mic = {
#if defined(DBMDX_I2S_BUFFERING_SUPPORTED)
#if defined(DBMDX_MELON_SRATE_48000)
	.usecase_name = "uc_melon_nr_dual_mic_48k",
#else
	.usecase_name = "uc_melon_nr_dual_mic_16k",
#endif
#else
	.usecase_name = "uc_melon_nr_dual_mic",
#endif
	.id	= (DBMDX_USECASE_ID_UC_IDX_01 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = true,
	.va_asrp_params_file_name = "asrp_params_melon_nr.bin",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = NULL,

#if defined(DBMDX_I2S_BUFFERING_SUPPORTED)
	.change_clock_src = true,
#else
	.change_clock_src = false,
#endif

#if defined(DBMDX_MELON_SRATE_48000)
	.tdm_clock_freq = TDM_CLK_FREQ_48,
#else
	.tdm_clock_freq = TDM_CLK_FREQ_16,
#endif

#ifdef AEC_REF_32_TO_16_BIT
	.number_of_bits = 32,
#else
	.number_of_bits = 16,
#endif
	.custom_d4_clock_hz = 55296000,
	.usecase_requires_amodel = true,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = true,
	.usecase_supports_us_buffering = true,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,
	.asrp_output_gain_type = (ASRP_TX_OUT_GAIN |
					ASRP_VCPF_OUT_GAIN |
					ASRP_RX_OUT_GAIN),


	.va_cfg_values = (u32 []){
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K |
			DBMDX_REGV_FW_VAD_TYPE_NO_VAD),
		(DBMDX_REGN_ASRP_OUTPUT_ROUTING |
			DBMDX_REGV_ASRP_OUTPUT_SRC_BFPF_1 |
			DBMDX_REGV_ASRP_OUTPUT_DEST_TX_1),
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_STREAM_CH_1_CP_0),
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
			DBMDX_REGV_EN_COPY_HIST |
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_VT_CP0 |
			DBMDX_REGV_VT_PROC_EN |
			DBMDX_REGV_I2S_CATCHUP_MODE_DISABLED |
			DBMDX_REGV_ALGO1_EN_FW_MODE_1_AND_MODE_2),
		(DBMDX_VA_USLEEP | 0x1500) },
	.num_of_va_cfg_values = 5,

#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.va_post_tdm_cfg_values = (u32 []){
		(DBMDX_REGN_AUDIO_ROUTING_CONFIG |
#if defined(DBMDX_MELON_SRATE_48000) && defined(AEC_REF_32_TO_16_BIT)
			DBMDX_REGV_TDM_SYNC_DELAY_6_CLKS_CYCLES |
#else
			DBMDX_REGV_TDM_SYNC_DELAY_4_CLKS_CYCLES |
#endif
			DBMDX_REGV_TDM_SYNC_RIGHT_CH |
			DBMDX_REGV_USE_TDM_MUSIC_TO_SYNC |
			DBMDX_REGV_MUSIC_IN_TDM0) },
	.num_of_va_post_tdm_cfg_values = 1,
	.usecase_supports_i2s_buffering = true,
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */

	.config_mics = MIC_CONFIG_BY_USECASE,
	.mic_config = {
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO6_DM1_GPIO12 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO5_DM1_GPIO11 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_DM1),
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO8_DM1_GPIO14 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO9_DM1_GPIO13 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_RISING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_DDF0_DM0),
		 0x0000,
		 0x0000 },
	.num_of_va_ve_cfg_values = 0,
	.num_of_va_ve_post_tdm_cfg_values = 0,

	.audio_routing_config = {
		(DBMDX_REGV_IO_SET_0 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_CP_1 |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_1 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_2 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_3 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_4 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_5 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_6 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_7 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		DBMDX_UNDEFINED_REGISTER },

	.tdm_configs = {
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
		/* DBMD4 TDM0_TX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_TX,
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#if defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
		DBMDX_REGV_RX_TX_I2S_CH_SUM_HIGH_AND_LOW_INTO_ONE_SAMPLE |
#if defined(DBMDX_MELON_SRATE_48000) && defined(DBMDX_I2S_CATCHUP_SUPPORTED)
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#elif defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#else
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
#endif
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP3),

			.tdm_interface	= TDM_INTERFACE_VA,
			.num_of_io_reg_configs = 4,
#ifdef AEC_REF_32_TO_16_BIT
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00000064
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x101F003F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00241024
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x100F001F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x0000000F
				}
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */
	},
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.num_of_tdm_configs = 1,
#else
	.num_of_tdm_configs = 0,
#endif
	.va_start_cmd_type = START_CMD_TYPE_OPMODE,
	.send_va_start_cmd = true,
	.va_start_cmd = (DBMDX_DETECTION),
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.va_start_i2s_buffering_cmd = (DBMDX_REGV_TDM0_TX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_BUFFERING_MODE),
#endif
	.send_va_ve_start_cmd = false,
};

/***********************************************************************/

/* Melon Barge IN Single Mic Usecase*/
static struct usecase_config config_uc_melon_barge_in_1mic = {
#if defined(DBMDX_MELON_SRATE_48000)
	.usecase_name = "uc_melon_barge_in_1mic_48k",
#else
	.usecase_name = "uc_melon_barge_in_1mic_16k",
#endif
	.id	= (DBMDX_USECASE_ID_UC_IDX_03 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = true,
	.va_asrp_params_file_name = "asrp_params_melon_aecnr_single_mic.bin",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = NULL,
	.change_clock_src = true,
#if defined(DBMDX_MELON_SRATE_48000)
	.tdm_clock_freq = TDM_CLK_FREQ_48,
#else
	.tdm_clock_freq = TDM_CLK_FREQ_16,
#endif
#ifdef AEC_REF_32_TO_16_BIT
	.number_of_bits = 32,
#else
	.number_of_bits = 16,
#endif
	.custom_d4_clock_hz = 55296000,
	.usecase_requires_amodel = true,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = true,
	.usecase_supports_us_buffering = true,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,

	.va_cfg_values = (u32 []){
		/* 0x80230000 */
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K |
			DBMDX_REGV_DDF_SAMPLE_WIDTH_16_BIT |
			DBMDX_REGV_FW_VAD_TYPE_NO_VAD),
		/* 0x8013fff0 */
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_STREAM_CH_1_CP_0),
		/* 0x80348044 */
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
			DBMDX_REGV_EN_COPY_HIST |
			DBMDX_REGV_ALGO2_EN_FW_MODE_1_ONLY |
#ifdef DBMDX_I2S_CATCHUP_SUPPORTED
			DBMDX_REGV_ENABLE_I2S_CATCHUP |
#endif
#endif
#ifdef DBMDX_MELON_SRATE_48000
			DBMDX_REGV_EN_48_EC_REF_DECIM |
#endif
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_VT_CP0 |
			DBMDX_REGV_VT_PROC_EN |
			DBMDX_REGV_ALGO1_EN_FW_MODE_1_AND_MODE_2),
		(DBMDX_VA_USLEEP | 0x1500) },
	.num_of_va_cfg_values = 4,

#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.va_post_tdm_cfg_values = (u32 []){
		(DBMDX_REGN_AUDIO_ROUTING_CONFIG |
#if defined(DBMDX_MELON_SRATE_48000) && defined(AEC_REF_32_TO_16_BIT)
			/* 0x801F6400 */
			DBMDX_REGV_TDM_SYNC_DELAY_5_CLKS_CYCLES |
#else
			/* 0x801F4400 */
			DBMDX_REGV_TDM_SYNC_DELAY_4_CLKS_CYCLES |
#endif
			DBMDX_REGV_TDM_SYNC_RIGHT_CH |
			DBMDX_REGV_USE_TDM_MUSIC_TO_SYNC |
			DBMDX_REGV_MUSIC_IN_TDM0) },
	.num_of_va_post_tdm_cfg_values = 1,
	.usecase_supports_i2s_buffering = true,
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */

	.config_mics = MIC_CONFIG_BY_USECASE,
	/* .mic_config = { 0x5276, 0x0000, 0x0000, 0x0000 }, */
	.mic_config = {
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO6_DM1_GPIO12 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO5_DM1_GPIO11 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_DM1),
		 0x0000,
		 0x0000,
		 0x0000 },
	.num_of_va_ve_cfg_values = 0,
	.num_of_va_ve_post_tdm_cfg_values = 0,
	/* .audio_routing_config = { 0x0ee0, 0x1eee, 0x22ee, 0x3eee,
	 *				0x4eee, 0x5ee0, 0x6eee, 0x7eee },
	 */
	.audio_routing_config = {
		(DBMDX_REGV_IO_SET_0 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_1 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_2 |
			DBMDX_REGV_IO_3N_2_CP_2 |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_3 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_4 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_5 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_6 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_7 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		DBMDX_UNDEFINED_REGISTER },

	.tdm_configs = {
		/* DBMD4 TDM0_RX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_RX,
			/* .tdm_reg_config = 16KHz: 0x112, 48KHz: 0x912*/
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#ifdef DBMDX_MELON_SRATE_48000
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
				DBMDX_REGV_RX_TX_I2S_CH_USE_HIGH_WORD_ONLY |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP2),

			.tdm_interface	= TDM_INTERFACE_VA,
#ifdef AEC_REF_32_TO_16_BIT
			.num_of_io_reg_configs = 4,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x0080405D
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00002064
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x103F003F
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.num_of_io_reg_configs = 3,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x00800015
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00000007
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x100F001F
				},
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
		/* DBMD4 TDM0_TX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_TX,
			/* .tdm_reg_config = 0x31F, */
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#if defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
		DBMDX_REGV_RX_TX_I2S_CH_SUM_HIGH_AND_LOW_INTO_ONE_SAMPLE |
#if defined(DBMDX_MELON_SRATE_48000) && defined(DBMDX_I2S_CATCHUP_SUPPORTED)
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#elif defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#else
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
#endif
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP3),

			.tdm_interface	= TDM_INTERFACE_VA,
			.num_of_io_reg_configs = 4,
#ifdef AEC_REF_32_TO_16_BIT
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00000064
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x101F003F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00241024
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x100F001F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x0000000F
				}
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */

	},
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.num_of_tdm_configs = 2,
#else
	.num_of_tdm_configs = 1,
#endif
	.va_start_cmd_type = START_CMD_TYPE_TDM,
	.send_va_start_cmd = true,
	/* Enable:
	 *		TDM0_RX (HOST CODEC==>D4)
	 */
	/* .va_start_cmd = 0x0104, */
	.va_start_cmd = (DBMDX_REGV_TDM0_RX_EN |
			DBMDX_REGV_PROC_EN_SWITCH_FW_TO_DETECTION_MODE),
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	/* 0x0308 */
	.va_start_i2s_buffering_cmd = (DBMDX_REGV_TDM0_TX_EN |
					DBMDX_REGV_TDM0_RX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_BUFFERING_MODE),
#endif

	.send_va_ve_start_cmd = false,
};

/***********************************************************************/
/* Melon Barge IN Dual Mic Mono Usecase */
static struct usecase_config config_uc_melon_barge_in_2mic = {
#if defined(DBMDX_MELON_SRATE_48000)
	.usecase_name = "uc_melon_barge_in_2mic_48k",
#else
	.usecase_name = "uc_melon_barge_in_2mic_16k",
#endif
	.id	= (DBMDX_USECASE_ID_UC_IDX_04 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = true,
	.va_asrp_params_file_name = "asrp_params_melon_aecnr_dual_mic.bin",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = NULL,
	.change_clock_src = true,
#if defined(DBMDX_MELON_SRATE_48000)
	.tdm_clock_freq = TDM_CLK_FREQ_48,
#else
	.tdm_clock_freq = TDM_CLK_FREQ_16,
#endif
#ifdef AEC_REF_32_TO_16_BIT
	.number_of_bits = 32,
#else
	.number_of_bits = 16,
#endif
	.custom_d4_clock_hz = 98304000,
	.usecase_requires_amodel = true,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = true,
	.usecase_supports_us_buffering = true,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,

	.va_cfg_values = (u32 []){
		/* 0x80230000 */
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K |
			DBMDX_REGV_DDF_SAMPLE_WIDTH_16_BIT |
			DBMDX_REGV_FW_VAD_TYPE_NO_VAD),
		/* 0x8013fff0 */
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_STREAM_CH_1_CP_0),
		/* 0x80348044 */
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
#ifdef DBMDX_MELON_SRATE_48000
			DBMDX_REGV_EN_48_EC_REF_DECIM |
#endif
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_VT_CP0 |
			DBMDX_REGV_VT_PROC_EN |
			DBMDX_REGV_ALGO1_EN_FW_MODE_1_AND_MODE_2),
		(DBMDX_VA_USLEEP | 0x1500) },
	.num_of_va_cfg_values = 4,

	.config_mics = MIC_CONFIG_BY_USECASE,
	/* .mic_config = { 0x5276, 0xA261, 0x0000, 0x0000 }, */
	.mic_config = {
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO6_DM1_GPIO12 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO5_DM1_GPIO11 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_DM1),
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO8_DM1_GPIO14 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO9_DM1_GPIO13 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_RISING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_DDF0_DM0),
		 0x0000,
		 0x0000 },
	.num_of_va_ve_cfg_values = 0,
	.num_of_va_ve_post_tdm_cfg_values = 0,
	/* .audio_routing_config = { 0x0e10, 0x1eee, 0x22ee, 0x3eee,
	 *				0x4eee, 0x5ee0, 0x6eee, 0x7eee },
	 */
	.audio_routing_config = {
		(DBMDX_REGV_IO_SET_0 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_CP_1 |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_1 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_2 |
			DBMDX_REGV_IO_3N_2_CP_2 |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_3 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_4 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_5 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_6 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_7 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		DBMDX_UNDEFINED_REGISTER },

	.tdm_configs = {
		/* DBMD4 TDM0_RX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_RX,
			/* .tdm_reg_config = 16KHz: 0x112, 48KHz: 0x912*/
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#ifdef DBMDX_MELON_SRATE_48000
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
				DBMDX_REGV_RX_TX_I2S_CH_USE_HIGH_WORD_ONLY |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP2),

			.tdm_interface	= TDM_INTERFACE_VA,
#ifdef AEC_REF_32_TO_16_BIT
			.num_of_io_reg_configs = 4,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x0080405D
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00002064
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x103F003F
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.num_of_io_reg_configs = 3,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x00800015
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00000007
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x100F001F
				},
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
		/* DBMD4 TDM0_TX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_TX,
			/* .tdm_reg_config = 0x31F, */
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#if defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
		DBMDX_REGV_RX_TX_I2S_CH_SUM_HIGH_AND_LOW_INTO_ONE_SAMPLE |
#if defined(DBMDX_MELON_SRATE_48000) && defined(DBMDX_I2S_CATCHUP_SUPPORTED)
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#elif defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#else
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
#endif
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP3),

			.tdm_interface	= TDM_INTERFACE_VA,
			.num_of_io_reg_configs = 4,
#ifdef AEC_REF_32_TO_16_BIT
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00000064
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x101F003F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00241024
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x100F001F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x0000000F
				}
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */

	},
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	.num_of_tdm_configs = 2,
#else
	.num_of_tdm_configs = 1,
#endif
	.va_start_cmd_type = START_CMD_TYPE_TDM,
	.send_va_start_cmd = true,
	/* Enable:
	 *		TDM0_RX (HOST CODEC==>D4)
	 */
	/* .va_start_cmd = 0x0104, */
	.va_start_cmd = (DBMDX_REGV_TDM0_RX_EN |
			DBMDX_REGV_PROC_EN_SWITCH_FW_TO_DETECTION_MODE),
#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
	/* 0x0308 */
	.va_start_i2s_buffering_cmd = (DBMDX_REGV_TDM0_TX_EN |
					DBMDX_REGV_TDM0_RX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_BUFFERING_MODE),
#endif

	.send_va_ve_start_cmd = false,
};

#ifdef DBMDX_I2S_BUFFERING_SUPPORTED
static struct usecase_config config_uc_melon_ga_2mic_aec = {
#if defined(DBMDX_MELON_SRATE_48000)
	.usecase_name = "uc_melon_ga_2mic_aec_48k",
#else
	.usecase_name = "uc_melon_ga_2mic_aec_16k",
#endif
	.id	= (DBMDX_USECASE_ID_UC_IDX_06 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = true,
	.va_asrp_params_file_name = "asrp_params_melon_aecnr_dual_mic.bin",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = NULL,
	.change_clock_src = true,
#if defined(DBMDX_MELON_SRATE_48000)
	.tdm_clock_freq = TDM_CLK_FREQ_48,
#else
	.tdm_clock_freq = TDM_CLK_FREQ_16,
#endif
#ifdef AEC_REF_32_TO_16_BIT
	.number_of_bits = 32,
#else
	.number_of_bits = 16,
#endif
	.custom_d4_clock_hz = 98304000,//122880000,//
	.usecase_requires_amodel = false,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = false,
	.usecase_supports_us_buffering = true,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,
	.asrp_output_gain_type = (ASRP_TX_OUT_GAIN |
					ASRP_VCPF_OUT_GAIN |
					ASRP_RX_OUT_GAIN),

	.va_cfg_values = (u32 []){
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K |
			DBMDX_REGV_DDF_SAMPLE_WIDTH_16_BIT |
			DBMDX_REGV_FW_VAD_TYPE_NO_VAD),
		(DBMDX_REGN_ASRP_OUTPUT_ROUTING |
			DBMDX_REGV_ASRP_OUTPUT_SRC_AEC_1 |
			DBMDX_REGV_ASRP_OUTPUT_DEST_TX_1),
		(DBMDX_REGN_ASRP_OUTPUT_ROUTING |
			DBMDX_REGV_ASRP_OUTPUT_SRC_AEC_2 |
			DBMDX_REGV_ASRP_OUTPUT_DEST_TX_2),
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_NO_STREAM_CH_1),
#ifndef DBMDX_MIC_TYPE_DIGITAL
		(DBMDX_REGN_MICROPHONE_ANALOG_GAIN |
			DBMDX_REGN_ANALOG_GAIN_DBMD8D_COMBINED),
		(DBMDX_REGN_DIGITAL_GAIN |
			0),
#endif
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_ALGO1_EN_FW_MODE_1_ONLY),
		(DBMDX_VA_USLEEP | 0x1500) },
#ifndef DBMDX_MIC_TYPE_DIGITAL
		.num_of_va_cfg_values = 8,
#else
		.num_of_va_cfg_values = 6,
#endif

	.va_post_tdm_cfg_values = (u32 []){
		(DBMDX_REGN_AUDIO_ROUTING_CONFIG |
#if defined(DBMDX_MELON_SRATE_48000) && defined(AEC_REF_32_TO_16_BIT)
			DBMDX_REGV_TDM_SYNC_DELAY_6_CLKS_CYCLES |
#else
			DBMDX_REGV_TDM_SYNC_DELAY_4_CLKS_CYCLES |
#endif
			DBMDX_REGV_TDM_SYNC_RIGHT_CH |
			DBMDX_REGV_USE_TDM_MUSIC_TO_SYNC |
			DBMDX_REGV_MUSIC_IN_TDM0) },
	.num_of_va_post_tdm_cfg_values = 1,
	.usecase_supports_i2s_buffering = true,

	.config_mics = MIC_CONFIG_BY_USECASE,
	.mic_config = {
#ifdef DBMDX_MIC_TYPE_DIGITAL
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO8_DM1_GPIO14 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO9_DM1_GPIO13 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_DF0_DM0),
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO8_DM1_GPIO14 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO9_DM1_GPIO13 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_RISING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_DDF1_DM0),

#else
		(0x0800 | DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SAR_DDF_SAR_ADC),
		(DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_SD_ADC),
#endif
		 0x0000,
		 0x0000 },
	.num_of_va_ve_cfg_values = 0,
	.num_of_va_ve_post_tdm_cfg_values = 0,

	.audio_routing_config = {
		(DBMDX_REGV_IO_SET_0 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_CP_1 |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_1 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_2 |
			DBMDX_REGV_IO_3N_2_CP_2 |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_3 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_3),
		(DBMDX_REGV_IO_SET_4 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_5 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_CP_1 |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_6 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_7 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		DBMDX_UNDEFINED_REGISTER },

	.tdm_configs = {
		/* DBMD4 TDM0_RX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_RX,
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_ENABLE |
				DBMDX_REGV_NUM_OF_CHANNELS_2_CH |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
#ifdef DBMDX_MELON_SRATE_48000
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
#endif
				DBMDX_REGV_RX_TX_I2S_CH_USE_I2S_STEREO |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP2),

			.tdm_interface	= TDM_INTERFACE_VA,
#ifdef AEC_REF_32_TO_16_BIT
			.num_of_io_reg_configs = 4,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x0080405D
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00002064
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x103F003F
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.num_of_io_reg_configs = 3,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x00800015
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00000007
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x100F001F
				},
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
		/* DBMD4 TDM0_TX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_TX,
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_ENABLE |
				DBMDX_REGV_NUM_OF_CHANNELS_2_CH |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
#ifdef DBMDX_MELON_SRATE_48000
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
#endif
				DBMDX_REGV_RX_TX_I2S_CH_USE_I2S_STEREO |
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP0),

			.tdm_interface	= TDM_INTERFACE_VA,
			.num_of_io_reg_configs = 4,
#ifdef AEC_REF_32_TO_16_BIT
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00000064
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x101F003F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00241024
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x100F001F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x0000000F
				}
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
	},
	.num_of_tdm_configs = 2,
	.va_start_cmd_type = START_CMD_TYPE_TDM,
	.send_va_start_cmd = true,
	/* Enable:
	 *		TDM0_RX (HOST CODEC==>D4)
	 */
	.va_start_cmd = (DBMDX_REGV_TDM0_TX_EN |
			DBMDX_REGV_TDM0_RX_EN |
			DBMDX_REGV_PROC_EN_SWITCH_FW_TO_DETECTION_MODE),
	.va_start_i2s_buffering_cmd = (DBMDX_REGV_TDM0_TX_EN |
					DBMDX_REGV_TDM0_RX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_DETECTION_MODE),
	.send_va_ve_start_cmd = false,
};



/***********************************************************************/
/* Melon AEC 1Mic I2S Streaming Usecase */
static struct usecase_config config_uc_melon_aec_i2s_streaming_1mic = {
#if defined(DBMDX_MELON_SRATE_48000)
	.usecase_name = "uc_melon_aec_i2s_stream_1mic_48k",
#else
	.usecase_name = "uc_melon_aec_i2s_stream_1mic_16k",
#endif
	.id	= (DBMDX_USECASE_ID_UC_IDX_05 |
			DBMDX_USECASE_ID_PRJ_MELON |
			DBMDX_USECASE_ID_HWREV_00),
	.hw_rev = 0,
	.send_va_asrp_parms = true,
	.va_asrp_params_file_name = "asrp_params_melon_aecnr_single_mic.bin",
	.send_va_ve_asrp_parms = false,
	.va_ve_asrp_params_file_name = NULL,
	.change_clock_src = true,
#if defined(DBMDX_MELON_SRATE_48000)
	.tdm_clock_freq = TDM_CLK_FREQ_48,
#else
	.tdm_clock_freq = TDM_CLK_FREQ_16,
#endif
#ifdef AEC_REF_32_TO_16_BIT
	.number_of_bits = 32,
#else
	.number_of_bits = 16,
#endif
	.custom_d4_clock_hz = 55296000,
	.usecase_requires_amodel = false,
	.usecase_amodel_mode = 1,
	.usecase_sets_detection_mode = false,
	.usecase_supports_us_buffering = false,
	.va_chip_low_power_mode = false,
	.va_ve_chip_low_power_mode = false,

	.va_cfg_values = (u32 []){
		/* 0x80230000 */
		(DBMDX_REGN_GENERAL_CONFIG_2 |
			DBMDX_REGV_MIC_SAMPLE_RATE_16K |
			DBMDX_REGV_DDF_SAMPLE_WIDTH_16_BIT |
			DBMDX_REGV_FW_VAD_TYPE_NO_VAD),
		/* 0x8013fff0 */
		(DBMDX_REGN_AUDIO_STREAMING_SRC_SELECT |
			DBMDX_REGV_NO_STREAM_CH_4 |
			DBMDX_REGV_NO_STREAM_CH_3 |
			DBMDX_REGV_NO_STREAM_CH_2 |
			DBMDX_REGV_STREAM_CH_1_CP_0),
		/* 0x80348044 */
		(DBMDX_REGN_AUDIO_PROCESSING_CONFIG |
			DBMDX_REGV_EN_COPY_HIST |
			DBMDX_REGV_ALGO2_EN_FW_MODE_1_ONLY |
#ifdef DBMDX_MELON_SRATE_48000
			DBMDX_REGV_EN_48_EC_REF_DECIM |
#endif
			DBMDX_REGV_POST_DET_MODE_SWITCH_TO_STREAMING |
			DBMDX_REGV_VT_CP0 |
			DBMDX_REGV_VT_PROC_EN |
			DBMDX_REGV_ALGO1_EN_FW_MODE_1_AND_MODE_2),
		(DBMDX_VA_USLEEP | 0x1500) },
	.num_of_va_cfg_values = 4,

	.va_post_tdm_cfg_values = (u32 []){
		(DBMDX_REGN_AUDIO_ROUTING_CONFIG |
#if defined(DBMDX_MELON_SRATE_48000) && defined(AEC_REF_32_TO_16_BIT)
			/* 0x801F6400 */
			DBMDX_REGV_TDM_SYNC_DELAY_5_CLKS_CYCLES |
#else
			/* 0x801F4400 */
			DBMDX_REGV_TDM_SYNC_DELAY_4_CLKS_CYCLES |
#endif
			DBMDX_REGV_TDM_SYNC_RIGHT_CH |
			DBMDX_REGV_USE_TDM_MUSIC_TO_SYNC |
			DBMDX_REGV_MUSIC_IN_TDM0) },
	.num_of_va_post_tdm_cfg_values = 1,
	.usecase_supports_i2s_buffering = true,

	.config_mics = MIC_CONFIG_BY_USECASE,
	/* .mic_config = { 0x5276, 0x0000, 0x0000, 0x0000 }, */
	.mic_config = {
		(DBMDX_REGV_DM_CLOCK_SRC_DM0_GPIO6_DM1_GPIO12 |
		 DBMDX_REGV_DM_DATA_SRC_DM0_GPIO5_DM1_GPIO11 |
		 DBMDX_REGV_DDF_AUDIO_ATTENUATION_0dB |
		 DBMDX_REGV_DM_CLK_FREQ_1536_1200_SR_8KHz_16KHz_32KHz_48KHz |
		 DBMDX_REGV_CLOCK_POLARITY_FALLING_EDGE |
		 DBMDX_REGV_DDF_AND_DM_CONFIG_SD_DDF_DM1),
		 0x0000,
		 0x0000,
		 0x0000 },
	.num_of_va_ve_cfg_values = 0,
	.num_of_va_ve_post_tdm_cfg_values = 0,
	/* .audio_routing_config = { 0x0ee0, 0x1eee, 0x22ee, 0x3eee,
	 *				0x4eee, 0x5ee0, 0x6eee, 0x7eee },
	 */
	.audio_routing_config = {
		(DBMDX_REGV_IO_SET_0 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_1 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_2 |
			DBMDX_REGV_IO_3N_2_CP_2 |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_3 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_4 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_5 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_CP_0),
		(DBMDX_REGV_IO_SET_6 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		(DBMDX_REGV_IO_SET_7 |
			DBMDX_REGV_IO_3N_2_NO_CP |
			DBMDX_REGV_IO_3N_1_NO_CP |
			DBMDX_REGV_IO_3N_0_NO_CP),
		DBMDX_UNDEFINED_REGISTER },

	.tdm_configs = {
		/* DBMD4 TDM0_RX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_RX,
			/* .tdm_reg_config = 16KHz: 0x112, 48KHz: 0x912*/
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#ifdef DBMDX_MELON_SRATE_48000
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
				DBMDX_REGV_RX_TX_I2S_CH_USE_HIGH_WORD_ONLY |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP2),

			.tdm_interface	= TDM_INTERFACE_VA,
#ifdef AEC_REF_32_TO_16_BIT
			.num_of_io_reg_configs = 4,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x0080405D
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00002064
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x103F003F
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.num_of_io_reg_configs = 3,
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_RX_ADDR,
						.value = 0x00800015
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 4,
						.value = 0x00000007
				},
				{		.addr = DBMD4_TDM_0_RX_ADDR + 6,
						.value = 0x100F001F
				},
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},
		/* DBMD4 TDM0_TX is connected to Host Codec */
		{	.tdm_index	= 0x0,
			.tdm_type	= TDM_TYPE_TX,
			/* .tdm_reg_config = 0x31F, */
			.tdm_reg_config	=
				(DBMDX_REGV_DEMUX_MUX_DISABLE |
				DBMDX_REGV_SAMPLE_WIDTH_16_BIT |
				DBMDX_REGV_NUM_OF_CHANNELS_1_CH |
#if defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_48_KHz |
#else
				DBMDX_REGV_INPUT_OUTPUT_SAMPLE_RATE_16_KHz |
#endif
		DBMDX_REGV_RX_TX_I2S_CH_SUM_HIGH_AND_LOW_INTO_ONE_SAMPLE |
#if defined(DBMDX_MELON_SRATE_48000)
				DBMDX_REGV_RESAMPLE_RATIO_3_1 |
				DBMDX_REGV_RESAMPLE_TYPE_INTERPOLATION |
#else
				DBMDX_REGV_RESAMPLE_RATIO_NO_RESAMPLING |
				DBMDX_REGV_RESAMPLE_TYPE_DECIMATION |
#endif
				DBMDX_REGV_HW_BLOCK_EN |
				DBMDX_REGV_RX_TX_CP3),

			.tdm_interface	= TDM_INTERFACE_VA,
			.num_of_io_reg_configs = 4,
#ifdef AEC_REF_32_TO_16_BIT
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00000064
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x101F003F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x00000005
				}
			},
#else
			.io_reg_configs	= {
				{		.addr = DBMD4_TDM_0_TX_ADDR,
						.value = 0x00804053
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 4,
						.value = 0x00241024
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR + 6,
						.value = 0x100F001F
				},
				{		.addr = DBMD4_TDM_0_TX_ADDR+0xA,
						.value = 0x0000000F
				}
			},
#endif /* AEC_REF_32_TO_16_BIT */
		},

	},
	.num_of_tdm_configs = 2,
	.va_start_cmd_type = START_CMD_TYPE_TDM,
	.send_va_start_cmd = true,
	/* Enable:
	 *		TDM0_RX (HOST CODEC==>D4)
	 */
	/* .va_start_cmd = 0x0308, */
	.va_start_cmd = (DBMDX_REGV_TDM0_TX_EN |
					DBMDX_REGV_TDM0_RX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_BUFFERING_MODE),
	/* 0x0308 */
	.va_start_i2s_buffering_cmd = (DBMDX_REGV_TDM0_TX_EN |
					DBMDX_REGV_TDM0_RX_EN |
				DBMDX_REGV_PROC_EN_SWITCH_FW_TO_BUFFERING_MODE),

	.send_va_ve_start_cmd = false,
};
#endif /* DBMDX_I2S_BUFFERING_SUPPORTED */


#endif /* _DBMDX_USECASE_CONFIG_MELON_H */

#endif /* DBMDX_MELON_USECASES_SUPPORTED */
