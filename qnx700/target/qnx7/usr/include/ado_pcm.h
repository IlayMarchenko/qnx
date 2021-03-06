/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */





/*
 *      ado_pcm.h
 *              The main header for the pcm devices.
 */

#ifndef _ADO_PCM_H_INCLUDED_
#define _ADO_PCM_H_INCLUDED_

#ifndef _MIXER_H_INCLUDED_
#include <sys/asound.h>
#include <ado_mixer.h>
#endif
#include <stdbool.h>

#define ADO_CHANNEL_UNSECURE				0
#define ADO_CHANNEL_SECURE					1

/***** typedefs *************/
typedef struct ado_pcm_cap					ado_pcm_cap_t;
typedef struct ado_pcm_hw					ado_pcm_hw_t;
typedef struct ado_pcm_dmabuf				ado_pcm_dmabuf_t;
typedef struct ado_pcm_mmap					ado_pcm_mmap_t;
typedef struct ado_pcm						ado_pcm_t;
typedef struct ado_pcm_chn					ado_pcm_chn_t;
typedef struct ado_pcm_config				ado_pcm_config_t;
typedef struct ado_pcm_subchn				ado_pcm_subchn_t;
typedef struct ado_pcm_link_group 			ado_pcm_link_group_t;
typedef struct ado_pcm_subchn_mixer 		ado_pcm_subchn_mixer_t;
typedef struct ado_pcm_subchn_mixer_config	ado_pcm_subchn_mixer_config_t;
typedef struct ado_pcm_devent               ado_pcm_devent_t;

enum	pcm_chn_type
{
	ADO_PCM_CHANNEL_PLAYBACK 	= SND_PCM_CHANNEL_PLAYBACK,
	ADO_PCM_CHANNEL_CAPTURE		= SND_PCM_CHANNEL_CAPTURE,
	ADO_PCM_CHANNEL_MAX
};

enum pcm_status
{
	ADO_PCM_STATUS_NOTREADY		= SND_PCM_STATUS_NOTREADY,
	ADO_PCM_STATUS_READY		= SND_PCM_STATUS_READY,
	ADO_PCM_STATUS_PREPARED		= SND_PCM_STATUS_PREPARED,
	ADO_PCM_STATUS_RUNNING		= SND_PCM_STATUS_RUNNING,
	ADO_PCM_STATUS_UNDERRUN		= SND_PCM_STATUS_UNDERRUN,
	ADO_PCM_STATUS_OVERRUN		= SND_PCM_STATUS_OVERRUN,
	ADO_PCM_STATUS_PAUSED		= SND_PCM_STATUS_PAUSED,
	ADO_PCM_STATUS_UNSECURE		= SND_PCM_STATUS_UNSECURE,
	ADO_PCM_STATUS_ERROR		= SND_PCM_STATUS_ERROR,
	ADO_PCM_STATUS_CHANGE		= SND_PCM_STATUS_CHANGE,
	ADO_PCM_STATUS_PREEMPTED	= SND_PCM_STATUS_PREEMPTED,
	ADO_PCM_STATUS_SUSPENDED	= SND_PCM_STATUS_SUSPENDED
};

enum pcm_transfer_mode
{
	ADO_PCM_MODE_UNKNOWN	= SND_PCM_MODE_UNKNOWN,
	ADO_PCM_MODE_BLOCK		= SND_PCM_MODE_BLOCK,
	ADO_PCM_MODE_STREAM		= SND_PCM_MODE_STREAM,
};

enum pcm_start_mode
{
	ADO_PCM_START_DATA	= PCM_START_DATA,
	ADO_PCM_START_FULL	= PCM_START_FULL,
	ADO_PCM_START_GO	= PCM_START_GO,
	ADO_PCM_START_MODE_COUNT,
};

