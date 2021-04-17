/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2014 Chen-Yu Tsai <wens@csie.org>
 *
 * Placeholder wrapper to allow addressing Allwinner A23 (and later) sun8i
 * CPU based devices separately. Please do not add anything in here.
 */
#ifndef __CONFIG_H
#define __CONFIG_H

#define SUNXI_RESUME_BASE		(CONFIG_ARMV7_SECURE_BASE + \
					 CONFIG_ARMV7_SECURE_MAX_SIZE)
#define SUNXI_RESUME_SIZE		1024

#define SUNXI_SCP_BASE			(SUNXI_RESUME_BASE + SUNXI_RESUME_SIZE)
#define SUNXI_SCP_MAX_SIZE		(16 * 1024)

#ifdef SUNXI_SRAM_A2_SIZE
#define SUNXI_RESUME_BASE		(CONFIG_ARMV7_SECURE_BASE + \
					 CONFIG_ARMV7_SECURE_MAX_SIZE)
#define SUNXI_RESUME_SIZE		1024

#define SUNXI_SCP_BASE			(SUNXI_RESUME_BASE + SUNXI_RESUME_SIZE)
#define SUNXI_SCP_MAX_SIZE		(16 * 1024)
#endif

/*
 * Include common sunxi configuration where most the settings are
 */
#include <configs/sunxi-common.h>

#endif /* __CONFIG_H */
