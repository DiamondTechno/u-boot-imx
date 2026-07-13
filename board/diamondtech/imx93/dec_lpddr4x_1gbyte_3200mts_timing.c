/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Code generated with DDR Tool v4.0.0_8.8-
 * DDR PHY FW2022.01
 * Part number: NXP LPDDR4X EVK and FRDM 11x11 board's default DDR part
 *
 * Optimized: shared arrays (ddr_phy_pie, fsp1/fsp2 message blocks) moved to
 * dec_lpddr4x_timing_shared.h; only variant-specific data remains here.
 */

#include <linux/kernel.h>
#include <asm/arch/ddr.h>
#include "dec_lpddr4x_timing_shared.h"
#include "dec_lpddr4x_3200mts_csr.h"

/* Initialize DDRC registers */
static struct dram_cfg_param ddr_ddrc_cfg[] = {
    {0x4e300110, 0x44100001},
    {0x4e300000, 0x8000bf},      /* 1GB: addrmap for 1 GByte */
    {0x4e300008, 0x0},
    {0x4e300080, 0x80000412},    /* 1GB: memory size encoding */
    {0x4e300084, 0x0},
    {0x4e300114, 0x1002},
    {0x4e300260, 0x80},
    {0x4e300f04, 0x80},
    {0x4e300800, 0x43b30002},
    {0x4e300804, 0x1f1f1f1f},
    {0x4e301000, 0x0},
    {0x4e301240, 0x0},
    {0x4e301244, 0x0},
    {0x4e301248, 0x0},
    {0x4e30124c, 0x0},
    {0x4e301250, 0x0},
    {0x4e301254, 0x0},
    {0x4e301258, 0x0},
    {0x4e30125c, 0x0},
};

/* dram fsp cfg */
static struct dram_fsp_cfg ddr_dram_fsp_cfg[] = {
    {
        {
            {0x4e300100, 0x145B311B},
            {0x4e300104, 0xDACC0017},
            {0x4e300108, 0xD4D68E00},
            {0x4e30010C, 0x0071E100},
            {0x4e300124, 0x18030000},
            {0x4e300160, 0x0000B101},
            {0x4e30016C, 0x33F00000},
            {0x4e300170, 0x8B0B0608},
            {0x4e300250, 0x00000022},
            {0x4e300254, 0x00D800D8},
            {0x4e300258, 0x00000008},
            {0x4e30025C, 0x00000400},
            {0x4e300300, 0x1D441D0D},
            {0x4e300304, 0x00D81E10},
            {0x4e300308, 0x0C3C0C03},
        },
        {
            {0x01, 0xD4},
            {0x02, 0x2D},
            {0x03, 0x32},
            {0x0b, 0x46},
            {0x0c, 0x11},
            {0x0e, 0x11},
            {0x16, 0x04},
        },
        0,
    },
    {
        {
            {0x4e300100, 0x124F2100},
            {0x4e300104, 0xDA77000E},
            {0x4e300108, 0x1816E4AA},
            {0x4e30010C, 0x005101E6},
            {0x4e300124, 0x0E030000},
            {0x4e300160, 0x0000B101},
            {0x4e30016C, 0x30900000},
            {0x4e300170, 0x8A0A0508},
            {0x4e300250, 0x00000014},
            {0x4e300254, 0x007B007B},
            {0x4e300258, 0x00000008},
            {0x4e30025C, 0x00000400},
        },
        {
            {0x01, 0xB4},
            {0x02, 0x1B},
            {0x03, 0x32},
            {0x0b, 0x46},
            {0x0c, 0x11},
            {0x0e, 0x11},
            {0x16, 0x04},
        },
        0,
    },
    {
        {
            {0x4e300100, 0x00051000},
            {0x4e300104, 0xDA55000A},
            {0x4e300108, 0x6E620A48},
            {0x4e30010C, 0x0031010D},
            {0x4e300124, 0x04830000},
            {0x4e300160, 0x0000B100},
            {0x4e30016C, 0x30000000},
            {0x4e300170, 0x89090408},
            {0x4e300250, 0x00000007},
            {0x4e300254, 0x00240024},  /* 1GB specific */
            {0x4e300258, 0x00000008},
            {0x4e30025C, 0x00000400},
        },
        {
            {0x01, 0x94},
            {0x02, 0x9},
            {0x03, 0x32},
            {0x0b, 0x46},
            {0x0c, 0x11},
            {0x0e, 0x11},
            {0x16, 0x04},
        },
        1,
    },
};


