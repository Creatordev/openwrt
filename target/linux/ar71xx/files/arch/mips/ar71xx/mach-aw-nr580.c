/*
 *  AzureWave AW-NR580 board support
 *
 *  Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/input.h>

#include <asm/mips_machine.h>
#include <asm/mach-ar71xx/ar71xx.h>
#include <asm/mach-ar71xx/pci.h>

#include "devices.h"

#define AW_NR580_GPIO_BTN_WPS		3
#define AW_NR580_GPIO_BTN_RESET		11

#define AW_NR580_BUTTONS_POLL_INTERVAL	20

static struct spi_board_info aw_nr580_spi_info[] = {
	{
		.bus_num	= 0,
		.chip_select	= 0,
		.max_speed_hz	= 25000000,
		.modalias	= "m25p80",
	}
};

static struct gpio_button aw_nr580_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
		.threshold	= 5,
		.gpio		= AW_NR580_GPIO_BTN_RESET,
		.active_low	= 1,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= BTN_1,
		.threshold	= 5,
		.gpio		= AW_NR580_GPIO_BTN_WPS,
		.active_low	= 1,
	}
};

static void __init aw_nr580_setup(void)
{
	ar71xx_add_device_spi(NULL, aw_nr580_spi_info,
					ARRAY_SIZE(aw_nr580_spi_info));

	ar71xx_add_device_gpio_buttons(-1, AW_NR580_BUTTONS_POLL_INTERVAL,
					ARRAY_SIZE(aw_nr580_gpio_buttons),
					aw_nr580_gpio_buttons);
}

MIPS_MACHINE(AR71XX_MACH_AW_NR580, "AzureWave AW-NR580", aw_nr580_setup);
