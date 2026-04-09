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

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-y += lpddr4x_1gbyte_timing.o lpddr4x_2gbyte_timing.o
endif
