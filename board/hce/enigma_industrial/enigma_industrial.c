/*
 * Copyright (C) 2015 HCE Engineering S.r.l.
 *                    Rodolfo Giometti <giometti@hce-enginerring.com>
 *
 * Based on sama5d3_xplained.c by:
 *
 * Copyright (C) 2014 Atmel Corporation
 *		      Bo Shen <voice.shen@atmel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <mmc.h>
#include <asm/io.h>
#include <asm/arch/sama5d3_smc.h>
#include <asm/arch/at91_common.h>
#include <asm/arch/at91_rstc.h>
#include <asm/arch/gpio.h>
#include <asm/arch/clk.h>
#include <lcd.h>
#include <atmel_lcdc.h>
#include <atmel_mci.h>
#include <net.h>
#include <netdev.h>
#include <spl.h>
#include <asm/arch/atmel_mpddrc.h>
#include <asm/arch/at91_wdt.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_NAND_ATMEL
void enigma_industrial_nand_hw_init(void)
{
	struct at91_smc *smc = (struct at91_smc *)ATMEL_BASE_SMC;

	at91_periph_clk_enable(ATMEL_ID_SMC);

	/* Configure SMC CS3 for NAND/SmartMedia */
	writel(AT91_SMC_SETUP_NWE(2) | AT91_SMC_SETUP_NCS_WR(1) |
	       AT91_SMC_SETUP_NRD(2) | AT91_SMC_SETUP_NCS_RD(1),
	       &smc->cs[3].setup);
	writel(AT91_SMC_PULSE_NWE(3) | AT91_SMC_PULSE_NCS_WR(5) |
	       AT91_SMC_PULSE_NRD(3) | AT91_SMC_PULSE_NCS_RD(5),
	       &smc->cs[3].pulse);
	writel(AT91_SMC_CYCLE_NWE(8) | AT91_SMC_CYCLE_NRD(8),
	       &smc->cs[3].cycle);
	writel(AT91_SMC_TIMINGS_TCLR(3) | AT91_SMC_TIMINGS_TADL(10) |
	       AT91_SMC_TIMINGS_TAR(3)  | AT91_SMC_TIMINGS_TRR(4)   |
	       AT91_SMC_TIMINGS_TWB(5)  | AT91_SMC_TIMINGS_RBNSEL(3)|
	       AT91_SMC_TIMINGS_NFSEL(1), &smc->cs[3].timings);
	writel(AT91_SMC_MODE_RM_NRD | AT91_SMC_MODE_WM_NWE |
	       AT91_SMC_MODE_EXNW_DISABLE |
#ifdef CONFIG_SYS_NAND_DBW_16
	       AT91_SMC_MODE_DBW_16 |
#else /* CONFIG_SYS_NAND_DBW_8 */
	       AT91_SMC_MODE_DBW_8 |
#endif
	       AT91_SMC_MODE_TDF_CYCLE(3),
	       &smc->cs[3].mode);
}
#endif

#ifdef CONFIG_GENERIC_ATMEL_MCI
static void enigma_industrial_mci0_hw_init(void)
{
	at91_mci_hw_init();

	at91_set_pio_output(AT91_PIO_PORTE, 2, 0);	/* MCI0 Power */
}

static void enigma_industrial_mci1_hw_init(void)
{
        at91_set_a_periph(AT91_PIO_PORTB, 19, 0);       /* MCI1 CMD */
        at91_set_a_periph(AT91_PIO_PORTB, 20, 0);       /* MCI1 DA0 */
        at91_set_a_periph(AT91_PIO_PORTB, 21, 0);       /* MCI1 DA1 */
        at91_set_a_periph(AT91_PIO_PORTB, 22, 0);       /* MCI1 DA2 */
        at91_set_a_periph(AT91_PIO_PORTB, 23, 0);       /* MCI1 DA3 */
        at91_set_a_periph(AT91_PIO_PORTB, 24, 0);       /* MCI1 CLK */

        /* Enable clock */
        at91_periph_clk_enable(ATMEL_ID_MCI1);
}
#endif

#ifdef CONFIG_LCD
vidinfo_t panel_info = {
        .vl_col = 800,
        .vl_row = 480,
        .vl_clk = 24000000,
        .vl_sync = ATMEL_LCDC_INVLINE_NORMAL | ATMEL_LCDC_INVFRAME_NORMAL,
        .vl_bpix = LCD_BPP,
        .vl_tft = 1,
        .vl_hsync_len = 48,
        .vl_left_margin = 40,
        .vl_right_margin = 40,
        .vl_vsync_len = 3,
        .vl_upper_margin = 29,
        .vl_lower_margin = 13,
        .mmio = ATMEL_BASE_LCDC,
};

