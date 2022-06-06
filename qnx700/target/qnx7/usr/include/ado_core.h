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
 *      ado_core.h
 *              The core header for audio drivers.
 */

#ifndef _ADO_CORE_H_INCLUDED_
#define _ADO_CORE_H_INCLUDED_


/***** defines **************/
#define ADO_MAJOR_VERSION          5
#define AFM_MAJOR_VERSION          1

/**** Convenience Macro's ****/
#define ADO_ROUND_UP(n, sz) (((n) + ((sz) - 1)) & ~((sz) - 1)) /* sz must be a power of 2 */
#define ADO_ROUND_DOWN(n, sz) (n & ~((sz) - 1)) /* sz must be a power of 2 */

/*  Applications use procmgr_ability_lookup() with one of these paths and then
    pass that value to procmgr_ability().
*/
#define IOAUDIO_ABILITY_RESTRICTED_CAPTURE	"ioaudio/capturerestricted"
#define IOAUDIO_ABILITY_RESTRICTED_PLAYBACK	"ioaudio/playbackrestricted"

#define _IOAUDIO_ABILITY_INVALID			(-1)

/***** typedefs **************/
#ifndef	HW_CONTEXT_T
typedef	struct hw_context HW_CONTEXT_T;
#endif

#ifndef	PCM_SUBCHN_CONTEXT_T
typedef	struct pcm_subchn_context PCM_SUBCHN_CONTEXT_T;
#endif

#ifndef	MIXER_CONTEXT_T
typedef	struct mixer_context MIXER_CONTEXT_T;
#endif

#ifndef	POWER_CONTEXT_T
typedef	HW_CONTEXT_T POWER_CONTEXT_T;
#endif

typedef struct ado_card				ado_card_t;
typedef struct ado_dswitch			ado_dswitch_t;

typedef void (ado_dll_version_t) (int *major, int *minor, char *date);
typedef int32_t (ado_ctrl_dll_init_t) (HW_CONTEXT_T **hw_context, ado_card_t * card, char *args);
typedef int32_t (ado_ctrl_dll_destroy_t) (HW_CONTEXT_T *hw_context);

/* Supported resource manager abilities.  These are passed to iofunc_ability_check(). */
typedef enum _ioaudio_ability_e {
	/* Allow to record restricted audio */
	IOAUDIO_ABILITYID_RESTRICTED_CAPTURE,
	/* Allow to play restricted audio */
	IOAUDIO_ABILITYID_RESTRICTED_PLAYBACK,
} ioaudio_ability_e;

/* If the underlying hardware supports multiple sample rates, the rate method
 * is used to select which sample rate to configure the PCM Software mixer for.
 * NOTE: First Active refers to the sample rate requested by the first active
 *       client subchn
 */
typedef enum {
	SWMIX_RM_FAHQ,       /* First Active High Quality (44.1Khz and above) */
	SWMIX_RM_FA,         /* First Active                                  */
	SWMIX_RM_LOCKED      /* Locked to specified rate                      */
} swmix_rate_method_t;


/***** structures ************/
struct	global_options
{
int32_t		db_lvl;
int32_t		config_write_delay;			/* seconds 0=immediate,-1=never */
uint32_t	max_dma_buf_size;
uint16_t	status_accuracy;			/* required accuracy in ms */
uint16_t	disable_sw_mixer;			/* 0 to enable sw-mixer, 1 to disable */
uint32_t	intr_thread_prio;			/* priority of the interrupt thread */
uint32_t	data_thread_prio;			/* priority of data processing threads (ie. sw_mixer thread) */
uint32_t	sw_mixer_samples;
swmix_rate_method_t sw_mixer_rate_method;
uint32_t	sw_mixer_rate_rate;
uint16_t	buffered_playback;          /* Enable buffered playback */
uint16_t	sw_mixer_ms;                /* Alternative to sw_mixer_samples, ms has precedence */
uint16_t	line_perm_override;         /* Override phoneline permission check */
};

struct ado_interrupt;

/***** externs  **************/
extern	struct	global_options global_options;



/*** function prototypes ****/

/* intr.c */
int32_t ado_attach_interrupt ( ado_card_t *card , int32_t irq , void (*handler )(HW_CONTEXT_T *hw_context ,int32_t ), HW_CONTEXT_T *hw_context );
int32_t ado_attach_interrupt_named ( ado_card_t *card , int32_t irq , void (*handler )(HW_CONTEXT_T *hw_context ,int32_t ), HW_CONTEXT_T *hw_context, const char* name );
void ado_detach_interrupts ( ado_card_t *card );
int32_t ado_detach_interrupt ( ado_card_t *card , int32_t irq );


/* Untracked interrupt handlers can avoid thread contention and possiblely
 * avoid deadlocks due to inter-dependencies. Thus it is better to use
 * untracked interrupt interfaces if the interrupt handler is allocated and
 * freed frequently
 */
int32_t ado_attach_interrupt_named_untracked ( int32_t irq , void (*handler )(HW_CONTEXT_T *hw_context ,int32_t ), HW_CONTEXT_T *hw_context, const char* name, struct ado_interrupt ** intr );
int32_t ado_detach_interrupt_untracked ( struct ado_interrupt * intr );
int32_t ado_toggle_interrupt ( struct ado_interrupt * intr, int32_t on);

void ctrl_version (int *major, int *minor, char *date);
int32_t ctrl_init (HW_CONTEXT_T **hw_context, ado_card_t * card, char *args);
int32_t ctrl_destroy (HW_CONTEXT_T *hw_context);
int	ctrl_devctl (uint32_t cmd, uint8_t *msg, uint16_t *msg_size, HW_CONTEXT_T *context);

/* util.c */
int ado_default_authentication(resmgr_context_t *ctp);
int ado_ability_check(const resmgr_context_t * const ctp, const ioaudio_ability_e ioaudioability);

#endif	 /* _ADO_CORE_H_INCLUDED_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/audio/public/include/ado_core.h $ $Rev: 821116 $")
#endif
