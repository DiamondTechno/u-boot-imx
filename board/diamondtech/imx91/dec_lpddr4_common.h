/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2025 Cargt Inc.
 *
 * Common DDR PHY trained CSR declarations for Diamond Technologies i.MX91 LPDDR4 timing variants.
 */

#ifndef DEC_LPDDR4_COMMON_H
#define DEC_LPDDR4_COMMON_H

#include <asm/arch/ddr.h>

extern struct dram_cfg_param ddr_ddrphy_trained_csr[];
#define DDR_DDRPHY_TRAINED_CSR_NUM 976

#endif /* DEC_LPDDR4_COMMON_H */
