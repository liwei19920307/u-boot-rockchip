/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 Rockchip Electronics Co. Ltd.
 * Author:
 * 	Elaine Zhang <zhangqing@rock-chips.com>
 *	Finley Xiao <finley.xiao@rock-chips.com>
 */

#ifndef _ASM_ARCH_CRU_RK3562_H
#define _ASM_ARCH_CRU_RK3562_H

#define MHz		1000000
#define KHz		1000
#define OSC_HZ		(24 * MHz)

#define CPU_PVTPLL_HZ	(1008 * MHz)
#define APLL_HZ		(600 * MHz)
#define GPLL_HZ		(1188 * MHz)
#define CPLL_HZ		(1000 * MHz)
#define HPLL_HZ		(1000 * MHz)

/* RK3562 pll id */
enum rk3562_pll_id {
	APLL,
	GPLL,
	VPLL,
	HPLL,
	CPLL,
	DPLL,
	PLL_COUNT,
};

struct rk3562_clk_info {
	unsigned long id;
	char *name;
};

struct rk3562_clk_priv {
	struct rk3562_cru *cru;
	ulong gpll_hz;
	ulong vpll_hz;
	ulong hpll_hz;
	ulong cpll_hz;
	ulong armclk_hz;
	ulong armclk_enter_hz;
	ulong armclk_init_hz;
	bool sync_kernel;
	bool set_armclk_rate;
};

struct rk3562_cru {
	/* top cru */
	uint32_t apll_con[5];
	uint32_t reserved0014[19];
	uint32_t gpll_con[5];
	uint32_t reserved0074[3];
	uint32_t vpll_con[5];
	uint32_t reserved0094[3];
	uint32_t hpll_con[5];
	uint32_t reserved00b4[19];
	uint32_t clksel_con[48];
	uint32_t reserved01c0[80];
	uint32_t gate_con[28];
	uint32_t reserved370[36];
	uint32_t softrst_con[28];
	uint32_t reserved0470[100];
	uint32_t mode_con[1];
	uint32_t reserved0604[3];
	uint32_t glb_cnt_th;
	uint32_t glb_srst_fst;
	uint32_t glb_srst_snd;
	uint32_t glb_rst_con;
	uint32_t glb_rst_st;
	unsigned int sdmmc0_con[2];
	unsigned int sdmmc1_con[2];
	uint32_t reserved0634[2];
	unsigned int emmc_con[1];
	uint32_t reserved0640[15984];

	/* pmu0 cru */
	uint32_t reserved10000[64];
	uint32_t pmu0clksel_con[4];
	uint32_t reserved10110[28];
	uint32_t pmu0gate_con[3];
	uint32_t reserved1018c[29];
	uint32_t pmu0softrst_con[3];
	uint32_t reserved1020c[8061];

	/* pmu1 cru */
	uint32_t reserved18000[16];
	uint32_t cpll_con[5];
	uint32_t reserved18054[43];
	uint32_t pmu1clksel_con[7];
	uint32_t reserved1811c[25];
	uint32_t pmu1gate_con[4];
	uint32_t reserved18190[28];
	uint32_t pmu1softrst_con[3];
	uint32_t reserved1820c[93];
	uint32_t pmu1mode_con[1];
	uint32_t reserved18384[7967];

	/* ddr cru */
	uint32_t reserved20000[64];
	uint32_t ddrclksel_con[2];
	uint32_t reserved20108[30];
	uint32_t ddrgate_con[2];
	uint32_t reserved20188[30];
	uint32_t ddrsoftrst_con[2];
	uint32_t reserved20208[8062];

	/* subddr cru */
	uint32_t reserved28000[8];
	uint32_t dpll_con[5];
	uint32_t reserved28034[51];
	uint32_t sudbddrclksel_con[1];
	uint32_t reserved28104[31];
	uint32_t subddrgate_con[1];
	uint32_t reserved28184[31];
	uint32_t sudbddrsoftrst_con[1];
	uint32_t reserved28204[95];
	uint32_t subddrmode_con[1];
	uint32_t reserved28384[7967];

