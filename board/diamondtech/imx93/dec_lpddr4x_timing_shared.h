/*
 * Shared LPDDR4X timing arrays (single-definition externs + counts)
 * Generated from optimized_timings_for_reference/dec_lpddr4x_timing_shared.h
 */
#ifndef DEC_LPDDR4X_TIMING_SHARED_H
#define DEC_LPDDR4X_TIMING_SHARED_H

#include <linux/kernel.h>
#include <asm/arch/ddr.h>

/* Single-definition arrays (defined in dec_lpddr4x_timing_shared.c) */
extern struct dram_cfg_param ddr_phy_pie[];
#define DDR_PHY_PIE_NUM 556

/* Backwards-compatible aliases for files that reference *_shared symbols */
#define ddr_phy_pie_shared ddr_phy_pie
#define DDR_PHY_PIE_SHARED_NUM DDR_PHY_PIE_NUM

extern struct dram_cfg_param ddr_fsp1_cfg[];
#define DDR_FSP1_CFG_NUM 34

#define ddr_fsp1_cfg_shared ddr_fsp1_cfg
#define DDR_FSP1_CFG_SHARED_NUM DDR_FSP1_CFG_NUM

extern struct dram_cfg_param ddr_fsp2_cfg[];
#define DDR_FSP2_CFG_NUM 34

#define ddr_fsp2_cfg_shared ddr_fsp2_cfg
#define DDR_FSP2_CFG_SHARED_NUM DDR_FSP2_CFG_NUM

extern struct dram_cfg_param ddr_fsp0_cfg[];
#define DDR_FSP0_CFG_NUM 34
#define ddr_fsp0_cfg_shared ddr_fsp0_cfg
#define DDR_FSP0_CFG_SHARED_NUM DDR_FSP0_CFG_NUM

extern struct dram_cfg_param ddr_fsp0_2d_cfg[];
#define DDR_FSP0_2D_CFG_NUM 34
#define ddr_fsp0_2d_cfg_shared ddr_fsp0_2d_cfg
#define DDR_FSP0_2D_CFG_SHARED_NUM DDR_FSP0_2D_CFG_NUM
/* Normalized macro aliases for all timing files */
#define DEC_LPDDR4X_FSP_CFG ddr_fsp1_cfg
#define DEC_LPDDR4X_FSP_CFG_NUM DDR_FSP1_CFG_NUM

#endif /* DEC_LPDDR4X_TIMING_SHARED_H */
