#
# Copyright 2022 NXP
# Copyright 2026 Diamond Technologies, Inc.
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += imx93_dec.o
obj-$(CONFIG_TARGET_IMX93_DEC) += imx9_eeprom.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_USB_TCPC) += ../../freescale/common/tcpc.o
obj-y += ../../freescale/common/mmc.o
endif

obj-y += dec_lpddr4x_timing_shared.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-y += dec_lpddr4x_common.o

obj-y += dec_lpddr4x_512mb_3200mts_timing.o
obj-y += dec_lpddr4x_1gbyte_3200mts_timing.o
obj-y += dec_lpddr4x_2gbyte_3200mts_timing.o

obj-y += dec_lpddr4x_512mb_3733mts_timing.o
obj-y += dec_lpddr4x_1gbyte_3733mts_timing.o
obj-y += dec_lpddr4x_2gbyte_3733mts_timing.o

obj-y += dec_lpddr4x_3200mts_csr.o
obj-y += dec_lpddr4x_3733mts_csr.o
endif