	/* peri cru */
	uint32_t reserved30000[64];
	uint32_t periclksel_con[48];
	uint32_t reserved301c0[80];
	uint32_t perigate_con[18];
	uint32_t reserved30348[46];
	uint32_t perisoftrst_con[18];
	uint32_t reserved30448[143];
};
check_member(rk3562_cru, reserved0640[0], 0x00640);
check_member(rk3562_cru, reserved1020c[0], 0x1020c);
check_member(rk3562_cru, reserved18384[0], 0x18384);
check_member(rk3562_cru, reserved20208[0], 0x20208);
check_member(rk3562_cru, reserved28384[0], 0x28384);
check_member(rk3562_cru, reserved30448[0], 0x30448);

struct pll_rate_table {
	unsigned long rate;
	unsigned int fbdiv;
	unsigned int postdiv1;
	unsigned int refdiv;
	unsigned int postdiv2;
	unsigned int dsmpd;
	unsigned int frac;
};

#define RK3562_PMU0_CRU_BASE		0x10000
#define RK3562_PMU1_CRU_BASE		0x18000
#define RK3562_DDR_CRU_BASE		0x20000
#define RK3562_SUBDDR_CRU_BASE		0x28000
#define RK3562_PERI_CRU_BASE		0x30000

#define RK3562_PLL_CON(x)		((x) * 0x4)
#define RK3562_PMU1_PLL_CON(x)		((x) * 0x4 + RK3562_PMU1_CRU_BASE + 0x40)
#define RK3562_SUBDDR_PLL_CON(x)	((x) * 0x4 + RK3562_SUBDDR_CRU_BASE + 0x20)
#define RK3562_MODE_CON			0x600
#define RK3562_PMU1_MODE_CON		(RK3562_PMU1_CRU_BASE + 0x380)
#define RK3562_SUBDDR_MODE_CON		(RK3562_SUBDDR_CRU_BASE + 0x380)
#define RK3562_GLB_SRST_FST		0x614
#define RK3562_GLB_SRST_SND		0x618
#define RK3562_GLB_RST_CON		0x61c
#define RK3562_GLB_RST_ST		0x620

enum {
	/* CRU_CLKSEL_CON10 */
	CLK_CORE_PRE_DIV_SHIFT		= 0,
	CLK_CORE_PRE_DIV_MASK		= 0x1f << CLK_CORE_PRE_DIV_SHIFT,

	/* CRU_CLKSEL_CON11 */
	ACLK_CORE_PRE_DIV_SHIFT		= 0,
	ACLK_CORE_PRE_DIV_MASK		= 0x7 << ACLK_CORE_PRE_DIV_SHIFT,
	CLK_SCANHS_ACLKM_CORE_DIV_SHIFT	= 8,
	CLK_SCANHS_ACLKM_CORE_DIV_MASK	= 0x7 << CLK_SCANHS_ACLKM_CORE_DIV_SHIFT,

	/* CRU_CLKSEL_CON12 */
	PCLK_DBG_PRE_DIV_SHIFT		= 0,
	PCLK_DBG_PRE_DIV_MASK		= 0xf << PCLK_DBG_PRE_DIV_SHIFT,
	CLK_SCANHS_PCLK_DBG_DIV_SHIFT	= 8,
	CLK_SCANHS_PCLK_DBG_DIV_MASK	= 0xf << CLK_SCANHS_PCLK_DBG_DIV_SHIFT,

	/* CRU_CLKSEL_CON28 */
	ACLK_VOP_DIV_SHIFT		= 0,
	ACLK_VOP_DIV_MASK		= 0x1f << ACLK_VOP_DIV_SHIFT,
	ACLK_VOP_SEL_SHIFT		= 6,
	ACLK_VOP_SEL_MASK		= 0x3 << ACLK_VOP_SEL_SHIFT,
	ACLK_VOP_SEL_GPLL		= 0,
	ACLK_VOP_SEL_CPLL,
	ACLK_VOP_SEL_VPLL,
	ACLK_VOP_SEL_HPLL,

