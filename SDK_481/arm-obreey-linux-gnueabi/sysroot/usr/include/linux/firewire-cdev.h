/*
 * Char device interface.
 *
 * Copyright (C) 2005-2007  Kristian Hoegsberg <krh@bitplanet.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _LINUX_FIREWIRE_CDEV_H
#define _LINUX_FIREWIRE_CDEV_H

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/firewire-constants.h>

#define FW_CDEV_EVENT_BUS_RESET			0x00
#define FW_CDEV_EVENT_RESPONSE			0x01
#define FW_CDEV_EVENT_REQUEST			0x02
#define FW_CDEV_EVENT_ISO_INTERRUPT		0x03
#define FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED	0x04
#define FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED	0x05

/**
 * struct fw_cdev_event_common - Common part of all fw_cdev_event_ types
 * @closure:	For arbitrary use by userspace
 * @type:	Discriminates the fw_cdev_event_ types
 *
 * This struct may be used to access generic members of all fw_cdev_event_
 * types regardless of the specific type.
 *
 * Data passed in the @closure field for a request will be returned in the
 * corresponding event.  It is big enough to hold a pointer on all platforms.
 * The ioctl used to set @closure depends on the @type of event.
 */
struct fw_cdev_event_common {
	__u64 closure;
	__u32 type;
};

/**
 * struct fw_cdev_event_bus_reset - Sent when a bus reset occurred
 * @closure:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_GET_INFO ioctl
 * @type:	See &fw_cdev_event_common; always %FW_CDEV_EVENT_BUS_RESET
 * @node_id:       New node ID of this node
 * @local_node_id: Node ID of the local node, i.e. of the controller
 * @bm_node_id:    Node ID of the bus manager
 * @irm_node_id:   Node ID of the iso resource manager
 * @root_node_id:  Node ID of the root node
 * @generation:    New bus generation
 *
 * This event is sent when the bus the device belongs to goes through a bus
 * reset.  It provides information about the new bus configuration, such as
 * new node ID for this device, new root ID, and others.
 */
struct fw_cdev_event_bus_reset {
	__u64 closure;
	__u32 type;
	__u32 node_id;
	__u32 local_node_id;
	__u32 bm_node_id;
	__u32 irm_node_id;
	__u32 root_node_id;
	__u32 generation;
};

/**
 * struct fw_cdev_event_response - Sent when a response packet was received
 * @closure:	See &fw_cdev_event_common;
 *		set by %FW_CDEV_IOC_SEND_REQUEST ioctl
 * @type:	See &fw_cdev_event_common; always %FW_CDEV_EVENT_RESPONSE
 * @rcode:	Response code returned by the remote node
 * @length:	Data length, i.e. the response's payload size in bytes
 * @data:	Payload data, if any
 *
 * This event is sent when the stack receives a response to an outgoing request
 * sent by %FW_CDEV_IOC_SEND_REQUEST ioctl.  The payload data for responses
 * carrying data (read and lock responses) follows immediately and can be
 * accessed through the @data field.
 */
struct fw_cdev_event_response {
	__u64 closure;
	__u32 type;
	__u32 rcode;
	__u32 length;
	__u32 data[0];
};

/**
 * struct fw_cdev_event_request - Sent on incoming request to an address region
 * @closure:	See &fw_cdev_event_common; set by %FW_CDEV_IOC_ALLOCATE ioctl
 * @type:	See &fw_cdev_event_common; always %FW_CDEV_EVENT_REQUEST
 * @tcode:	Transaction code of the incoming request
 * @offset:	The offset into the 48-bit per-node address space
 * @handle:	Reference to the kernel-side pending request
 * @length:	Data length, i.e. the request's payload size in bytes
 * @data:	Incoming data, if any
 *
 * This event is sent when the stack receives an incoming request to an address
 * region registered using the %FW_CDEV_IOC_ALLOCATE ioctl.  The request is
 * guaranteed to be completely contained in the specified region.  Userspace is
 * responsible for sending the response by %FW_CDEV_IOC_SEND_RESPONSE ioctl,
 * using the same @handle.
 *
 * The payload data for requests carrying data (write and lock requests)
 * follows immediately and can be accessed through the @data field.
 */
struct fw_cdev_event_request {
	__u64 closure;
	__u32 type;
	__u32 tcode;
	__u64 offset;
	__u32 handle;
	__u32 length;
	__u32 data[0];
};

