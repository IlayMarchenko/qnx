/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef IVCLIB_TEGRA_IVC_H
#define IVCLIB_TEGRA_IVC_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

struct tegra_hv_ivc_ops;

struct tegra_hv_ivc_cookie {
	/* some fields that might be useful */
	int irq;
	int peer_vmid;
	int nframes;
	int frame_size;
};


struct tegra_hv_ivc_ops {
	/* called when data are received */
	void (*rx_rdy)(struct tegra_hv_ivc_cookie *ivck);
	/* called when space is available to write data */
	void (*tx_rdy)(struct tegra_hv_ivc_cookie *ivck);
};

struct ivc;

/**
 * tegra_hv_ivc_reserve - Reserve an IVC queue for use
 * @queue_id	Id number of the queue to use.
 * @ops		Ops structure or NULL
 *
 * Reserves the queue for use
 *
 * Returns a pointer to the cookie for the IVC channel or NULL
 * if a channel with the given queue_id could not be found.
 */
struct tegra_hv_ivc_cookie *tegra_hv_ivc_reserve(unsigned id,
		const struct tegra_hv_ivc_ops *ops);

/**
 * tegra_hv_ivc_unreserve - Unreserve an IVC queue used
 * @ivck	IVC cookie
 *
 * Unreserves the IVC channel
 *
 * Returns 0 on success and an error code otherwise
 */
int tegra_hv_ivc_unreserve(struct tegra_hv_ivc_cookie *ivck);

/**
 * ivc_hv_ivc_write - Writes a frame to the IVC queue
 * @ivck	IVC cookie of the queue
 * @buf		Pointer to the data to write
 * @size	Size of the data to write
 *
 * Write a number of bytes (as a single frame) from the queue.
 *
 * Returns size on success and an error code otherwise
 */
int tegra_hv_ivc_write(struct tegra_hv_ivc_cookie *ivck, const void *buf,
		int size);
int32_t tegra_ivc_write(struct ivc *ivc, const void *buf, size_t size);

/**
 * ivc_hv_ivc_read - Reads a frame from the IVC queue
 * @ivck	IVC cookie of the queue
 * @buf		Pointer to the data to read
 * @size	max size of the data to read
 *
 * Reads a number of bytes (as a single frame) from the queue.
 *
 * Returns size on success and an error code otherwise
 */
int tegra_hv_ivc_read(struct tegra_hv_ivc_cookie *ivck, void *buf, int size);
int32_t tegra_ivc_read(struct ivc *ivc, void *buf, size_t size);

/**
 * ivc_hv_ivc_can_read - Test whether data are available
 * @ivck	IVC cookie of the queue
 *
 * Test wheter data to read are available
 *
 * Returns true if data are available in the rx queue, false if not
 */
int tegra_hv_ivc_can_read(struct tegra_hv_ivc_cookie *ivck);
bool tegra_ivc_can_read(struct ivc *ivc);

/**
 * ivc_hv_ivc_can_write - Test whether data can be written
 * @ivck	IVC cookie of the queue
 *
 * Test wheter data can be written
 *
 * Returns true if data are can be written to the tx queue, false if not
 */
int tegra_hv_ivc_can_write(struct tegra_hv_ivc_cookie *ivck);
bool tegra_ivc_can_write(struct ivc *ivc);

/**
 * ivc_hv_ivc_tx_empty - Test whether the tx queue is empty
 * @ivck	IVC cookie of the queue
 *
 * Test wheter the tx queue is completely empty
 *
 * Returns true if the queue is empty, false otherwise
 */
int tegra_hv_ivc_tx_empty(struct tegra_hv_ivc_cookie *ivck);
bool tegra_ivc_tx_empty(struct ivc *ivc);

/**
 * ivc_hv_ivc_loopback - Sets (or clears) loopback mode
 * @ivck	IVC cookie of the queue
 * @mode	Set loopback on/off (1 = on, 0 = off)
 *
 * Sets or clears loopback mode accordingly.
 *
 * When loopback is active any writes are ignored, while
 * reads do not return data.
 * Incoming data are copied immediately to the tx queue.
 *
 * Returns 0 on success, a negative error code otherwise
 */
int tegra_hv_ivc_set_loopback(struct tegra_hv_ivc_cookie *ivck, int mode);

/* debugging aid */
int tegra_hv_ivc_dump(struct tegra_hv_ivc_cookie *ivck);

/**
 * ivc_hv_ivc_read_peek - Peek (copying) data from a received frame
 * @ivck	IVC cookie of the queue
 * @buf		Buffer to receive the data
 * @off		Offset in the frame
 * @count	Count of bytes to copy
 *
 * Peek data from a received frame, copying to buf, without removing
 * the frame from the queue.
 *
 * Returns size on success, a negative error code otherwise
 */
