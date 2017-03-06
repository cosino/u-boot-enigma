/*
 * Configuration settings for the HCE Cosino Enigma Development board.
 *
 * Copyright (C) 2015 HCE Engineering S.r.l.
 *                    Rodolfo Giometti <giometti@hce-engineering.com>
 *
 * based on sama5d3_xplained.h by:
 * Copyright (C) 2013 Atmel Corporation
 *		      Bo Shen <voice.shen@atmel.com>
 *
 * Based on sama5d3xek.h by: Bo Shen <voice.shen@atmel.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/hardware.h>

#define CONFIG_SYS_TEXT_BASE		0x26f00000

/* ARM asynchronous clock */
#define CONFIG_SYS_AT91_SLOW_CLOCK      32768
#define CONFIG_SYS_AT91_MAIN_CLOCK      12000000 /* from 12 MHz crystal */
#define CONFIG_SYS_HZ		        1000

#define CONFIG_AT91FAMILY
#define CONFIG_CMDLINE_TAG              /* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_ARCH_CPU_INIT
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_CMD_BOOTZ
#define CONFIG_OF_LIBFDT		/* Device Tree support */

/* general purpose I/O */
#define CONFIG_AT91_GPIO

/* serial console */
#define CONFIG_ATMEL_USART
#define CONFIG_USART_BASE		ATMEL_BASE_DBGU
#define	CONFIG_USART_ID			ATMEL_ID_DBGU

/*
 * This needs to be defined for the OHCI code to work but it is defined as
 * ATMEL_ID_UHPHS in the CPU specific header files.
 */
#define ATMEL_ID_UHP			ATMEL_ID_UHPHS

/*
 * Specify the clock enable bit in the PMC_SCER register.
 */
#define ATMEL_PMC_UHP			AT91SAM926x_PMC_UHP

/* LCD */
#define CONFIG_LCD
#define LCD_BPP			 LCD_COLOR16
#define LCD_OUTPUT_BPP                  24
#define CONFIG_LCD_LOGO
#define CONFIG_LCD_INFO
#define CONFIG_LCD_INFO_BELOW_LOGO
#define CONFIG_SYS_WHITE_ON_BLACK
#define CONFIG_ATMEL_HLCD
#define CONFIG_ATMEL_LCD_BGR555
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

/* board specific (not enough SRAM) */
#define CONFIG_SAMA5D3_LCD_BASE         0x23E00000

#define CONFIG_BOOTDELAY		3

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/* No NOR flash */
#define CONFIG_SYS_NO_FLASH

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_LOADS
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP

/* SDRAM */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE           ATMEL_BASE_DDRCS
#define CONFIG_SYS_SDRAM_SIZE		(256<<20)	/* 256MB */

#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_SDRAM_BASE + 4 * 1024 - GENERATED_GBL_DATA_SIZE)

/* SerialFlash */
#define CONFIG_CMD_SF

#ifdef CONFIG_CMD_SF
#define CONFIG_ATMEL_SPI
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SF_DEFAULT_SPEED		30000000
#endif
/* NAND flash */
#define CONFIG_CMD_NAND

#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_ATMEL
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		ATMEL_BASE_CS3
/* our ALE is AD21 */
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
/* our CLE is AD22 */
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)
#define CONFIG_SYS_NAND_ONFI_DETECTION
/* PMECC & PMERRLOC */
#define CONFIG_ATMEL_NAND_HWECC
#define CONFIG_ATMEL_NAND_HW_PMECC
#define CONFIG_PMECC_CAP		4
#define CONFIG_PMECC_SECTOR_SIZE	512
#define CONFIG_CMD_NAND_TRIMFFS
#define CONFIG_CMD_MTDPARTS

#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#endif

/* Ethernet Hardware */
#define CONFIG_MACB
#define CONFIG_RMII
#define CONFIG_NET_MULTI
#define CONFIG_NET_RETRY_COUNT		20
#define CONFIG_MACB_SEARCH_PHY
#define CONFIG_RGMII
#define CONFIG_CMD_MII
#define CONFIG_PHYLIB

/* MMC */
#define CONFIG_CMD_MMC

#ifdef CONFIG_CMD_MMC
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_GENERIC_ATMEL_MCI
#define CONFIG_ATMEL_MCI_8BIT
#endif

/* USB */
#define CONFIG_CMD_USB

#ifdef CONFIG_CMD_USB
#define CONFIG_USB_ATMEL
#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_CPU_INIT
#define CONFIG_SYS_USB_OHCI_REGS_BASE		ATMEL_BASE_OHCI
#define CONFIG_SYS_USB_OHCI_SLOT_NAME		"enigma"
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	2
#define CONFIG_DOS_PARTITION
#define CONFIG_USB_STORAGE
#endif