/**
 * struct fw_cdev_event_iso_interrupt - Sent when an iso packet was completed
 * @closure:	See &fw_cdev_event_common;
 *		set by %FW_CDEV_CREATE_ISO_CONTEXT ioctl
 * @type:	See &fw_cdev_event_common; always %FW_CDEV_EVENT_ISO_INTERRUPT
 * @cycle:	Cycle counter of the interrupt packet
 * @header_length: Total length of following headers, in bytes
 * @header:	Stripped headers, if any
 *
 * This event is sent when the controller has completed an &fw_cdev_iso_packet
 * with the %FW_CDEV_ISO_INTERRUPT bit set.  In the receive case, the headers
 * stripped of all packets up until and including the interrupt packet are
 * returned in the @header field.  The amount of header data per packet is as
 * specified at iso context creation by &fw_cdev_create_iso_context.header_size.
 *
 * In version 1 of this ABI, header data consisted of the 1394 isochronous
 * packet header, followed by quadlets from the packet payload if
 * &fw_cdev_create_iso_context.header_size > 4.
 *
 * In version 2 of this ABI, header data consist of the 1394 isochronous
 * packet header, followed by a timestamp quadlet if
 * &fw_cdev_create_iso_context.header_size > 4, followed by quadlets from the
 * packet payload if &fw_cdev_create_iso_context.header_size > 8.
 *
 * Behaviour of ver. 1 of this ABI is no longer available since ABI ver. 2.
 *
 * Format of 1394 iso packet header: 16 bits len, 2 bits tag, 6 bits channel,
 * 4 bits tcode, 4 bits sy, in big endian byte order.  Format of timestamp:
 * 16 bits invalid, 3 bits cycleSeconds, 13 bits cycleCount, in big endian byte
 * order.
 */
struct fw_cdev_event_iso_interrupt {
	__u64 closure;
	__u32 type;
	__u32 cycle;
	__u32 header_length;
	__u32 header[0];
};

/**
 * struct fw_cdev_event_iso_resource - Iso resources were allocated or freed
 * @closure:	See &fw_cdev_event_common;
 *		set by %FW_CDEV_IOC_(DE)ALLOCATE_ISO_RESOURCE(_ONCE) ioctl
 * @type:	%FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED or
 *		%FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED
 * @handle:	Reference by which an allocated resource can be deallocated
 * @channel:	Isochronous channel which was (de)allocated, if any
 * @bandwidth:	Bandwidth allocation units which were (de)allocated, if any
 *
 * An %FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED event is sent after an isochronous
 * resource was allocated at the IRM.  The client has to check @channel and
 * @bandwidth for whether the allocation actually succeeded.
 *
 * An %FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED event is sent after an isochronous
 * resource was deallocated at the IRM.  It is also sent when automatic
 * reallocation after a bus reset failed.
 *
 * @channel is <0 if no channel was (de)allocated or if reallocation failed.
 * @bandwidth is 0 if no bandwidth was (de)allocated or if reallocation failed.
 */
struct fw_cdev_event_iso_resource {
	__u64 closure;
	__u32 type;
	__u32 handle;
	__s32 channel;
	__s32 bandwidth;
};

/**
 * union fw_cdev_event - Convenience union of fw_cdev_event_ types
 * @common:        Valid for all types
 * @bus_reset:     Valid if @common.type == %FW_CDEV_EVENT_BUS_RESET
 * @response:      Valid if @common.type == %FW_CDEV_EVENT_RESPONSE
 * @request:       Valid if @common.type == %FW_CDEV_EVENT_REQUEST
 * @iso_interrupt: Valid if @common.type == %FW_CDEV_EVENT_ISO_INTERRUPT
 * @iso_resource:  Valid if @common.type ==
 *				%FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED or
 *				%FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED
 *
 * Convenience union for userspace use.  Events could be read(2) into an
 * appropriately aligned char buffer and then cast to this union for further
 * processing.  Note that for a request, response or iso_interrupt event,
 * the data[] or header[] may make the size of the full event larger than
 * sizeof(union fw_cdev_event).  Also note that if you attempt to read(2)
 * an event into a buffer that is not large enough for it, the data that does
 * not fit will be discarded so that the next read(2) will return a new event.
 */
