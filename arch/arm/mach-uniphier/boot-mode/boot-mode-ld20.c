/*
 * Copyright (C) 2016 Masahiro Yamada <yamada.masahiro@socionext.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <spl.h>
#include <linux/io.h>

#include "../sg-regs.h"
#include "boot-device.h"

static struct boot_device_info boot_device_table[] = {
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, EraseSize 128KB, Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, EraseSize 128KB, Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, EraseSize 128KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, EraseSize 128KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, EraseSize 256KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, EraseSize 256KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, EraseSize 512KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, EraseSize 512KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, EraseSize 128KB, Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, EraseSize 128KB, Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, EraseSize 128KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, EraseSize 128KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, EraseSize 256KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, EraseSize 256KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, EraseSize 512KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, EraseSize 512KB, Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, ONFI,            Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, ONFI,            Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC  8, ONFI,            Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 8, ECC 16, ONFI,            Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, ONFI             Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, ONFI             Addr 4)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC  8, ONFI             Addr 5)"},
	{BOOT_DEVICE_NAND, "NAND (Mirror 1, ECC 16, ONFI             Addr 5)"},
	{BOOT_DEVICE_MMC1, "eMMC (Legacy,         4bit, 1.8V, Training Off)"},
	{BOOT_DEVICE_MMC1, "eMMC (Legacy,         4bit, 1.8V, Training On)"},
	{BOOT_DEVICE_MMC1, "eMMC (Legacy,         8bit, 1.8V, Training Off)"},
	{BOOT_DEVICE_MMC1, "eMMC (Legacy,         8bit, 1.8V, Training On)"},
	{BOOT_DEVICE_MMC1, "eMMC (High Speed SDR, 8bit, 1.8V, Training Off)"},
	{BOOT_DEVICE_MMC1, "eMMC (High Speed SDR, 8bit, 1.8V, Training On)"},
	{BOOT_DEVICE_MMC1, "eMMC (Legacy,         4bit, 1.8V, Training Off)"},
	{BOOT_DEVICE_NOR,  "NOR Boot (XECS1)"},
};

static int get_boot_mode_sel(void)
{
	return (readl(SG_PINMON0) >> 1) & 0x1f;
}

u32 uniphier_ld20_boot_device(void)
{
	int boot_mode;

	if (~readl(SG_PINMON0) & 0x00000780)
		return BOOT_DEVICE_USB;

	boot_mode = get_boot_mode_sel();

	return boot_device_table[boot_mode].type;
}

void uniphier_ld20_boot_mode_show(void)
{
	int mode_sel, i;

	mode_sel = get_boot_mode_sel();

	puts("Boot Mode Pin:\n");

	for (i = 0; i < ARRAY_SIZE(boot_device_table); i++)
		printf(" %c %02x %s\n", i == mode_sel ? '*' : ' ', i,
		       boot_device_table[i].info);
}
