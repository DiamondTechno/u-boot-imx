/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2025 Cargt Inc.
 *
 * Shared LPDDR4 2400 MT/s PHY table externs for all Diamond Technologies i.MX91 timing variants.
 */

#ifndef DEC_LPDDR4_TIMING_SHARED_H
#define DEC_LPDDR4_TIMING_SHARED_H

#include <linux/kernel.h>
#include <asm/arch/ddr.h>

extern struct dram_cfg_param ddr_phy_pie[];
#define DDR_PHY_PIE_NUM 559

extern struct dram_cfg_param ddr_ddrphy_cfg[];
#define DDR_DDRPHY_CFG_NUM 131

#endif /* DEC_LPDDR4_TIMING_SHARED_H */
