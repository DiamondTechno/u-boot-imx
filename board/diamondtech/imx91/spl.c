// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2022 NXP
 * Copyright 2026 Diamond Technologies, Inc.
 */

#include <common.h>
#include <command.h>
#include <cpu_func.h>
#include <hang.h>
#include <image.h>
#include <init.h>
#include <log.h>
#include <spl.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <asm/arch/imx91_pins.h>
#include <asm/arch/mu.h>
#include <asm/arch/clock.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/mach-imx/mxc_i2c.h>
#include <asm/arch-mx7ulp/gpio.h>
#include <asm/mach-imx/ele_api.h>
#include <asm/mach-imx/syscounter.h>
#include <asm/sections.h>
#include <dm/uclass.h>
#include <ctype.h>
#include <dm/device.h>
#include <dm/uclass-internal.h>
#include <dm/device-internal.h>
#include <linux/delay.h>
#include <asm/arch/clock.h>
#include <asm/arch/ccm_regs.h>
#include <asm/arch/ddr.h>
#include <power/pmic.h>
#include <power/pca9450.h>
#include <asm/arch/trdc.h>
#include "../imx93/imx9_eeprom.h"

DECLARE_GLOBAL_DATA_PTR;

static struct dec_eeprom eeprom = {0};

int spl_board_boot_device(enum boot_device boot_dev_spl)
{
#ifdef CONFIG_SPL_BOOTROM_SUPPORT
	return BOOT_DEVICE_BOOTROM;
#else
	switch (boot_dev_spl) {
	case SD1_BOOT:
	case MMC1_BOOT:
		return BOOT_DEVICE_MMC1;
	case SD2_BOOT:
	case MMC2_BOOT:
		return BOOT_DEVICE_MMC2;
	default:
		return BOOT_DEVICE_NONE;
	}
#endif
}

void spl_board_init(void)
{
	struct dec_eeprom *ep = DEC_EEPROM_DATA;
	int ret;

	ret = ele_start_rng();
	if (ret)
		printf("Fail to start RNG: %d\n", ret);

	/* Copy EEPROM contents to DRAM */
	memcpy(ep, &eeprom, sizeof(*ep));
}

extern struct dram_timing_info dec_lpddr4_512mb_2400mts_timing;
extern struct dram_timing_info dec_lpddr4_512mb_2400mts_caodt120_timing;
extern struct dram_timing_info dec_lpddr4_512mb_1600mts_timing;
extern struct dram_timing_info dec_lpddr4_1gbyte_2400mts_timing;
extern struct dram_timing_info dec_lpddr4_2gbyte_2400mts_timing;
extern struct dram_timing_info dec_lpddr4_2gbyte_2400mts_rank2_timing;

/* Failsafe DRAM config, selected via Kconfig */
#if IS_ENABLED(CONFIG_DEC_IMX91_FAILSAFE_DRAM_2GB_RANK2)
# define FAILSAFE_DRAM_SIZE_MB	2048
# define FAILSAFE_DRAM_RANK	2
# define FAILSAFE_DRAM_RATE_MTS	2400
# define failsafe_dram_timing	dec_lpddr4_2gbyte_2400mts_rank2_timing
#elif IS_ENABLED(CONFIG_DEC_IMX91_FAILSAFE_DRAM_512MB_1600MTS)
# define FAILSAFE_DRAM_SIZE_MB	512
# define FAILSAFE_DRAM_RANK	1
# define FAILSAFE_DRAM_RATE_MTS	1600
# define failsafe_dram_timing	dec_lpddr4_512mb_1600mts_timing
#elif IS_ENABLED(CONFIG_DEC_IMX91_FAILSAFE_DRAM_512MB_RANK1)
# define FAILSAFE_DRAM_SIZE_MB	512
# define FAILSAFE_DRAM_RANK	1
# define FAILSAFE_DRAM_RATE_MTS	2400
# define failsafe_dram_timing	dec_lpddr4_512mb_2400mts_timing
#elif IS_ENABLED(CONFIG_DEC_IMX91_FAILSAFE_DRAM_512MB_RANK1_CAODT120)
# define FAILSAFE_DRAM_SIZE_MB	512
# define FAILSAFE_DRAM_RANK	1
# define FAILSAFE_DRAM_RATE_MTS	2400
# define failsafe_dram_timing	dec_lpddr4_512mb_2400mts_caodt120_timing
#else
# error "No DEC_IMX91_FAILSAFE_DRAM_* option selected"
#endif

/*
 * Pick a timing set for the DRAM fitted to this SOM. The i.MX91 SOM only
 * uses LPDDR4 at 2400 MT/s, so speed is not a selection criterion; 2GB
 * parts ship as both single- and dual-rank, each with its own table.
 */
static struct dram_timing_info *select_dram_timing(uint16_t size_mbytes,
						   uint8_t rank)
{
	switch (size_mbytes) {
	case 2048:
		if (rank == 2)
			return &dec_lpddr4_2gbyte_2400mts_rank2_timing;
		return &dec_lpddr4_2gbyte_2400mts_timing;

	case 1024:
		return &dec_lpddr4_1gbyte_2400mts_timing;

	case 512:
		return &dec_lpddr4_512mb_2400mts_timing;

	default:
		printf("Unsupported DRAM size %u MB, using failsafe %u MB/rank%u\n",
		       size_mbytes, FAILSAFE_DRAM_SIZE_MB, FAILSAFE_DRAM_RANK);
		return &failsafe_dram_timing;
	}
}