	/* CRU_CLKSEL_CON30 */
	DCLK_VOP_DIV_SHIFT		= 0,
	DCLK_VOP_DIV_MASK		= 0xff << DCLK_VOP_DIV_SHIFT,
	DCLK_VOP_SEL_SHIFT		= 14,
	DCLK_VOP_SEL_MASK		= 0x3 << DCLK_VOP_SEL_SHIFT,
	DCLK_VOP_SEL_GPLL		= 0,
	DCLK_VOP_SEL_HPLL,
	DCLK_VOP_SEL_VPLL,
	DCLK_VOP_SEL_APLL,

	/* CRU_CLKSEL_CON31 */
	DCLK_VOP1_DIV_SHIFT		= 0,
	DCLK_VOP1_DIV_MASK		= 0xff << DCLK_VOP1_DIV_SHIFT,
	DCLK_VOP1_SEL_SHIFT		= 14,
	DCLK_VOP1_SEL_MASK		= 0x3 << DCLK_VOP1_SEL_SHIFT,

	/* CRU_CLKSEL_CON40 */
	ACLK_BUS_DIV_SHIFT		= 0,
	ACLK_BUS_DIV_MASK		= 0x1f << ACLK_BUS_DIV_SHIFT,
	ACLK_BUS_SEL_SHIFT		= 7,
	ACLK_BUS_SEL_MASK		= 0x1 << ACLK_BUS_SEL_SHIFT,
	ACLK_BUS_SEL_GPLL		= 0,
	ACLK_BUS_SEL_CPLL,
	HCLK_BUS_DIV_SHIFT		= 8,
	HCLK_BUS_DIV_MASK		= 0x3f << HCLK_BUS_DIV_SHIFT,
	HCLK_BUS_SEL_SHIFT		= 15,
	HCLK_BUS_SEL_MASK		= 0x1 << HCLK_BUS_SEL_SHIFT,

	/* CRU_CLKSEL_CON41 */
	PCLK_BUS_DIV_SHIFT		= 0,
	PCLK_BUS_DIV_MASK		= 0x1f << PCLK_BUS_DIV_SHIFT,
	PCLK_BUS_SEL_SHIFT		= 7,
	PCLK_BUS_SEL_MASK		= 0x1 << PCLK_BUS_SEL_SHIFT,
	CLK_I2C_SEL_SHIFT		= 8,
	CLK_I2C_SEL_MASK		= 0x3 << CLK_I2C_SEL_SHIFT,
	CLK_I2C_SEL_200M		= 0,
	CLK_I2C_SEL_100M,
	CLK_I2C_SEL_50M,
	CLK_I2C_SEL_24M,
	DCLK_BUS_GPIO_SEL_SHIFT		= 15,
	DCLK_BUS_GPIO_SEL_MASK		= 0x1 << DCLK_BUS_GPIO_SEL_SHIFT,

	/* CRU_CLKSEL_CON43 */
	CLK_TSADC_DIV_SHIFT		= 0,
	CLK_TSADC_DIV_MASK		= 0x7ff << CLK_TSADC_DIV_SHIFT,
	CLK_TSADC_TSEN_DIV_SHIFT	= 11,
	CLK_TSADC_TSEN_DIV_MASK		= 0x1f << CLK_TSADC_TSEN_DIV_SHIFT,

	/* CRU_CLKSEL_CON44 */
	CLK_SARADC_VCCIO156_DIV_SHIFT	= 0,
	CLK_SARADC_VCCIO156_DIV_MASK 	= 0xfff << CLK_SARADC_VCCIO156_DIV_SHIFT,