enum pcm_stop_mode
{
	ADO_PCM_STOP_STOP		= SND_PCM_STOP_STOP,
	ADO_PCM_STOP_ROLLOVER	= SND_PCM_STOP_ROLLOVER,
	ADO_PCM_STOP_ROLLOVER_RESET = SND_PCM_STOP_ROLLOVER_RESET,
	ADO_PCM_STOP_MODE_COUNT,
};

enum pcm_trigger
{
	ADO_PCM_TRIGGER_STOP,
	ADO_PCM_TRIGGER_GO,
	ADO_PCM_TRIGGER_SYNC_GO
};

enum pcm_pause
{
	ADO_PCM_PAUSE_RESUME = ADO_PCM_TRIGGER_GO,
	ADO_PCM_PAUSE_PAUSE = ADO_PCM_TRIGGER_GO + 100,
	ADO_PCM_PAUSE_SUSPEND = ADO_PCM_TRIGGER_GO + 101,
	ADO_PCM_PAUSE_UNSUSPEND = ADO_PCM_TRIGGER_GO + 102,
};

/***** PCM sub-channel qualification flags ***********/
#define PCM_SUBCHN_TIME                     (1<<0)
#define PCM_SUBCHN_UST_TIME                 (1<<1)
/* Make sure never to send the data through any hardware or software module */
/* without giving the data source a chance to check that it approves of the */
/* protection mechanisms on that module */
#define PCM_SUBCHN_PROTECTED_CONTENT        (1<<2)
/* Request the recipient of data on this subchannel try to enable any content */
/* protection mechanisms that it supports */
#define PCM_SUBCHN_ENABLE_PROTECTION        (1<<3)
/* Fail playback if data on the subchannel would pass through any hardware or */
/* software where a user could tap the data */
#define PCM_SUBCHN_REQUIRE_PROTECTION       (1<<4)
/* Bit 5 is reserved for future use         (1<<5) */
/* Bit 6 is reserved for future use         (1<<6) */
/* In the process of reconfiguration. Resources associated with the channel */
/* may be cached */
#define PCM_SUBCHN_RECONFIGURING            (1<<7)

/* Mark as an internal AFM sub-channel */
#define PCM_SUBCHN_AFM                      (1<<8)
/* Bits 9 - 12 reserved for AFM types, encoded number, max 15
                                            (1<<9)
                                            (1<<10)
                                            (1<<11)
                                            (1<<12) */
/* Maximum number of AFM types */
#define PCM_SUBCHN_AFM_MAX_TYPES            0xF
/* Shift to access AFM type bits */
#define PCM_SUBCHN_AFM_TYPE_SHIFT           9
/* Mask to select AFM type bits */
#define PCM_SUBCHN_AFM_TYPE_MASK            (PCM_SUBCHN_AFM_MAX_TYPES<<PCM_SUBCHN_AFM_TYPE_SHIFT)
/* Reserve some specific AFM types */
#define PCM_SUBCHN_AFM_TYPE_ICC             (0<<PCM_SUBCHN_AFM_TYPE_SHIFT)
#define PCM_SUBCHN_AFM_TYPE_VOICE           (1<<PCM_SUBCHN_AFM_TYPE_SHIFT)
#define PCM_SUBCHN_AFM_TYPE_ESE             (2<<PCM_SUBCHN_AFM_TYPE_SHIFT)
#define PCM_SUBCHN_AFM_TYPE_ANC             (3<<PCM_SUBCHN_AFM_TYPE_SHIFT)

#define PCM_SUBCHN_LOGGING_ACTIVE           (1<<13)

/***** structures ***********/
struct	ado_pcm_cap
{
	uint32_t chn_flags;			/* SND_PCM_CHNINFO_* */
	uint32_t formats;			/* SND_PCM_FMT_* */
	uint32_t rates;				/* SND_PCM_RATE_* */
	uint32_t min_rate;			/* min rate */
	uint32_t max_rate;			/* max rate */
	struct	ratelist			/* used when SND_PCM_RATE_KNOT specified in rates */
	{
		int32_t		*list;
		uint32_t	list_len;
		void (*list_free)(void *data);
	}	ratelist;
	uint32_t min_voices;		/* min voices */
	uint32_t max_voices;		/* max voices */
	uint64_t voices_excluded;	/* excluded from range above */
	uint32_t min_fragsize;		/* min frag size */
	uint32_t max_fragsize;		/* max frag size */
	uint32_t max_dma_size;		/* maximum dma buffer size 0 == no limit */
	uint32_t max_frags;			/* maximum fragments 0 == no limit */
	uint32_t reserved[32];		/* reserved for future use */
};