union fw_cdev_event {
	struct fw_cdev_event_common		common;
	struct fw_cdev_event_bus_reset		bus_reset;
	struct fw_cdev_event_response		response;
	struct fw_cdev_event_request		request;
	struct fw_cdev_event_iso_interrupt	iso_interrupt;
	struct fw_cdev_event_iso_resource	iso_resource;
};

/* available since kernel version 2.6.22 */
#define FW_CDEV_IOC_GET_INFO           _IOWR('#', 0x00, struct fw_cdev_get_info)
#define FW_CDEV_IOC_SEND_REQUEST        _IOW('#', 0x01, struct fw_cdev_send_request)
#define FW_CDEV_IOC_ALLOCATE           _IOWR('#', 0x02, struct fw_cdev_allocate)
#define FW_CDEV_IOC_DEALLOCATE          _IOW('#', 0x03, struct fw_cdev_deallocate)
#define FW_CDEV_IOC_SEND_RESPONSE       _IOW('#', 0x04, struct fw_cdev_send_response)
#define FW_CDEV_IOC_INITIATE_BUS_RESET  _IOW('#', 0x05, struct fw_cdev_initiate_bus_reset)
#define FW_CDEV_IOC_ADD_DESCRIPTOR     _IOWR('#', 0x06, struct fw_cdev_add_descriptor)
#define FW_CDEV_IOC_REMOVE_DESCRIPTOR   _IOW('#', 0x07, struct fw_cdev_remove_descriptor)
#define FW_CDEV_IOC_CREATE_ISO_CONTEXT _IOWR('#', 0x08, struct fw_cdev_create_iso_context)
#define FW_CDEV_IOC_QUEUE_ISO          _IOWR('#', 0x09, struct fw_cdev_queue_iso)
#define FW_CDEV_IOC_START_ISO           _IOW('#', 0x0a, struct fw_cdev_start_iso)
#define FW_CDEV_IOC_STOP_ISO            _IOW('#', 0x0b, struct fw_cdev_stop_iso)

/* available since kernel version 2.6.24 */
#define FW_CDEV_IOC_GET_CYCLE_TIMER     _IOR('#', 0x0c, struct fw_cdev_get_cycle_timer)

/* available since kernel version 2.6.30 */
#define FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE       _IOWR('#', 0x0d, struct fw_cdev_allocate_iso_resource)
#define FW_CDEV_IOC_DEALLOCATE_ISO_RESOURCE      _IOW('#', 0x0e, struct fw_cdev_deallocate)
#define FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE_ONCE   _IOW('#', 0x0f, struct fw_cdev_allocate_iso_resource)
#define FW_CDEV_IOC_DEALLOCATE_ISO_RESOURCE_ONCE _IOW('#', 0x10, struct fw_cdev_allocate_iso_resource)
#define FW_CDEV_IOC_GET_SPEED                     _IO('#', 0x11) /* returns speed code */
#define FW_CDEV_IOC_SEND_BROADCAST_REQUEST       _IOW('#', 0x12, struct fw_cdev_send_request)
#define FW_CDEV_IOC_SEND_STREAM_PACKET           _IOW('#', 0x13, struct fw_cdev_send_stream_packet)

/* available since kernel version 2.6.34 */
#define FW_CDEV_IOC_GET_CYCLE_TIMER2   _IOWR('#', 0x14, struct fw_cdev_get_cycle_timer2)

/*
 * FW_CDEV_VERSION History
 *  1  (2.6.22)  - initial version
 *  2  (2.6.30)  - changed &fw_cdev_event_iso_interrupt.header if
 *                 &fw_cdev_create_iso_context.header_size is 8 or more
 *     (2.6.32)  - added time stamp to xmit &fw_cdev_event_iso_interrupt
 *     (2.6.33)  - IR has always packet-per-buffer semantics now, not one of
 *                 dual-buffer or packet-per-buffer depending on hardware
 *  3  (2.6.34)  - made &fw_cdev_get_cycle_timer reliable
 */
#define FW_CDEV_VERSION 3

/**
 * struct fw_cdev_get_info - General purpose information ioctl
 * @version:	The version field is just a running serial number.
 *		We never break backwards compatibility, but may add more
 *		structs and ioctls in later revisions.
 * @rom_length:	If @rom is non-zero, at most rom_length bytes of configuration
 *		ROM will be copied into that user space address.  In either
 *		case, @rom_length is updated with the actual length of the
 *		configuration ROM.
 * @rom:	If non-zero, address of a buffer to be filled by a copy of the
 *		device's configuration ROM
 * @bus_reset:	If non-zero, address of a buffer to be filled by a
 *		&struct fw_cdev_event_bus_reset with the current state
 *		of the bus.  This does not cause a bus reset to happen.
 * @bus_reset_closure: Value of &closure in this and subsequent bus reset events
 * @card:	The index of the card this device belongs to
 */