	/* CRU_CLKSEL_CON45 */
	CLK_GMAC_125M_SEL_SHIFT		= 8,
	CLK_GMAC_125M_SEL_MASK		= 0x1 << CLK_GMAC_125M_SEL_SHIFT,
	CLK_GMAC_125M			= 0,
	CLK_GMAC_24M,
	CLK_GMAC_50M_SEL_SHIFT		= 7,
	CLK_GMAC_50M_SEL_MASK		= 0x1 << CLK_GMAC_50M_SEL_SHIFT,
	CLK_GMAC_50M			= 0,

	/* CRU_CLKSEL_CON46 */
	CLK_GMAC_ETH_OUT2IO_SEL_SHIFT	= 7,
	CLK_GMAC_ETH_OUT2IO_SEL_MASK	= 0x1 << CLK_GMAC_ETH_OUT2IO_SEL_SHIFT,
	CLK_GMAC_ETH_OUT2IO_GPLL	= 0,
	CLK_GMAC_ETH_OUT2IO_CPLL,
	CLK_GMAC_ETH_OUT2IO_DIV_SHIFT	= 0,
	CLK_GMAC_ETH_OUT2IO_DIV_MASK	= 0x7f,

	/* PMU0CRU_CLKSEL_CON03 */
	CLK_PMU0_I2C0_DIV_SHIFT		= 8,
	CLK_PMU0_I2C0_DIV_MASK		= 0x1f << CLK_PMU0_I2C0_DIV_SHIFT,
	CLK_PMU0_I2C0_SEL_SHIFT		= 14,
	CLK_PMU0_I2C0_SEL_MASK		= 0x3 << CLK_PMU0_I2C0_SEL_SHIFT,
	CLK_PMU0_I2C0_SEL_200M		= 0,
	CLK_PMU0_I2C0_SEL_24M,
	CLK_PMU0_I2C0_SEL_32K,

	/* PMU1CRU_CLKSEL_CON02 */
	CLK_PMU1_UART0_SRC_DIV_SHIFT	= 0,
	CLK_PMU1_UART0_SRC_DIV_MASK	= 0xf << CLK_PMU1_UART0_SRC_DIV_SHIFT,
	CLK_PMU1_UART0_SEL_SHIFT	= 6,
	CLK_PMU1_UART0_SEL_MASK		= 0x3 << CLK_PMU1_UART0_SEL_SHIFT,

	/* PMU1CRU_CLKSEL_CON04 */
	CLK_PMU1_SPI0_DIV_SHIFT		= 0,
	CLK_PMU1_SPI0_DIV_MASK		= 0x3 << CLK_PMU1_SPI0_DIV_SHIFT,
	CLK_PMU1_SPI0_SEL_SHIFT		= 6,
	CLK_PMU1_SPI0_SEL_MASK		= 0x3 << CLK_PMU1_SPI0_SEL_SHIFT,
	CLK_PMU1_SPI0_SEL_200M		= 0,
	CLK_PMU1_SPI0_SEL_24M,
	CLK_PMU1_SPI0_SEL_32K,
	CLK_PMU1_PWM0_DIV_SHIFT		= 8,
	CLK_PMU1_PWM0_DIV_MASK		= 0x3 << CLK_PMU1_PWM0_DIV_SHIFT,
	CLK_PMU1_PWM0_SEL_SHIFT		= 14,
	CLK_PMU1_PWM0_SEL_MASK		= 0x3 << CLK_PMU1_PWM0_SEL_SHIFT,
	CLK_PMU1_PWM0_SEL_200M		= 0,
	CLK_PMU1_PWM0_SEL_24M,
	CLK_PMU1_PWM0_SEL_32K,

