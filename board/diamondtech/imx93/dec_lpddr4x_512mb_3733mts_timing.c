// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022-2026 NXP
 *
 * LPDDR4X 512MByte 3733MTs rank1 timing configuration
 * Generated from DDR Tool v4.0.0_8.8-, DDR PHY FW2022.01
 */

#include <linux/kernel.h>
#include <asm/arch/ddr.h>
#include "dec_lpddr4x_timing_shared.h"
#include "dec_lpddr4x_3733mts_csr.h"

/* Initialize DDRC registers */
static struct dram_cfg_param ddr_ddrc_cfg[] = {
#include "include/ddrc_cfg_512mb_3733_elements.inc"
};

/* P0 FSP message block (3733 MT/s 1D training) */
static struct dram_cfg_param ddr_fsp0_cfg_512mb_3733[] = {
#include "include/fsp0_cfg_512mb_3733_elements.inc"
};

/* P1 FSP message block (1866 MT/s 1D training) */
static struct dram_cfg_param ddr_fsp1_cfg_512mb_3733[] = {
#include "include/fsp1_cfg_512mb_3733_elements.inc"
};

/* P2 FSP message block (625 MT/s 1D training) */
static struct dram_cfg_param ddr_fsp2_cfg_512mb_3733[] = {
#include "include/fsp2_cfg_512mb_3733_elements.inc"
};

/* P0 2D FSP message block */
static struct dram_cfg_param ddr_fsp0_2d_cfg_512mb_3733[] = {
#include "include/fsp0_2d_cfg_512mb_3733_elements.inc"
};

/* PHY init engine (PIE) program */
static struct dram_cfg_param ddr_phy_pie_512mb_3733[] = {
#include "include/phy_pie_512mb_3733_elements.inc"
};

/* PHY initialization configuration */
static struct dram_cfg_param ddr_ddrphy_cfg[] = {
#include "include/ddrphy_cfg_512mb_3733_elements.inc"
};

/* Per-FSP DDRC configuration */
static struct dram_fsp_cfg ddr_dram_fsp_cfg[] = {
#include "include/dram_fsp_cfg_512mb_3733_elements.inc"
};

static struct dram_fsp_msg ddr_dram_fsp_msg[] = {
	{
		/* P0 3733 MT/s 1D */
		.drate = 3733,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = ddr_fsp0_cfg_512mb_3733,
		.fsp_cfg_num = ARRAY_SIZE(ddr_fsp0_cfg_512mb_3733),
	},
	{
		/* P1 1866 MT/s 1D */
		.drate = 1866,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = ddr_fsp1_cfg_512mb_3733,
		.fsp_cfg_num = ARRAY_SIZE(ddr_fsp1_cfg_512mb_3733),
	},
	{
		/* P2 625 MT/s 1D */
		.drate = 625,
		.fw_type = FW_1D_IMAGE,
		.fsp_cfg = ddr_fsp2_cfg_512mb_3733,
		.fsp_cfg_num = ARRAY_SIZE(ddr_fsp2_cfg_512mb_3733),
	},
	{
		/* P0 3733 MT/s 2D */
		.drate = 3733,
		.fw_type = FW_2D_IMAGE,
		.fsp_cfg = ddr_fsp0_2d_cfg_512mb_3733,
		.fsp_cfg_num = ARRAY_SIZE(ddr_fsp0_2d_cfg_512mb_3733),
	},
};

/* ddr timing config params */
struct dram_timing_info dec_lpddr4x_512mb_3733mts_timing = {
	.ddrc_cfg		= ddr_ddrc_cfg,
	.ddrc_cfg_num		= ARRAY_SIZE(ddr_ddrc_cfg),
	.ddrphy_cfg		= ddr_ddrphy_cfg,
	.ddrphy_cfg_num		= ARRAY_SIZE(ddr_ddrphy_cfg),
	.fsp_msg		= ddr_dram_fsp_msg,
	.fsp_msg_num		= ARRAY_SIZE(ddr_dram_fsp_msg),
	.ddrphy_trained_csr	= ddr_lpddr4x_3733mts_trained_csr,
	.ddrphy_trained_csr_num	= DDR_LPDDR4X_3733MTS_TRAINED_CSR_NUM,
	.ddrphy_pie		= ddr_phy_pie_512mb_3733,
	.ddrphy_pie_num		= ARRAY_SIZE(ddr_phy_pie_512mb_3733),
	.fsp_table		= { 3733, 1866, 625, },
	.fsp_cfg		= ddr_dram_fsp_cfg,
	.fsp_cfg_num		= ARRAY_SIZE(ddr_dram_fsp_cfg),
};