int tegra_hv_ivc_read_peek(struct tegra_hv_ivc_cookie *ivck,
		void *buf, int off, int count);
int32_t tegra_ivc_read_peek(struct ivc *ivc, void *buf, size_t off, size_t count);

/**
 * ivc_hv_ivc_read_get_next_frame - Peek at the next frame to receive
 * @ivck	IVC cookie of the queue
 *
 * Peek at the next frame to be received, without removing it from
 * the queue.
 *
 * Returns a pointer to the frame, or an error encoded pointer.
 */
void *tegra_hv_ivc_read_get_next_frame(struct tegra_hv_ivc_cookie *ivck);
void *tegra_ivc_read_get_next_frame(struct ivc *ivc);

/**
 * ivc_hv_ivc_read_advance - Advance the read queue
 * @ivck	IVC cookie of the queue
 *
 * Advance the read queue
 *
 * Returns 0, or a negative error value if failed.
 */
int tegra_hv_ivc_read_advance(struct tegra_hv_ivc_cookie *ivck);
int32_t tegra_ivc_read_advance(struct ivc *ivc);

/**
 * ivc_hv_ivc_write_poke - Poke data to a frame to be transmitted
 * @ivck	IVC cookie of the queue
 * @buf		Buffer to the data
 * @off		Offset in the frame
 * @count	Count of bytes to copy
 *
 * Copy data to a transmit frame, copying from buf, without advancing
 * the the transmit queue.
 *
 * Returns 0 on success, a negative error code otherwise
 */
int tegra_hv_ivc_write_poke(struct tegra_hv_ivc_cookie *ivck,
		const void *buf, int off, int count);
int32_t tegra_ivc_write_poke(struct ivc *ivc, const void *buf, size_t off,
		size_t count);

/**
 * ivc_hv_ivc_write_get_next_frame - Poke at the next frame to transmit
 * @ivck	IVC cookie of the queue
 *
 * Get access to the next frame.
 *
 * Returns a pointer to the frame, or an error encoded pointer.
 */
void *tegra_hv_ivc_write_get_next_frame(struct tegra_hv_ivc_cookie *ivck);
void *tegra_ivc_write_get_next_frame(struct ivc *ivc);

/**
 * ivc_hv_ivc_write_advance - Advance the write queue
 * @ivck	IVC cookie of the queue
 *
 * Advance the write queue
 *
 * Returns 0, or a negative error value if failed.
 */
int tegra_hv_ivc_write_advance(struct tegra_hv_ivc_cookie *ivck);
int32_t tegra_ivc_write_advance(struct ivc *ivc);

struct tegra_hv_ivm_cookie {
	uint64_t ipa;
	uint64_t size;
	unsigned peer_vmid;
	void *reserved;
};

/**
 * tegra_hv_mempool_reserve - reserve a mempool for use
 * @id		Id of the requested mempool.
 *
 * Returns a cookie representing the mempool on success, otherwise NULL.
 */
struct tegra_hv_ivm_cookie *tegra_hv_mempool_reserve(unsigned id);

/**
 * tegra_hv_mempool_release - release a reserved mempool
 * @ck		Cookie returned by tegra_hv_mempool_reserve().
 *
 * Returns 0 on success or a negative error code otherwise.
 */
int tegra_hv_mempool_unreserve(struct tegra_hv_ivm_cookie *ck);

/*
 * Returns the mempool pointer accessible in the current address space.
 */
void *tegra_hv_mempool_map(struct tegra_hv_ivm_cookie *ck);

/*
 * Unmap the mempool currently mapped to buf
 */
void tegra_hv_mempool_unmap(struct tegra_hv_ivm_cookie *ck, void *buf);

/**
 * ivc_channel_notified - handle internal messages
 * @ivck	IVC cookie of the queue
 *
 * This function must be called following every notification (interrupt or
 * callback invocation) for the tegra_hv_- version).
 *
 * Returns 0 if the channel is ready for communication, or -EAGAIN if a channel
 * reset is in progress.
 */
int tegra_hv_ivc_channel_notified(struct tegra_hv_ivc_cookie *ivck);
int32_t tegra_ivc_channel_notified(struct ivc *ivc);

/**
 * ivc_channel_reset - initiates a reset of the shared memory state
 * @ivck	IVC cookie of the queue
 *
 * This function must be called after a channel is reserved before it is used
 * for communication. The channel will be ready for use when a subsequent call
 * to ivc_channel_notified() returns 0.
 */
void tegra_hv_ivc_channel_reset(struct tegra_hv_ivc_cookie *ivck);
void tegra_ivc_channel_reset(struct ivc *ivc);

struct ivc *tegra_hv_ivc_convert_cookie(struct tegra_hv_ivc_cookie *ivck);

#endif /* IVCLIB_TEGRA_IVC_H */