	/* PERICRU_CLKSEL_CON00 */
	ACLK_PERI_DIV_SHIFT		= 0,
	ACLK_PERI_DIV_MASK		= 0x1f << ACLK_PERI_DIV_SHIFT,
	ACLK_PERI_SEL_SHIFT		= 7,
	ACLK_PERI_SEL_MASK		= 0x1 << ACLK_PERI_SEL_SHIFT,
	ACLK_PERI_SEL_GPLL		= 0,
	ACLK_PERI_SEL_CPLL,
	HCLK_PERI_DIV_SHIFT		= 8,
	HCLK_PERI_DIV_MASK		= 0x3f << HCLK_PERI_DIV_SHIFT,
	HCLK_PERI_SEL_SHIFT		= 15,
	HCLK_PERI_SEL_MASK		= 0x1 << HCLK_PERI_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON01 */
	PCLK_PERI_DIV_SHIFT		= 0,
	PCLK_PERI_DIV_MASK		= 0x1f << PCLK_PERI_DIV_SHIFT,
	PCLK_PERI_SEL_SHIFT		= 7,
	PCLK_PERI_SEL_MASK		= 0x1 << PCLK_PERI_SEL_SHIFT,
	CLK_SAI0_SRC_DIV_SHIFT		= 8,
	CLK_SAI0_SRC_DIV_MASK		= 0x3f << CLK_SAI0_SRC_DIV_SHIFT,
	CLK_SAI0_SRC_SEL_SHIFT		= 14,
	CLK_SAI0_SRC_SEL_MASK		= 0x3 << CLK_SAI0_SRC_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON16 */
	CCLK_SDMMC0_DIV_SHIFT		= 0,
	CCLK_SDMMC0_DIV_MASK		= 0xff << CCLK_SDMMC0_DIV_SHIFT,
	CCLK_SDMMC0_SEL_SHIFT		= 14,
	CCLK_SDMMC0_SEL_MASK		= 0x3 << CCLK_SDMMC0_SEL_SHIFT,
	CCLK_SDMMC_SEL_GPLL		= 0,
	CCLK_SDMMC_SEL_CPLL,
	CCLK_SDMMC_SEL_24M,
	CCLK_SDMMC_SEL_HPLL,

	/* PERICRU_CLKSEL_CON17 */
	CCLK_SDMMC1_DIV_SHIFT		= 0,
	CCLK_SDMMC1_DIV_MASK		= 0xff << CCLK_SDMMC1_DIV_SHIFT,
	CCLK_SDMMC1_SEL_SHIFT		= 14,
	CCLK_SDMMC1_SEL_MASK		= 0x3 << CCLK_SDMMC1_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON18 */
	CCLK_EMMC_DIV_SHIFT		= 0,
	CCLK_EMMC_DIV_MASK		= 0xff << CCLK_EMMC_DIV_SHIFT,
	CCLK_EMMC_SEL_SHIFT		= 14,
	CCLK_EMMC_SEL_MASK		= 0x3 << CCLK_EMMC_SEL_SHIFT,
	CCLK_EMMC_SEL_GPLL		= 0,
	CCLK_EMMC_SEL_CPLL,
	CCLK_EMMC_SEL_24M,
	CCLK_EMMC_SEL_HPLL,

	/* PERICRU_CLKSEL_CON19 */
	BCLK_EMMC_DIV_SHIFT		= 8,
	BCLK_EMMC_DIV_MASK		= 0x7f << BCLK_EMMC_DIV_SHIFT,
	BCLK_EMMC_SEL_SHIFT		= 15,
	BCLK_EMMC_SEL_MASK		= 0x1 << BCLK_EMMC_SEL_SHIFT,
	BCLK_EMMC_SEL_GPLL		= 0,
	BCLK_EMMC_SEL_CPLL,