struct	ado_pcm_hw
{
	int32_t	(*capabilities)(HW_CONTEXT_T *hw_context, ado_pcm_t *pcm, snd_pcm_channel_info_t *info );
	int32_t	(*aquire)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T **PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config, ado_pcm_subchn_t *subchn, uint32_t *why_failed );
	int32_t	(*release)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*prepare)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*trigger)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, uint32_t cmd);
	uint32_t (*position)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config, uint32_t *hw_buffer_level);
	int32_t (*reconstitute)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, int8_t *dmaptr, size_t size);
	int32_t (*pause)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, uint32_t cmd);
	int32_t	(*subchn_capabilities)(HW_CONTEXT_T *hw_context, ado_pcm_subchn_t *subchn, snd_pcm_channel_info_t *info );
	void   	(*reserved_18)();		/* reserved for future use */
	int32_t (*process)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, int8_t *dmaptr, size_t size);
	int32_t (*volume)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, int * min_step, int * max_step, int * current_step);
	int32_t (*mixer_subchn_trigger)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_subchn_t *subchn, uint32_t cmd);
	void   	(*reserved_17)();		/* reserved for future use */
	/* channel_map() returns a negative errno on error, data length/message size on success */
	int32_t	(*channel_map)(HW_CONTEXT_T *hw_context, ado_pcm_t *pcm, uint32_t dcmd, int channel_type, unsigned int **msgbuf, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT);
	void   	(*reserved_16)();		/* reserved for future use */
	void   	(*reserved_15)();		/* reserved for future use */
	void   	(*reserved_14)();		/* reserved for future use */
	void   	(*reserved_13)();		/* reserved for future use */
	void   	(*reserved_12)();		/* reserved for future use */
	void   	(*reserved_11)();		/* reserved for future use */
	void   	(*reserved_10)();		/* reserved for future use */
	void   	(*reserved_09)();		/* reserved for future use */
	void   	(*reserved_08)();		/* reserved for future use */
	void   	(*reserved_07)();		/* reserved for future use */
	void   	(*reserved_06)();		/* reserved for future use */
	void   	(*reserved_05)();		/* reserved for future use */
	void   	(*reserved_04)();		/* reserved for future use */
	void   	(*reserved_03)();		/* reserved for future use */
	void   	(*reserved_02)();		/* reserved for future use */
	void   	(*reserved_01)();		/* reserved for future use */
	void   	(*reserved_00)();		/* reserved for future use */
};


struct	ado_pcm_mmap	{
		snd_pcm_mmap_control_t	*control;
		size_t					size;
		char					name[QNX_SHM_NAME_LEN];
		uint32_t reserved[8];	/* reserved for future use */
};


struct	ado_pcm_dmabuf	{
		int8_t			*addr;
		size_t			size;
		uint32_t		flags; 		/* SEE ADO_SHMBUF_DMA_???? */
		off64_t			phys_addr;
		char			name[QNX_SHM_NAME_LEN];
		struct			cache_ctrl	*cache_ctrl;
		uint32_t		reserved[16];	/* reserved for future use */
};