/* PHY Initialize Configuration
 * All entries are shared with 3200mts variants except {0x20008}.
 */
static struct dram_cfg_param ddr_ddrphy_cfg[] = {
#include "include/ddrphy_cfg_1g_3200_elements.inc"
};

/* PHY PIE for 1GB 3200MT/s */
static struct dram_cfg_param ddr_phy_pie_1g_3200[] = {
#include "include/phy_pie_1g_3200_elements.inc"
};

/* Local 2D FSP array for 1GB 3200MT/s */
static struct dram_cfg_param ddr_fsp0_2d_cfg_1g_3200[] = {
#include "include/fsp0_2d_cfg_1g_3200_elements.inc"
};

/* P0 1D message block for 1GB 3200MT/s (variant-specific: rate=3200) */
static struct dram_cfg_param ddr_fsp0_cfg_1g_3200[] = {
    {0xd0000, 0x0},
    {0x54003, 0xc80},
    {0x54004, 0x4},
    {0x54006, 0x15},
    {0x54008, 0x131f},
    {0x54009, 0xc8},
    {0x5400b, 0x4},
    {0x5400d, 0x100},
    {0x5400f, 0x100},
    {0x54012, 0x110},
    {0x54019, 0x2dd4},
    {0x5401a, 0x32},
    {0x5401b, 0x1146},
    {0x5401c, 0x1108},
    {0x5401e, 0x4},
    {0x5401f, 0x2dd4},
    {0x54020, 0x32},
    {0x54021, 0x1146},
    {0x54022, 0x1108},
    {0x54024, 0x4},
    {0x54032, 0xd400},
    {0x54033, 0x322d},
    {0x54034, 0x4600},
    {0x54035, 0x811},
    {0x54036, 0x11},
    {0x54037, 0x400},
    {0x54038, 0xd400},
    {0x54039, 0x322d},
    {0x5403a, 0x4600},
    {0x5403b, 0x811},
    {0x5403c, 0x11},
    {0x5403d, 0x400},
    {0xd0000, 0x1}
};

static struct dram_fsp_msg ddr_dram_fsp_msg[] = {
    {
        /* P0 3200mts 1D */
        .drate = 3200,
        .fw_type = FW_1D_IMAGE,
        .fsp_cfg = ddr_fsp0_cfg_1g_3200,
        .fsp_cfg_num = ARRAY_SIZE(ddr_fsp0_cfg_1g_3200),
    },
    {
        /* P1 1866mts 1D */
        .drate = 1866,
        .fw_type = FW_1D_IMAGE,
        .fsp_cfg = ddr_fsp1_cfg,
        .fsp_cfg_num = DDR_FSP1_CFG_NUM,
    },
    {
        /* P2 625mts 1D */
        .drate = 625,
        .fw_type = FW_1D_IMAGE,
        .fsp_cfg = ddr_fsp2_cfg,
        .fsp_cfg_num = DDR_FSP2_CFG_NUM,
    },
    {
        /* P0 3200mts 2D */
        .drate = 3200,
        .fw_type = FW_2D_IMAGE,
        .fsp_cfg = ddr_fsp0_2d_cfg_1g_3200,
        .fsp_cfg_num = ARRAY_SIZE(ddr_fsp0_2d_cfg_1g_3200),
    },
};

/* ddr timing config params */
struct dram_timing_info dec_lpddr4x_1gbyte_3200mts_timing = {
    .ddrc_cfg = ddr_ddrc_cfg,
    .ddrc_cfg_num = ARRAY_SIZE(ddr_ddrc_cfg),
    .ddrphy_cfg = ddr_ddrphy_cfg,
    .ddrphy_cfg_num = ARRAY_SIZE(ddr_ddrphy_cfg),
    .fsp_msg = ddr_dram_fsp_msg,
    .fsp_msg_num = ARRAY_SIZE(ddr_dram_fsp_msg),
    .ddrphy_trained_csr = ddr_lpddr4x_3200mts_trained_csr,
    .ddrphy_trained_csr_num = DDR_LPDDR4X_3200MTS_TRAINED_CSR_NUM,
    .ddrphy_pie = ddr_phy_pie_1g_3200,
    .ddrphy_pie_num = ARRAY_SIZE(ddr_phy_pie_1g_3200),
    .fsp_table = { 3200, 1866, 625, },
    .fsp_cfg = ddr_dram_fsp_cfg,
    .fsp_cfg_num = ARRAY_SIZE(ddr_dram_fsp_cfg),
};