void lcd_enable(void)
{
}

void lcd_disable(void)
{
}

static void enigma_industrial_lcd_hw_init(void)
{
        gd->fb_base = CONFIG_SAMA5D3_LCD_BASE;

        /* The higher 8 bit of LCD is board related */
        at91_set_a_periph(AT91_PIO_PORTA, 16, 0);       /* LCDD16 */
        at91_set_a_periph(AT91_PIO_PORTA, 17, 0);       /* LCDD17 */
        at91_set_a_periph(AT91_PIO_PORTA, 18, 0);       /* LCDD18 */
        at91_set_a_periph(AT91_PIO_PORTA, 19, 0);       /* LCDD19 */
        at91_set_a_periph(AT91_PIO_PORTA, 20, 0);       /* LCDD20 */
        at91_set_a_periph(AT91_PIO_PORTA, 21, 0);       /* LCDD21 */
        at91_set_a_periph(AT91_PIO_PORTA, 22, 0);       /* LCDD22 */
        at91_set_a_periph(AT91_PIO_PORTA, 23, 0);       /* LCDD23 */
        at91_set_a_periph(AT91_PIO_PORTA, 24, 0);       /* LCDPWM */
        at91_set_a_periph(AT91_PIO_PORTA, 25, 0);       /* LCDDISP */
        at91_set_a_periph(AT91_PIO_PORTA, 26, 0);       /* LCDVSYNC */
        at91_set_a_periph(AT91_PIO_PORTA, 27, 0);       /* LCDHSYNC */
        at91_set_a_periph(AT91_PIO_PORTA, 28, 0);       /* LCDPCK */
        at91_set_a_periph(AT91_PIO_PORTA, 29, 0);       /* LCDDEN */

        /* Configure lower 16 bit of LCD and enable clock */
        at91_lcd_hw_init();
}

#ifdef CONFIG_LCD_INFO
#include <nand.h>
#include <version.h>

void lcd_show_board_info(void)
{
        ulong dram_size;
        uint64_t nand_size;
        int i;
        char temp[32];

        lcd_printf("%s\n", U_BOOT_VERSION);
        lcd_printf("(C) 2015-2017 HCE Engineering S.r.l.\n");
        lcd_printf("info@cosino.io\n");
        lcd_printf("%s CPU at %s MHz\n", get_cpu_name(),
                   strmhz(temp, get_cpu_clk_rate()));

        dram_size = 0;
        for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
                dram_size += gd->bd->bi_dram[i].size;

        nand_size = 0;
#ifdef CONFIG_NAND_ATMEL
        for (i = 0; i < CONFIG_SYS_MAX_NAND_DEVICE; i++)
                nand_size += nand_info[i].size;
#endif
        lcd_printf("%ld MB SDRAM, %lld MB NAND\n",
                   dram_size >> 20, nand_size >> 20);
}
#endif /* CONFIG_LCD_INFO */
#endif /* CONFIG_LCD */

int board_early_init_f(void)
{
	at91_periph_clk_enable(ATMEL_ID_PIOA);
	at91_periph_clk_enable(ATMEL_ID_PIOB);
	at91_periph_clk_enable(ATMEL_ID_PIOC);
	at91_periph_clk_enable(ATMEL_ID_PIOD);
	at91_periph_clk_enable(ATMEL_ID_PIOE);

	at91_seriald_hw_init();

	return 0;
}