struct fw_cdev_get_info {
	__u32 version;
	__u32 rom_length;
	__u64 rom;
	__u64 bus_reset;
	__u64 bus_reset_closure;
	__u32 card;
};

/**
 * struct fw_cdev_send_request - Send an asynchronous request packet
 * @tcode:	Transaction code of the request
 * @length:	Length of outgoing payload, in bytes
 * @offset:	48-bit offset at destination node
 * @closure:	Passed back to userspace in the response event
 * @data:	Userspace pointer to payload
 * @generation:	The bus generation where packet is valid
 *
 * Send a request to the device.  This ioctl implements all outgoing requests.
 * Both quadlet and block request specify the payload as a pointer to the data
 * in the @data field.  Once the transaction completes, the kernel writes an
 * &fw_cdev_event_response event back.  The @closure field is passed back to
 * user space in the response event.
 */
struct fw_cdev_send_request {
	__u32 tcode;
	__u32 length;
	__u64 offset;
	__u64 closure;
	__u64 data;
	__u32 generation;
};

/**
 * struct fw_cdev_send_response - Send an asynchronous response packet
 * @rcode:	Response code as determined by the userspace handler
 * @length:	Length of outgoing payload, in bytes
 * @data:	Userspace pointer to payload
 * @handle:	The handle from the &fw_cdev_event_request
 *
 * Send a response to an incoming request.  By setting up an address range using
 * the %FW_CDEV_IOC_ALLOCATE ioctl, userspace can listen for incoming requests.  An
 * incoming request will generate an %FW_CDEV_EVENT_REQUEST, and userspace must
 * send a reply using this ioctl.  The event has a handle to the kernel-side
 * pending transaction, which should be used with this ioctl.
 */
struct fw_cdev_send_response {
	__u32 rcode;
	__u32 length;
	__u64 data;
	__u32 handle;
};

/**
 * struct fw_cdev_allocate - Allocate a CSR address range
 * @offset:	Start offset of the address range
 * @closure:	To be passed back to userspace in request events
 * @length:	Length of the address range, in bytes
 * @handle:	Handle to the allocation, written by the kernel
 *
 * Allocate an address range in the 48-bit address space on the local node
 * (the controller).  This allows userspace to listen for requests with an
 * offset within that address range.  When the kernel receives a request
 * within the range, an &fw_cdev_event_request event will be written back.
 * The @closure field is passed back to userspace in the response event.
 * The @handle field is an out parameter, returning a handle to the allocated
 * range to be used for later deallocation of the range.
 *
 * The address range is allocated on all local nodes.  The address allocation
 * is exclusive except for the FCP command and response registers.
 */
struct fw_cdev_allocate {
	__u64 offset;
	__u64 closure;
	__u32 length;
	__u32 handle;
};

/**
 * struct fw_cdev_deallocate - Free a CSR address range or isochronous resource
 * @handle:	Handle to the address range or iso resource, as returned by the
 *		kernel when the range or resource was allocated
 */
struct fw_cdev_deallocate {
	__u32 handle;
};

#define FW_CDEV_LONG_RESET	0
#define FW_CDEV_SHORT_RESET	1

/**
 * struct fw_cdev_initiate_bus_reset - Initiate a bus reset
 * @type:	%FW_CDEV_SHORT_RESET or %FW_CDEV_LONG_RESET
 *
 * Initiate a bus reset for the bus this device is on.  The bus reset can be
 * either the original (long) bus reset or the arbitrated (short) bus reset
 * introduced in 1394a-2000.
 */
struct fw_cdev_initiate_bus_reset {
	__u32 type;	/* FW_CDEV_SHORT_RESET or FW_CDEV_LONG_RESET */
};

