/* SPDX-License-Identifier: MIT */
/*
 * Copyright (C) 2024, Matheus Castello <matheus@castello.eng.br>
 *
 */

#ifndef __VIRTIO_GPU_H
#define __VIRTIO_GPU_H

#define VIRTIO_GPU_F_VIRGL               0
#define VIRTIO_GPU_F_EDID                1
#define VIRTIO_GPU_F_RESOURCE_UUID       2
#define VIRTIO_GPU_F_RESOURCE_BLOB       3
#define VIRTIO_GPU_F_CONTEXT_INIT        4

#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

struct virtio_gpu_config {
        __le32 events_read;
        __le32 events_clear;
        __le32 num_scanouts;
        __le32 num_capsets;
};

enum virtio_gpu_shm_id {
        VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
        VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1,
};

enum virtio_gpu_ctrl_type {
        VIRTIO_GPU_UNDEFINED = 0,

        /* 2d commands */
        VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
        VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
        VIRTIO_GPU_CMD_RESOURCE_UNREF,
        VIRTIO_GPU_CMD_SET_SCANOUT,
        VIRTIO_GPU_CMD_RESOURCE_FLUSH,
        VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
        VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
        VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
        VIRTIO_GPU_CMD_GET_CAPSET_INFO,
        VIRTIO_GPU_CMD_GET_CAPSET,
        VIRTIO_GPU_CMD_GET_EDID,
        VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID,
        VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB,
        VIRTIO_GPU_CMD_SET_SCANOUT_BLOB,

        /* 3d commands */
        VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
        VIRTIO_GPU_CMD_CTX_DESTROY,
        VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
        VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
        VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
        VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
        VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
        VIRTIO_GPU_CMD_SUBMIT_3D,
        VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB,
        VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB,

        /* cursor commands */
        VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
        VIRTIO_GPU_CMD_MOVE_CURSOR,

        /* success responses */
        VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
        VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
        VIRTIO_GPU_RESP_OK_CAPSET_INFO,
        VIRTIO_GPU_RESP_OK_CAPSET,
        VIRTIO_GPU_RESP_OK_EDID,
        VIRTIO_GPU_RESP_OK_RESOURCE_UUID,
        VIRTIO_GPU_RESP_OK_MAP_INFO,

        /* error responses */
        VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
        VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
        VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
        VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
        VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
        VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
};

#define VIRTIO_GPU_FLAG_FENCE (1 << 0)
#define VIRTIO_GPU_FLAG_INFO_RING_IDX (1 << 1)

struct virtio_gpu_ctrl_hdr {
        __le32 type;
        __le32 flags;
        __le64 fence_id;
        __le32 ctx_id;
        __u8 ring_idx;
        __u8 padding[3];
};

#define VIRTIO_GPU_MAX_SCANOUTS 16

struct virtio_gpu_rect {
        __le32 x;
        __le32 y;
        __le32 width;
        __le32 height;
};

struct virtio_gpu_resp_display_info {
        struct virtio_gpu_ctrl_hdr hdr;
        struct virtio_gpu_display_one {
                struct virtio_gpu_rect r;
                __le32 enabled;
                __le32 flags;
        } pmodes[VIRTIO_GPU_MAX_SCANOUTS];
};

struct virtio_gpu_get_edid {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 scanout;
        __le32 padding;
};

struct virtio_gpu_resp_edid {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 size;
        __le32 padding;
        __u8 edid[1024];
};

enum virtio_gpu_formats {
        VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1,
        VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2,
        VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3,
        VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4,

        VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67,
        VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68,

        VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121,
        VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134,
};

struct virtio_gpu_resource_create_2d {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 resource_id;
        __le32 format;
        __le32 width;
        __le32 height;
};

struct virtio_gpu_resource_unref {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 resource_id;
        __le32 padding;
};

struct virtio_gpu_set_scanout {
        struct virtio_gpu_ctrl_hdr hdr;
        struct virtio_gpu_rect r;
        __le32 scanout_id;
        __le32 resource_id;
};

struct virtio_gpu_resource_flush {
        struct virtio_gpu_ctrl_hdr hdr;
        struct virtio_gpu_rect r;
        __le32 resource_id;
        __le32 padding;
};

struct virtio_gpu_resource_attach_backing {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 resource_id;
        __le32 nr_entries;
};

struct virtio_gpu_mem_entry {
        __le64 addr;
        __le32 length;
        __le32 padding;
};

struct virtio_gpu_resource_detach_backing {
        struct virtio_gpu_ctrl_hdr hdr;
        __le32 resource_id;
        __le32 padding;
};

#endif