int board_init(void)
{
	/* adress of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

#ifdef CONFIG_NAND_ATMEL
	enigma_industrial_nand_hw_init();
#endif
#ifdef CONFIG_USB_GADGET_ATMEL_USBA
        at91_udp_hw_init();
#endif
#ifdef CONFIG_GENERIC_ATMEL_MCI
	enigma_industrial_mci0_hw_init();
	enigma_industrial_mci1_hw_init();
	at91_set_pio_periph(AT91_PIO_PORTC, 15, 0);
#endif
#ifdef CONFIG_MACB
	at91_gmac_hw_init();
	at91_macb_hw_init();
#endif
#ifdef CONFIG_LCD
        if (has_lcdc())
                enigma_industrial_lcd_hw_init();
#endif
	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE,
				    CONFIG_SYS_SDRAM_SIZE);

	return 0;
}

int board_eth_init(bd_t *bis)
{
#ifdef CONFIG_MACB
	macb_eth_initialize(0, (void *)ATMEL_BASE_GMAC, 0x00);
	macb_eth_initialize(0, (void *)ATMEL_BASE_EMAC, 0x00);
#endif
	return 0;
}

#ifdef CONFIG_GENERIC_ATMEL_MCI
int board_mmc_init(bd_t *bis)
{
	atmel_mci_init((void *)ATMEL_BASE_MCI0);

	return 0;
}
#endif

/* SPL */
#ifdef CONFIG_SPL_BUILD
void spl_board_init(void)
{
#ifdef CONFIG_SYS_USE_MMC
	enigma_industrial_mci0_hw_init();
#elif CONFIG_SYS_USE_NANDFLASH
	enigma_industrial_nand_hw_init();
#endif
}

static void ddr2_conf(struct atmel_mpddrc_config *ddr2)
{
	ddr2->md = (ATMEL_MPDDRC_MD_DBW_32_BITS | ATMEL_MPDDRC_MD_DDR2_SDRAM);

	ddr2->cr = (ATMEL_MPDDRC_CR_NC_COL_10 |
		    ATMEL_MPDDRC_CR_NR_ROW_14 |
		    ATMEL_MPDDRC_CR_CAS_DDR_CAS3 |
		    ATMEL_MPDDRC_CR_ENRDM_ON |
		    ATMEL_MPDDRC_CR_NB_8BANKS |
		    ATMEL_MPDDRC_CR_NDQS_DISABLED |
		    ATMEL_MPDDRC_CR_DECOD_INTERLEAVED |
		    ATMEL_MPDDRC_CR_UNAL_SUPPORTED);
	/*
	 * As the DDR2-SDRAm device requires a refresh time is 7.8125us
	 * when DDR run at 133MHz, so it needs (7.8125us * 133MHz / 10^9) clocks
	 */
	ddr2->rtr = 0x411;

	ddr2->tpr0 = (6 << ATMEL_MPDDRC_TPR0_TRAS_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TRCD_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TWR_OFFSET |
		      8 << ATMEL_MPDDRC_TPR0_TRC_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TRP_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TRRD_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TWTR_OFFSET |
		      2 << ATMEL_MPDDRC_TPR0_TMRD_OFFSET);

	ddr2->tpr1 = (2 << ATMEL_MPDDRC_TPR1_TXP_OFFSET |
		      200 << ATMEL_MPDDRC_TPR1_TXSRD_OFFSET |
		      28 << ATMEL_MPDDRC_TPR1_TXSNR_OFFSET |
		      26 << ATMEL_MPDDRC_TPR1_TRFC_OFFSET);

	ddr2->tpr2 = (7 << ATMEL_MPDDRC_TPR2_TFAW_OFFSET |
		      2 << ATMEL_MPDDRC_TPR2_TRTP_OFFSET |
		      2 << ATMEL_MPDDRC_TPR2_TRPA_OFFSET |
		      7 << ATMEL_MPDDRC_TPR2_TXARDS_OFFSET |
		      8 << ATMEL_MPDDRC_TPR2_TXARD_OFFSET);
}

void mem_init(void)
{
	struct atmel_mpddrc_config ddr2;

	ddr2_conf(&ddr2);

	/* Enable MPDDR clock */
	at91_periph_clk_enable(ATMEL_ID_MPDDRC);
	at91_system_clk_enable(AT91_PMC_DDR);

	/* DDRAM2 Controller initialize */
	ddr2_init(ATMEL_BASE_MPDDRC, ATMEL_BASE_DDRCS, &ddr2);
}

void at91_pmc_init(void)
{
	u32 tmp;

	tmp = AT91_PMC_PLLAR_29 |
	      AT91_PMC_PLLXR_PLLCOUNT(0x3f) |
	      AT91_PMC_PLLXR_MUL(43) |
	      AT91_PMC_PLLXR_DIV(1);
	at91_plla_init(tmp);

	at91_pllicpr_init(AT91_PMC_IPLL_PLLA(0x3));

	tmp = AT91_PMC_MCKR_MDIV_4 |
	      AT91_PMC_MCKR_CSS_PLLA;
	at91_mck_init(tmp);
}
#endif