	/* PERICRU_CLKSEL_CON20 */
	SCLK_SFC_DIV_SHIFT		= 0,
	SCLK_SFC_DIV_MASK		= 0xff << SCLK_SFC_DIV_SHIFT,
	SCLK_SFC_SEL_SHIFT		= 8,
	SCLK_SFC_SEL_MASK		= 0x3 << SCLK_SFC_SEL_SHIFT,
	SCLK_SFC_SRC_SEL_GPLL		= 0,
	SCLK_SFC_SRC_SEL_CPLL,
	SCLK_SFC_SRC_SEL_24M,
	CLK_SPI1_SEL_SHIFT		= 12,
	CLK_SPI1_SEL_MASK		= 0x3 << CLK_SPI1_SEL_SHIFT,
	CLK_SPI_SEL_200M		= 0,
	CLK_SPI_SEL_100M,
	CLK_SPI_SEL_50M,
	CLK_SPI_SEL_24M,
	CLK_SPI2_SEL_SHIFT		= 14,
	CLK_SPI2_SEL_MASK		= 0x3 << CLK_SPI2_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON21 */
	CLK_UART_SRC_DIV_SHIFT		= 0,
	CLK_UART_SRC_DIV_MASK		= 0x7f << CLK_UART_SRC_DIV_SHIFT,
	CLK_UART_SRC_SEL_SHIFT		= 8,
	CLK_UART_SRC_SEL_MASK		= 0x1 << CLK_UART_SRC_SEL_SHIFT,
	CLK_UART_SRC_SEL_GPLL		= 0,
	CLK_UART_SRC_SEL_CPLL,
	CLK_UART_SEL_SHIFT		= 14,
	CLK_UART_SEL_MASK		= 0x3 << CLK_UART_SEL_SHIFT,
	CLK_UART_SEL_SRC		= 0,
	CLK_UART_SEL_FRAC,
	CLK_UART_SEL_XIN24M,

	/* PERICRU_CLKSEL_CON22 */
	CLK_UART_FRAC_NUMERATOR_SHIFT	= 16,
	CLK_UART_FRAC_NUMERATOR_MASK	= 0xffff << 16,
	CLK_UART_FRAC_DENOMINATOR_SHIFT	= 0,
	CLK_UART_FRAC_DENOMINATOR_MASK	= 0xffff,

	/* PERICRU_CLKSEL_CON40 */
	CLK_PWM1_PERI_SEL_SHIFT		= 0,
	CLK_PWM1_PERI_SEL_MASK		= 0x3 << CLK_PWM1_PERI_SEL_SHIFT,
	CLK_PWM_SEL_100M		= 0,
	CLK_PWM_SEL_50M,
	CLK_PWM_SEL_24M,
	CLK_PWM2_PERI_SEL_SHIFT		= 6,
	CLK_PWM2_PERI_SEL_MASK		= 0x3 << CLK_PWM2_PERI_SEL_SHIFT,
	CLK_PWM3_PERI_SEL_SHIFT		= 8,
	CLK_PWM3_PERI_SEL_MASK		= 0x3 << CLK_PWM3_PERI_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON43 */
	CLK_CORE_CRYPTO_SEL_SHIFT	= 0,
	CLK_CORE_CRYPTO_SEL_MASK	= 0x3 << CLK_CORE_CRYPTO_SEL_SHIFT,
	CLK_CORE_CRYPTO_SEL_200M	= 0,
	CLK_CORE_CRYPTO_SEL_100M,
	CLK_CORE_CRYPTO_SEL_24M,
	CLK_PKA_CRYPTO_SEL_SHIFT	= 6,
	CLK_PKA_CRYPTO_SEL_MASK		= 0x3 << CLK_PKA_CRYPTO_SEL_SHIFT,
	CLK_PKA_CRYPTO_SEL_300M		= 0,
	CLK_PKA_CRYPTO_SEL_200M,
	CLK_PKA_CRYPTO_SEL_100M,
	CLK_PKA_CRYPTO_SEL_24M,
	TCLK_PERI_WDT_SEL_SHIFT		= 15,
	TCLK_PERI_WDT_SEL_MASK		= 0x1 << TCLK_PERI_WDT_SEL_SHIFT,

	/* PERICRU_CLKSEL_CON46 */
	CLK_SARADC_DIV_SHIFT		= 0,
	CLK_SARADC_DIV_MASK		= 0xfff << CLK_SARADC_DIV_SHIFT,
};
#endif