struct	ado_pcm_config	{
	enum	pcm_transfer_mode	trans_mode;
	struct snd_pcm_format		format;
	union
	{
		struct
		{
			int32_t 		frag_size;
			int32_t			frags_min;
			int32_t			frags_max;
			int32_t			frags_total;
			ado_pcm_mmap_t	mmap;
			int32_t			frag_buffer_limit;		/* Lower limit of frags to try to keep buffered in low latency mode */
			int32_t			spare[7];				/* reserved for future use */
		} 	block;
		struct
		{
			int32_t			queue_size;
			int32_t			fill;
			int32_t			max_fill;
		}	stream;
	}							mode;
	ado_pcm_dmabuf_t			dmabuf;
	int32_t						mixer_device;	/* mixer device */
	snd_mixer_eid_t				mixer_eid;		/* pcm subchn source element */
	snd_mixer_gid_t 			mixer_gid;		/* lowest level mixer group subchn specific */
	char					sw_mixer_subchn_name[32];	/* sw_mixer subchn name override */
	uint32_t				cross_core_handle;			/* For cross-core access */
	uint32_t				reserved[23];		/* reserved for future use */
};


struct ado_pcm_subchn_mixer_config
{
	HW_CONTEXT_T		 				*hw_context;
	PCM_SUBCHN_CONTEXT_T 				*pcm_sc_context;
	uint32_t							channel_mask;
	uint32_t							volume_jointly:1;
	snd_mixer_element_volume1_range_t	volume_range;
	uint32_t							mute_jointly:1;
	uint32_t							spare_1[16];
	void		(*volume_set) (HW_CONTEXT_T * hw_context, PCM_SUBCHN_CONTEXT_T * pcm_sc_context, uint32_t * volumes, int32_t mute, ado_pcm_subchn_mixer_config_t *config);
	void		(*mute_set) (HW_CONTEXT_T * hw_context, PCM_SUBCHN_CONTEXT_T * pcm_sc_context,  uint32_t * volumes, int32_t mute, ado_pcm_subchn_mixer_config_t *config);
	uint32_t							spare_2[16];
};

/*** function prototypes ****/

/* pcm.c */
int32_t ado_pcm_create ( ado_card_t *card , const char *name , uint32_t flags , const char *id , uint32_t play_subchns , ado_pcm_cap_t *play_cap , ado_pcm_hw_t *play_hw , uint32_t cap_subchns , ado_pcm_cap_t *cap_cap , ado_pcm_hw_t *cap_hw , ado_mixer_t *mixer, ado_pcm_t **rpcm );
int32_t ado_pcm_destroy ( ado_pcm_t *pcm );
void ado_pcm_chn_mixer ( ado_pcm_t *pcm , enum pcm_chn_type type , ado_mixer_t *mixer , ado_mixer_delement_t *delement , ado_mixer_dgroup_t *dgroup );
void ado_pcm_subchn_mixer ( ado_pcm_subchn_t *subchn , ado_mixer_t *mixer , ado_mixer_delement_t *delement , ado_mixer_dgroup_t *dgroup );
uint32_t ado_pcm_playback_stop_artifact_protection( ado_pcm_subchn_t *subchn , uint16_t samples );
void dma_interrupt ( ado_pcm_subchn_t *subchn );
void dma_interrupt_n ( ado_pcm_subchn_t *subchn, uint32_t n, uint32_t max);
void dma_interrupt_checked ( ado_pcm_subchn_t *subchn, uint32_t n, uint32_t max, bool xrun_check);
int ado_pcm_underrun_check( ado_pcm_subchn_t *subchn );
int ado_pcm_overrun_check( ado_pcm_subchn_t *subchn );
int32_t ado_pcm_symname ( ado_pcm_t *pcm , enum pcm_chn_type type , const char *name );
const char * ado_pcm_get_symname ( ado_pcm_t *pcm, enum pcm_chn_type type );
int32_t ado_pcm_get_frags_used_n ( ado_pcm_subchn_t *subchn );
int32_t ado_pcm_error ( ado_pcm_subchn_t *subchn , int32_t status );
int32_t ado_pcm_subchn_state_lock ( ado_pcm_subchn_t * subchn, int count );
int32_t ado_pcm_subchn_state_unlock ( ado_pcm_subchn_t * subchn, int *count );