/**
 * struct fw_cdev_add_descriptor - Add contents to the local node's config ROM
 * @immediate:	If non-zero, immediate key to insert before pointer
 * @key:	Upper 8 bits of root directory pointer
 * @data:	Userspace pointer to contents of descriptor block
 * @length:	Length of descriptor block data, in quadlets
 * @handle:	Handle to the descriptor, written by the kernel
 *
 * Add a descriptor block and optionally a preceding immediate key to the local
 * node's configuration ROM.
 *
 * The @key field specifies the upper 8 bits of the descriptor root directory
 * pointer and the @data and @length fields specify the contents. The @key
 * should be of the form 0xXX000000. The offset part of the root directory entry
 * will be filled in by the kernel.
 *
 * If not 0, the @immediate field specifies an immediate key which will be
 * inserted before the root directory pointer.
 *
 * @immediate, @key, and @data array elements are CPU-endian quadlets.
 *
 * If successful, the kernel adds the descriptor and writes back a handle to the
 * kernel-side object to be used for later removal of the descriptor block and
 * immediate key.
 *
 * This ioctl affects the configuration ROMs of all local nodes.
 * The ioctl only succeeds on device files which represent a local node.
 */
struct fw_cdev_add_descriptor {
	__u32 immediate;
	__u32 key;
	__u64 data;
	__u32 length;
	__u32 handle;
};

/**
 * struct fw_cdev_remove_descriptor - Remove contents from the configuration ROM
 * @handle:	Handle to the descriptor, as returned by the kernel when the
 *		descriptor was added
 *
 * Remove a descriptor block and accompanying immediate key from the local
 * nodes' configuration ROMs.
 */
struct fw_cdev_remove_descriptor {
	__u32 handle;
};

#define FW_CDEV_ISO_CONTEXT_TRANSMIT	0
#define FW_CDEV_ISO_CONTEXT_RECEIVE	1

/**
 * struct fw_cdev_create_iso_context - Create a context for isochronous IO
 * @type:	%FW_CDEV_ISO_CONTEXT_TRANSMIT or %FW_CDEV_ISO_CONTEXT_RECEIVE
 * @header_size: Header size to strip for receive contexts
 * @channel:	Channel to bind to
 * @speed:	Speed for transmit contexts
 * @closure:	To be returned in &fw_cdev_event_iso_interrupt
 * @handle:	Handle to context, written back by kernel
 *
 * Prior to sending or receiving isochronous I/O, a context must be created.
 * The context records information about the transmit or receive configuration
 * and typically maps to an underlying hardware resource.  A context is set up
 * for either sending or receiving.  It is bound to a specific isochronous
 * channel.
 *
 * If a context was successfully created, the kernel writes back a handle to the
 * context, which must be passed in for subsequent operations on that context.
 *
 * For receive contexts, @header_size must be at least 4 and must be a multiple
 * of 4.
 *
 * Note that the effect of a @header_size > 4 depends on
 * &fw_cdev_get_info.version, as documented at &fw_cdev_event_iso_interrupt.
 */
struct fw_cdev_create_iso_context {
	__u32 type;
	__u32 header_size;
	__u32 channel;
	__u32 speed;
	__u64 closure;
	__u32 handle;
};

#define FW_CDEV_ISO_PAYLOAD_LENGTH(v)	(v)
#define FW_CDEV_ISO_INTERRUPT		(1 << 16)
#define FW_CDEV_ISO_SKIP		(1 << 17)
#define FW_CDEV_ISO_SYNC		(1 << 17)
#define FW_CDEV_ISO_TAG(v)		((v) << 18)
#define FW_CDEV_ISO_SY(v)		((v) << 20)
#define FW_CDEV_ISO_HEADER_LENGTH(v)	((v) << 24)

