/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Common DDR PHY trained CSR declarations for Diamond Technologies LPDDR4X timing variants.
 * The ddr_ddrphy_trained_csr array is defined in dec_lpddr4x_common.c and
 * is identical across all 1gbyte/2gbyte and 3200mts/3733mts configurations.
 */

#ifndef DEC_LPDDR4X_COMMON_H
#define DEC_LPDDR4X_COMMON_H

#include <asm/arch/ddr.h>

extern struct dram_cfg_param ddr_ddrphy_trained_csr[];
#define DDR_DDRPHY_TRAINED_CSR_NUM 976

#endif /* DEC_LPDDR4X_COMMON_H */
