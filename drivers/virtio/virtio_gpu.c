// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2024, Matheus Castello <matheus@castello.eng.br>
 *
 */

#define LOG_CATEGORY UCLASS_VIRTIO

#include <common.h>
#include <dm.h>
#include <log.h>
#include <pci.h>
#include <video.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <virtio.h>
#include <virtio_ring.h>
#include "virtio_gpu.h"

#define VIRTIO_PCI_VENDOR_ID	0x1af4
#define VIRTIO_PCI_DEVICE_ID10	0x1050

struct virtio_gpu_priv {
	struct virtqueue *vqs[2];
};

int virtio_gpu_cmd_get_display_info()
{
	struct virtio_gpu_ctrl_hdr cmd_p;

	cmd_p.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_DISPLAY_INFO);

	return 0;
}

static int virtio_gpu_probe(struct udevice *dev)
{
	struct virtio_gpu_priv *priv = dev_get_priv(dev);
	struct video_uc_plat *plat = dev_get_uclass_plat(dev);
	int ret;

	log_debug("%s: Trying to probe\n", __func__);

	ret = virtio_find_vqs(dev, 2, priv->vqs);
	if (ret) {
		log_debug(
			"%s: Error trying to get the virtqueues :: %d\n",
			__func__,
			ret
		);
		return ret;
	}

    return 0;
}

static int virtio_gpu_bind(struct udevice *dev)
{
	struct virtio_dev_priv *uc_priv = dev_get_uclass_priv(dev->parent);

	log_debug("%s: Trying to bind\n", __func__);
	virtio_driver_features_init(uc_priv, NULL, 0, NULL, 0);

	return 0;
}

U_BOOT_DRIVER(virtio_gpu) = {
	.name	= "virtio_gpu",
	.id	= UCLASS_VIDEO,
	.bind	= virtio_gpu_bind,
	.probe	= virtio_gpu_probe,
	.priv_auto	= sizeof(struct virtio_gpu_priv),
	.flags	= DM_FLAG_ACTIVE_DMA,
};

static struct pci_device_id virtio_gpu_supported[] = {
	{ PCI_DEVICE(VIRTIO_PCI_VENDOR_ID, VIRTIO_PCI_DEVICE_ID10) },
	{ },
};

U_BOOT_PCI_DEVICE(virtio_gpu, virtio_gpu_supported);