/**
 * struct fw_cdev_iso_packet - Isochronous packet
 * @control:	Contains the header length (8 uppermost bits), the sy field
 *		(4 bits), the tag field (2 bits), a sync flag (1 bit),
 *		a skip flag (1 bit), an interrupt flag (1 bit), and the
 *		payload length (16 lowermost bits)
 * @header:	Header and payload
 *
 * &struct fw_cdev_iso_packet is used to describe isochronous packet queues.
 *
 * Use the FW_CDEV_ISO_ macros to fill in @control.
 *
 * For transmit packets, the header length must be a multiple of 4 and specifies
 * the numbers of bytes in @header that will be prepended to the packet's
 * payload; these bytes are copied into the kernel and will not be accessed
 * after the ioctl has returned.  The sy and tag fields are copied to the iso
 * packet header (these fields are specified by IEEE 1394a and IEC 61883-1).
 * The skip flag specifies that no packet is to be sent in a frame; when using
 * this, all other fields except the interrupt flag must be zero.
 *
 * For receive packets, the header length must be a multiple of the context's
 * header size; if the header length is larger than the context's header size,
 * multiple packets are queued for this entry.  The sy and tag fields are
 * ignored.  If the sync flag is set, the context drops all packets until
 * a packet with a matching sy field is received (the sync value to wait for is
 * specified in the &fw_cdev_start_iso structure).  The payload length defines
 * how many payload bytes can be received for one packet (in addition to payload
 * quadlets that have been defined as headers and are stripped and returned in
 * the &fw_cdev_event_iso_interrupt structure).  If more bytes are received, the
 * additional bytes are dropped.  If less bytes are received, the remaining
 * bytes in this part of the payload buffer will not be written to, not even by
 * the next packet, i.e., packets received in consecutive frames will not
 * necessarily be consecutive in memory.  If an entry has queued multiple
 * packets, the payload length is divided equally among them.
 *
 * When a packet with the interrupt flag set has been completed, the
 * &fw_cdev_event_iso_interrupt event will be sent.  An entry that has queued
 * multiple receive packets is completed when its last packet is completed.
 */
struct fw_cdev_iso_packet {
	__u32 control;
	__u32 header[0];
};

/**
 * struct fw_cdev_queue_iso - Queue isochronous packets for I/O
 * @packets:	Userspace pointer to packet data
 * @data:	Pointer into mmap()'ed payload buffer
 * @size:	Size of packet data in bytes
 * @handle:	Isochronous context handle
 *
 * Queue a number of isochronous packets for reception or transmission.
 * This ioctl takes a pointer to an array of &fw_cdev_iso_packet structs,
 * which describe how to transmit from or receive into a contiguous region
 * of a mmap()'ed payload buffer.  As part of transmit packet descriptors,
 * a series of headers can be supplied, which will be prepended to the
 * payload during DMA.
 *
 * The kernel may or may not queue all packets, but will write back updated
 * values of the @packets, @data and @size fields, so the ioctl can be
 * resubmitted easily.
 */
struct fw_cdev_queue_iso {
	__u64 packets;
	__u64 data;
	__u32 size;
	__u32 handle;
};

#define FW_CDEV_ISO_CONTEXT_MATCH_TAG0		 1
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG1		 2
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG2		 4
#define FW_CDEV_ISO_CONTEXT_MATCH_TAG3		 8
#define FW_CDEV_ISO_CONTEXT_MATCH_ALL_TAGS	15

/**
 * struct fw_cdev_start_iso - Start an isochronous transmission or reception
 * @cycle:	Cycle in which to start I/O.  If @cycle is greater than or
 *		equal to 0, the I/O will start on that cycle.
 * @sync:	Determines the value to wait for for receive packets that have
 *		the %FW_CDEV_ISO_SYNC bit set
 * @tags:	Tag filter bit mask.  Only valid for isochronous reception.
 *		Determines the tag values for which packets will be accepted.
 *		Use FW_CDEV_ISO_CONTEXT_MATCH_ macros to set @tags.
 * @handle:	Isochronous context handle within which to transmit or receive
 */
struct fw_cdev_start_iso {
	__s32 cycle;
	__u32 sync;
	__u32 tags;
	__u32 handle;
};

/**
 * struct fw_cdev_stop_iso - Stop an isochronous transmission or reception
 * @handle:	Handle of isochronous context to stop
 */
struct fw_cdev_stop_iso {
	__u32 handle;
};

/**
 * struct fw_cdev_get_cycle_timer - read cycle timer register
 * @local_time:   system time, in microseconds since the Epoch
 * @cycle_timer:  Cycle Time register contents
 *
 * The %FW_CDEV_IOC_GET_CYCLE_TIMER ioctl reads the isochronous cycle timer
 * and also the system clock (%CLOCK_REALTIME).  This allows to express the
 * receive time of an isochronous packet as a system time.
 *
 * @cycle_timer consists of 7 bits cycleSeconds, 13 bits cycleCount, and
 * 12 bits cycleOffset, in host byte order.  Cf. the Cycle Time register
 * per IEEE 1394 or Isochronous Cycle Timer register per OHCI-1394.
 *
 * In version 1 and 2 of the ABI, this ioctl returned unreliable (non-
 * monotonic) @cycle_timer values on certain controllers.
 */
struct fw_cdev_get_cycle_timer {
	__u64 local_time;
	__u32 cycle_timer;
};