void spl_dram_init(void)
{
	struct dram_timing_info *ptiming = &failsafe_dram_timing;
	uint16_t dram_size_mbytes = FAILSAFE_DRAM_SIZE_MB;
	uint8_t dram_rank = FAILSAFE_DRAM_RANK;
	bool use_failsafe = false;

#if IS_ENABLED(CONFIG_DEC_IMX91_LPDDR4_TIMING_BY_EEPROM)
	printf("Reading EEPROM over I2C...\n");
	dec_eeprom_read(&eeprom);
	printf("EEPROM read complete.\n");

	if (!dec_eeprom_is_valid(&eeprom)) {
		printf("WARNING: EEPROM blank or invalid magic - using failsafe timing %uMB/%u/rank%u\n",
		       FAILSAFE_DRAM_SIZE_MB, FAILSAFE_DRAM_RATE_MTS, FAILSAFE_DRAM_RANK);
		printf("         Program EEPROM with correct DDR parameters after boot.\n");
		use_failsafe = true;
	} else {
		dec_eeprom_print_prod_info(&eeprom);
		dram_size_mbytes = dec_eeprom_get_dram_size_mb(&eeprom);
		dram_rank        = dec_eeprom_get_dram_rank(&eeprom);
	}

#if CONFIG_DEC_IMX91_MIN_SDRAM_SIZE_MB > 0
	if (dram_size_mbytes < CONFIG_DEC_IMX91_MIN_SDRAM_SIZE_MB) {
		printf("WARNING: DRAM %u MB < minimum %u MB, loading failsafe %uMB/%u/rank%u\n",
		       dram_size_mbytes, CONFIG_DEC_IMX91_MIN_SDRAM_SIZE_MB,
		       FAILSAFE_DRAM_SIZE_MB, FAILSAFE_DRAM_RATE_MTS, FAILSAFE_DRAM_RANK);
		dram_size_mbytes = FAILSAFE_DRAM_SIZE_MB;
		dram_rank        = FAILSAFE_DRAM_RANK;
		use_failsafe     = true;
	}
#endif

	if (!use_failsafe)
		ptiming = select_dram_timing(dram_size_mbytes, dram_rank);

	printf("\tSelected board timing: %uMB (rank %u)\r\n",
	       dram_size_mbytes, dram_rank);
#endif /* CONFIG_DEC_IMX91_LPDDR4_TIMING_BY_EEPROM */

	printf("DDR: %uMTS\n", ptiming->fsp_msg[0].drate);
	ddr_init(ptiming);
}

#if CONFIG_IS_ENABLED(DM_PMIC_PCA9450)
int power_init_board(void)
{
	struct udevice *dev;
	int ret;
	unsigned int val = 0, buck_val;

	ret = pmic_get("pmic@25", &dev);
	if (ret != 0) {
		puts("ERROR: Get PMIC PCA9451A failed!\n");
		return ret;
	}
	puts("PMIC: PCA9451A\n");
	/* BUCKxOUT_DVS0/1 control BUCK123 output */
	pmic_reg_write(dev, PCA9450_BUCK123_DVS, 0x29);

	/* enable DVS control through PMIC_STBY_REQ */
	pmic_reg_write(dev, PCA9450_BUCK1CTRL, 0x59);

	ret = pmic_reg_read(dev, PCA9450_PWR_CTRL);
	if (ret < 0)
		return ret;
	else
		val = ret;

	if (is_voltage_mode(VOLT_LOW_DRIVE)) {
		buck_val = 0x0c; /* 0.8v for Low drive mode */
		printf("PMIC: Low Drive Voltage Mode\n");
	} else if (is_voltage_mode(VOLT_NOMINAL_DRIVE)) {
		buck_val = 0x10; /* 0.85v for Nominal drive mode */
		printf("PMIC: Nominal Voltage Mode\n");
	} else {
		buck_val = 0x14; /* 0.9v for Over drive mode */
		printf("PMIC: Over Drive Voltage Mode\n");
	}

	if (val & PCA9450_REG_PWRCTRL_TOFF_DEB) {
		pmic_reg_write(dev, PCA9450_BUCK1OUT_DVS0, buck_val);
		pmic_reg_write(dev, PCA9450_BUCK3OUT_DVS0, buck_val);
	} else {
		pmic_reg_write(dev, PCA9450_BUCK1OUT_DVS0, buck_val + 0x4);
		pmic_reg_write(dev, PCA9450_BUCK3OUT_DVS0, buck_val + 0x4);
	}

	/* The i.MX91 SOM uses LPDDR4: set VDDQ to 1.1V from buck2 */
	pmic_reg_write(dev, PCA9450_BUCK2OUT_DVS0, 0x28);

	/* set standby voltage to 0.65v */
	if (val & PCA9450_REG_PWRCTRL_TOFF_DEB)
		pmic_reg_write(dev, PCA9450_BUCK1OUT_DVS1, 0x0);
	else
		pmic_reg_write(dev, PCA9450_BUCK1OUT_DVS1, 0x4);

	/* I2C_LT_EN*/
	pmic_reg_write(dev, 0xa, 0x3);
	return 0;
}
#endif

void board_init_f(ulong dummy)
{
	int ret;

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	timer_init();

	arch_cpu_init();

	board_early_init_f();

	spl_early_init();

	preloader_console_init();

	ret = imx9_probe_mu();
	if (ret) {
		printf("Fail to init ELE API\n");
	} else {
		printf("SOC: 0x%x\n", gd->arch.soc_rev);
		printf("LC: 0x%x\n", gd->arch.lifecycle);
	}

	clock_init_late();

	power_init_board();

	if (!is_voltage_mode(VOLT_LOW_DRIVE))
		set_arm_core_max_clk();

	/* Init power of mix */
	soc_power_init();

	/* Setup TRDC for DDR access */
	trdc_init();

	/* DDR initialization */
	spl_dram_init();

	board_init_r(NULL, 0);
}

#ifdef CONFIG_ANDROID_SUPPORT
int board_get_emmc_id(void) {
	return 0;
}
#endif