/* USB device */
#define CONFIG_USB_GADGET

#ifdef CONFIG_USB_GADGET
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_ATMEL_USBA

/* DFU class support */
#define CONFIG_CMD_DFU

#ifdef CONFIG_CMD_DFU
#define CONFIG_DFU_FUNCTION
#define CONFIG_DFU_MMC
#define CONFIG_DFU_NAND
#define CONFIG_DFU_RAM
#define CONFIG_USBDOWNLOAD_GADGET

#define CONFIG_USB_GADGET_VBUS_DRAW		2

/* USB Atmel's IDs */
#define CONFIG_G_DNL_VENDOR_NUM			0x03EB
#define CONFIG_G_DNL_PRODUCT_NUM		0x6156
#define CONFIG_G_DNL_MANUFACTURER		"Atmel"

#define CONFIG_SYS_CACHELINE_SIZE		16

#else

/* RNDIS class support */
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_RNDIS
#define CONFIG_USBNET_MANUFACTURER		"SAMA5D3 Xplained"

#endif
#endif

#if defined(CONFIG_CMD_USB) || defined(CONFIG_CMD_MMC)
#define CONFIG_CMD_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE
#endif

#define CONFIG_SYS_LOAD_ADDR			0x22000000 /* load address */

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START		CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END			0x26e00000

#ifdef CONFIG_SYS_USE_NANDFLASH
/* bootstrap + u-boot + env + linux in nandflash */
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET               0x0c0000
#define CONFIG_ENV_OFFSET_REDUND        0x0e0000
#define CONFIG_ENV_SIZE         0x20000         /* 1 sector = 128 kB */
#define CONFIG_NAND_BOOTCOMMAND \
	"if nand device ${nanddev}; then " \
		"echo NAND found on device ${mmcdev};" \
		"run loadzimagenand;" \
		"run nandboot;" \
	"fi;"
#else
#define CONFIG_NAND_BOOTCOMMAND ""      /* nop */
#endif /* CONFIG_SYS_USE_NANDFLASH */

#ifdef CONFIG_SYS_USE_MMC
/* bootstrap + u-boot + env + linux in mmc */
#define CONFIG_ENV_IS_IN_MMC
/* For FAT system, most cases it should be in the reserved sector */
#define CONFIG_ENV_OFFSET       0x2000
#define CONFIG_ENV_SIZE         0x1000
#define CONFIG_SYS_MMC_ENV_DEV  0
#define CONFIG_MMC_BOOTCOMMAND  \
	"if mmc rescan ; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadzimagefat; then " \
			"run mmcboot;" \
		"fi;" \
	"fi;"
#else
#define CONFIG_MMC_BOOTCOMMAND  ""      /* nop */
#endif /* CONFIG_SYS_USE_MMC */

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=22000000\0" \
	"bootfile=zImage\0" \
	"bootimage_addr=00100000\0" \
	"bootimage_size=00500000\0" \
	"console=ttyS0,115200\0" \
	"videoargs=video=Unknown-1:800x480-32\0" \
	"nanddev=0\0" \
	"nandroot=ubi0:rootfs rw\0" \
	"nandrootfstype=ubifs ubi.mtd=5\0" \
	"nandargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"${videoargs} " \
		"root=${nandroot} " \
		"rootfstype=${nandrootfstype}\0" \
	"loadzimagenand=nand read ${loadaddr} ${bootimage_addr} " \
					"${bootimage_size}\0" \
	"nandboot=echo Booting from NAND...; " \
		"run nandargs; " \
		"bootz ${loadaddr}\0" \
	"mmcdev=0\0" \
	"mmcroot=/dev/mmcblk0p2 rw\0" \
	"mmcrootfstype=ext4 rootwait\0" \
	"mmcargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"${videoargs} " \
		"root=${mmcroot} " \
		"rootfstype=${mmcrootfstype}\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=fatload mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc...; " \
		"env import -t $loadaddr $filesize\0" \
	"loadzimagefat=fatload mmc ${mmcdev} ${loadaddr} ${bootfile}\0" \
	"mmcboot=echo Booting from mmc...; " \
		"run mmcargs; " \
		"bootz ${loadaddr}\0"

#define CONFIG_BOOTCOMMAND \
	CONFIG_NAND_BOOTCOMMAND \
	CONFIG_MMC_BOOTCOMMAND \
	"echo \"Error! Cannot load kernel\""

#define CONFIG_BAUDRATE			115200

#define CONFIG_SYS_PROMPT		"U-Boot> "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_HUSH_PARSER

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)

#endif