/**
 * struct fw_cdev_get_cycle_timer2 - read cycle timer register
 * @tv_sec:       system time, seconds
 * @tv_nsec:      system time, sub-seconds part in nanoseconds
 * @clk_id:       input parameter, clock from which to get the system time
 * @cycle_timer:  Cycle Time register contents
 *
 * The %FW_CDEV_IOC_GET_CYCLE_TIMER2 works like
 * %FW_CDEV_IOC_GET_CYCLE_TIMER but lets you choose a clock like with POSIX'
 * clock_gettime function.  Supported @clk_id values are POSIX' %CLOCK_REALTIME
 * and %CLOCK_MONOTONIC and Linux' %CLOCK_MONOTONIC_RAW.
 */
struct fw_cdev_get_cycle_timer2 {
	__s64 tv_sec;
	__s32 tv_nsec;
	__s32 clk_id;
	__u32 cycle_timer;
};

/**
 * struct fw_cdev_allocate_iso_resource - (De)allocate a channel or bandwidth
 * @closure:	Passed back to userspace in correponding iso resource events
 * @channels:	Isochronous channels of which one is to be (de)allocated
 * @bandwidth:	Isochronous bandwidth units to be (de)allocated
 * @handle:	Handle to the allocation, written by the kernel (only valid in
 *		case of %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE ioctls)
 *
 * The %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE ioctl initiates allocation of an
 * isochronous channel and/or of isochronous bandwidth at the isochronous
 * resource manager (IRM).  Only one of the channels specified in @channels is
 * allocated.  An %FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED is sent after
 * communication with the IRM, indicating success or failure in the event data.
 * The kernel will automatically reallocate the resources after bus resets.
 * Should a reallocation fail, an %FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED event
 * will be sent.  The kernel will also automatically deallocate the resources
 * when the file descriptor is closed.
 *
 * The %FW_CDEV_IOC_DEALLOCATE_ISO_RESOURCE ioctl can be used to initiate
 * deallocation of resources which were allocated as described above.
 * An %FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED event concludes this operation.
 *
 * The %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE_ONCE ioctl is a variant of allocation
 * without automatic re- or deallocation.
 * An %FW_CDEV_EVENT_ISO_RESOURCE_ALLOCATED event concludes this operation,
 * indicating success or failure in its data.
 *
 * The %FW_CDEV_IOC_DEALLOCATE_ISO_RESOURCE_ONCE ioctl works like
 * %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE_ONCE except that resources are freed
 * instead of allocated.
 * An %FW_CDEV_EVENT_ISO_RESOURCE_DEALLOCATED event concludes this operation.
 *
 * To summarize, %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE allocates iso resources
 * for the lifetime of the fd or @handle.
 * In contrast, %FW_CDEV_IOC_ALLOCATE_ISO_RESOURCE_ONCE allocates iso resources
 * for the duration of a bus generation.
 *
 * @channels is a host-endian bitfield with the least significant bit
 * representing channel 0 and the most significant bit representing channel 63:
 * 1ULL << c for each channel c that is a candidate for (de)allocation.
 *
 * @bandwidth is expressed in bandwidth allocation units, i.e. the time to send
 * one quadlet of data (payload or header data) at speed S1600.
 */
struct fw_cdev_allocate_iso_resource {
	__u64 closure;
	__u64 channels;
	__u32 bandwidth;
	__u32 handle;
};

/**
 * struct fw_cdev_send_stream_packet - send an asynchronous stream packet
 * @length:	Length of outgoing payload, in bytes
 * @tag:	Data format tag
 * @channel:	Isochronous channel to transmit to
 * @sy:		Synchronization code
 * @closure:	Passed back to userspace in the response event
 * @data:	Userspace pointer to payload
 * @generation:	The bus generation where packet is valid
 * @speed:	Speed to transmit at
 *
 * The %FW_CDEV_IOC_SEND_STREAM_PACKET ioctl sends an asynchronous stream packet
 * to every device which is listening to the specified channel.  The kernel
 * writes an &fw_cdev_event_response event which indicates success or failure of
 * the transmission.
 */
struct fw_cdev_send_stream_packet {
	__u32 length;
	__u32 tag;
	__u32 channel;
	__u32 sy;
	__u64 closure;
	__u64 data;
	__u32 generation;
	__u32 speed;
};

#endif /* _LINUX_FIREWIRE_CDEV_H */