/* pcm_core.c */
int32_t ado_pcm_state (ado_pcm_t * pcm, enum pcm_chn_type type, uint32_t state, uint32_t pcm_chninfo_cap_flags, uint32_t pcminfo_flags);
int32_t ado_pcm_secure_state (ado_pcm_t * pcm, enum pcm_chn_type type, uint32_t state);
int32_t ado_pcm_restricted_state (ado_pcm_t * pcm, enum pcm_chn_type type, uint32_t state);
int32_t ado_pcm_preempt(ado_pcm_subchn_t *preempted_subchn, ado_pcm_subchn_t *replacement);


/* pcm_helper.c */
uint32_t ado_pcm_dma_int_size ( ado_pcm_config_t *config );
ado_pcm_cap_t *ado_pcm_subchn_caps ( ado_pcm_subchn_t *subchn );
pid_t ado_pcm_subchn_get_client_pid ( ado_pcm_subchn_t * subchn );
const char *ado_pcm_name( ado_pcm_t *pcm );
int ado_pcm_subchn_flags ( ado_pcm_subchn_t * subchn );
int32_t ado_pcm_subchn_is_channel ( ado_pcm_subchn_t *subchn , ado_pcm_t *pcm , enum pcm_chn_type chn_type );
size_t ado_pcm_format_bit_width ( int32_t format );
size_t ado_pcm_format_byte_width ( int32_t format );
int ado_pcm_format_little_endian (int format);
int ado_pcm_format_big_endian (int format);
int ado_pcm_format_variable_size (int32_t format);
int32_t ado_pcm_pick_best_format(uint32_t formats);
void ado_pcm_silence_fill ( void *buf , size_t length , int32_t format );
uint32_t ado_pcm_rate2flag ( uint32_t rate );
uint32_t ado_pcm_rates2flag ( uint32_t min_rate, uint32_t max_rate );
uint32_t ado_pcm_flag2rate ( uint32_t flag );
const char * ado_pcm_format_str (int format);
int ado_pcm_get_devno (ado_pcm_t *pcm);
void ado_pcm_subchn_set_start_time( ado_pcm_subchn_t * subchn, int32_t delay );
void ado_pcm_subchn_set_stop_time( ado_pcm_subchn_t * subchn, int32_t delay );
int ado_gcd(int value1, int value2);
int ado_lcm(int value1, int value2);


/* pcm_sw_mix.c */
int32_t ado_pcm_sw_mix ( ado_card_t *card , ado_pcm_t *pcm , ado_mixer_t *mixer );
ado_pcm_t *ado_get_sw_mix_pcm ( ado_card_t *card, ado_pcm_t *parent_pcm );
ado_pcm_t *ado_get_parent_pcm ( ado_pcm_t *pcm );
ado_pcm_subchn_t * ado_get_sw_mix_parent_subchn( HW_CONTEXT_T * psw );
int32_t ado_pcm_sw_mix_reconfig(ado_pcm_t *pcm, bool can_block);
int32_t ado_pcm_sw_mix_start_trigger( ado_pcm_t *pcm, int32_t frags_needed );
int32_t ado_get_pcm_sw_mix_start_trigger( ado_pcm_t *pcm, int32_t * frags_needed );

/* pcm_subchn_mixer.c */
void ado_pcm_subchn_mixer_destroy ( ado_pcm_subchn_mixer_t *sc_mixer );
ado_pcm_subchn_mixer_t *ado_pcm_subchn_mixer_create ( ado_pcm_subchn_t *subchn , ado_mixer_t *mixer , ado_pcm_subchn_mixer_config_t *config );

int	pcm_devctl (uint32_t cmd, uint8_t *msg, uint16_t *msg_size, HW_CONTEXT_T *context, ado_pcm_t *pcm, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT);

#endif /* _ADO_PCM_H_INCLUDED_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/audio/public/include/ado_pcm.h $ $Rev: 821827 $")
#endif
