#
# Copyright 2022 NXP
# Copyright 2026 Diamond Technologies, Inc.
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += imx91_dec.o
obj-$(CONFIG_TARGET_IMX91_DEC) += ../imx93/imx9_eeprom.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_USB_TCPC) += ../../freescale/common/tcpc.o
obj-y += ../../freescale/common/mmc.o
endif

obj-y += dec_lpddr4_timing_shared.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-y += dec_lpddr4_common.o

obj-y += dec_lpddr4_512mb_2400mts_timing.o
obj-y += dec_lpddr4_512mb_2400mts_caodt120_timing.o
obj-y += dec_lpddr4_512mb_1600mts_timing.o
obj-y += dec_lpddr4_1gbyte_2400mts_timing.o
obj-y += dec_lpddr4_2gbyte_2400mts_timing.o
obj-y += dec_lpddr4_2gbyte_2400mts_rank2_timing.o
endif
