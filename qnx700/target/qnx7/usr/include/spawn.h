/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _SPAWN_H_INCLUDED
#define _SPAWN_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
# include <sys/types.h>
#endif

#ifndef _SIGNAL_H_INCLUDED
# include <signal.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
# include <sys/platform.h>
#endif

#include <_pack64.h>

__BEGIN_DECLS

#ifndef _SCHED_H_INCLUDED
# include <sched.h>
#endif


typedef _Uintptrt posix_spawnattr_t;
typedef _Uintptrt posix_spawn_file_actions_t;

extern int posix_spawnattr_init(posix_spawnattr_t *__attrp);
extern int posix_spawnattr_destroy(posix_spawnattr_t *__attrp);
extern int posix_spawnattr_getflags(const posix_spawnattr_t *_Restrict __attrp, short *_Restrict __flags_p);
extern int posix_spawnattr_setflags(posix_spawnattr_t *__attrp, short __flags);
extern int posix_spawnattr_getsigdefault(const posix_spawnattr_t *_Restrict __attrp, sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_setsigdefault(posix_spawnattr_t *_Restrict __attrp, const sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_getsigmask(const posix_spawnattr_t *_Restrict __attrp, sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_setsigmask(posix_spawnattr_t *_Restrict __attrp, const sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_getpgroup(const posix_spawnattr_t *_Restrict __attrp, pid_t *_Restrict __pid_p);
extern int posix_spawnattr_setpgroup(posix_spawnattr_t *__attrp, pid_t __pid);
struct __msg_sched_param;
extern int __posix_spawnattr_get_msgschedparam(const posix_spawnattr_t *_Restrict __attrp, struct __msg_sched_param *_Restrict __sched_p);
extern int posix_spawnattr_getschedparam(const posix_spawnattr_t *_Restrict __attrp, struct sched_param *_Restrict __sched_p);
extern int posix_spawnattr_setschedparam(posix_spawnattr_t *_Restrict __attrp, const struct sched_param *_Restrict __sched_p);
extern int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *_Restrict __attrp, int *_Restrict __policy_p);
extern int posix_spawnattr_setschedpolicy(posix_spawnattr_t *__attrp, int __policy);

extern int posix_spawn_file_actions_init(posix_spawn_file_actions_t *__fact_p);
extern int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *__fact_p);
extern int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *__fact_p, int __fd);
extern int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *__fact_p, int __fd, int __new_fd);
extern int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *_Restrict __fact_p, int __new_fd,
                                            const char *_Restrict __path, int __oflags, mode_t __omode);

extern int posix_spawn(
      pid_t *_Restrict                  __pid,
      const char *_Restrict             __path,
      const posix_spawn_file_actions_t * __file_actions,
      const posix_spawnattr_t *_Restrict __attrp,
      char * const                      __argv[_Restrict_arr],
      char * const                      __envp[_Restrict_arr] );
extern int posix_spawnp(
      pid_t *_Restrict                  __pid,
      const char *_Restrict             __file,
      const posix_spawn_file_actions_t * __file_actions,
      const posix_spawnattr_t *_Restrict __attrp,
      char * const                      __argv[_Restrict_arr],
      char * const                      __envp[_Restrict_arr] );

#define POSIX_SPAWN_SETPGROUP       0x00000001  /* set process group */
#define POSIX_SPAWN_SETSIGMASK      0x00000002  /* set mask to sigmask */
#define POSIX_SPAWN_SETSIGDEF       0x00000004  /* set members of sigdefault to SIG_DFL */
#define POSIX_SPAWN_RESETIDS        0x00000010  /* map childs euid/egid to parents ruid/rgid */
#define POSIX_SPAWN_SETSCHEDULER    0x00000040  /* set scheduler policy */
#define POSIX_SPAWN_SETSCHEDPARAM   0x00000400  /* set scheduling parameters */

/* QNX extensions */
#if defined(__EXT_QNX)

# define POSIX_SPAWN_SETSIGIGN       0x00000008  /* set members of sigignore to SIG_IGN */
# define POSIX_SPAWN_TCSETPGROUP     0x00000080  /* Start a new terminal group */
# define POSIX_SPAWN_SETND           0x00000100  /* spawn to remote node */
# define POSIX_SPAWN_SETSID          0x00000200  /* Make new process a session leader */
# define POSIX_SPAWN_EXPLICIT_CPU    0x00000800  /* Set the CPU affinity/runmask */
# define POSIX_SPAWN_SETSTACKMAX     0x00001000  /* Set the stack max */
# define POSIX_SPAWN_NOZOMBIE        0x00002000  /* Process will not zombie on death  */
# define POSIX_SPAWN_DEBUG           0x00004000  /* Debug process */
# define POSIX_SPAWN_HOLD            0x00008000  /* Hold a process for Debug */
# define POSIX_SPAWN_EXEC            0x00010000  /* Cause the spawn to act like exec() */
# define POSIX_SPAWN_SEARCH_PATH     0x00020000  /* Search envar PATH for executable */
# define POSIX_SPAWN_CHECK_SCRIPT    0x00040000  /* Allow starting a shell passing file as script */
# define POSIX_SPAWN_SETCRED         0x00080000  /* Set the uid/gid */
# define POSIX_SPAWN_ALIGN_DEFAULT   0x00000000  /* Use system default settings for alignment */
# define POSIX_SPAWN_ALIGN_FAULT     0x01000000  /* Try to always fault data misalignment references */
# define POSIX_SPAWN_ALIGN_NOFAULT   0x02000000  /* Don't fault on misalignment, and attempt to fix it (may be slow) */
# define POSIX_SPAWN_ASLR_INVERT	 0x08000000  /* If parent has ASLR, turn it off, if parent is off, turn it on: allows us to turn on/off with one bit */
# define POSIX_SPAWN_NEWAPP			 0x10000000  /* Assign the process a new application id */
# define POSIX_SPAWN_SETTYPEID       0x20000000  /* Assign security type to process */

extern int posix_spawnattr_getxflags(const posix_spawnattr_t *_Restrict __attrp, _Uint32t *_Restrict __flags_p);
extern int posix_spawnattr_setxflags(posix_spawnattr_t *__attrp, _Uint32t __flags);
extern int posix_spawnattr_getrunmask(const posix_spawnattr_t *_Restrict __attrp, _Uint32t *_Restrict __runmask_p);
extern int posix_spawnattr_setrunmask(posix_spawnattr_t *__attrp, _Uint32t __runmask);
extern int posix_spawnattr_getsigignore(const posix_spawnattr_t *_Restrict __attrp, sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_setsigignore(posix_spawnattr_t *_Restrict __attrp, const sigset_t *_Restrict __sigset_p);
extern int posix_spawnattr_getstackmax(const posix_spawnattr_t *_Restrict __attrp, _Uint32t *_Restrict size_p);
extern int posix_spawnattr_setstackmax(posix_spawnattr_t *__attrp, _Uint32t __size);
extern int posix_spawnattr_getnode(const posix_spawnattr_t *_Restrict __attrp, _Uint32t *_Restrict __node_p);
extern int posix_spawnattr_setnode(posix_spawnattr_t *__attrp, _Uint32t __node);
extern int posix_spawnattr_getcred(const posix_spawnattr_t *_Restrict __attrp, uid_t *_Restrict __uid_p, gid_t *_Restrict __gid_p);
extern int posix_spawnattr_setcred(posix_spawnattr_t *__attrp, uid_t __uid, gid_t __gid);
extern int posix_spawnattr_gettypeid(const posix_spawnattr_t *_Restrict __attrp, _Uint32t *_Restrict __type_id_p);
extern int posix_spawnattr_settypeid(posix_spawnattr_t *__attrp, _Uint32t __type_id);

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __INHERIT_FIELDS(__sched_type)														\
    _Uint32t	               	flags;														\
    pid_t                       pgroup;     /* SPAWN_SETGROUP must be set in flags */		\
    sigset_t                    sigmask;    /* SPAWN_SETSIGMASK must be set in flags */		\
    sigset_t                    sigdefault; /* SPAWN_SETSIGDEF must be set in flags */		\
    sigset_t                    sigignore;  /* SPAWN_SETSIGIGN must be set in flags */		\
    _Uint32t					stack_max;  /* SPAWN_SETSTACKMAX must be set in flags */	\
    _Int32t                     policy;     /* SPAWN_EXPLICIT_SCHED must be set in flags */	\
    _Uint32t                    nd;         /* SPAWN_SETND must be set in flags */			\
    _Uint32t                    runmask;    /* SPAWN_EXPLICIT_CPU must be set in flags */	\
    struct __sched_type         param;      /* SPAWN_EXPLICIT_SCHED must be set in flags */

typedef struct inheritance {
	__INHERIT_FIELDS(sched_param)
} spawn_inheritance_type;

struct __msg_timespec {
	_Uint32t	__tv_sec;
	_Uint32t	__tv_nsec;
};

__SCHED_PARAM_DEF(__msg_sched_param, __msg_timespec, __sched);

struct __msg_inheritance {
	__INHERIT_FIELDS(__msg_sched_param)
};

# define SPAWN_SETGROUP          POSIX_SPAWN_SETPGROUP
# define SPAWN_SETSIGMASK        POSIX_SPAWN_SETSIGMASK
# define SPAWN_SETSIGDEF         POSIX_SPAWN_SETSIGDEF
# define SPAWN_SETSIGIGN         POSIX_SPAWN_SETSIGIGN
# define SPAWN_TCSETPGROUP       POSIX_SPAWN_TCSETPGROUP
# define SPAWN_SETND             POSIX_SPAWN_SETND
# define SPAWN_SETSID            POSIX_SPAWN_SETSID  /* Make new process a session leader */
# define SPAWN_EXPLICIT_SCHED    POSIX_SPAWN_SETSCHEDPARAM
# define SPAWN_EXPLICIT_CPU      POSIX_SPAWN_EXPLICIT_CPU
# define SPAWN_SETSTACKMAX       POSIX_SPAWN_SETSTACKMAX
# define SPAWN_NOZOMBIE          POSIX_SPAWN_NOZOMBIE
# define SPAWN_DEBUG             POSIX_SPAWN_DEBUG  /* Debug process */
# define SPAWN_HOLD              POSIX_SPAWN_HOLD
# define SPAWN_EXEC              POSIX_SPAWN_EXEC  /* Cause the spawn to act like exec() */
# define SPAWN_SEARCH_PATH       POSIX_SPAWN_SEARCH_PATH  /* Search envar PATH for executable */
# define SPAWN_CHECK_SCRIPT      POSIX_SPAWN_CHECK_SCRIPT  /* Allow starting a shell passing file as script */
# define SPAWN_ALIGN_DEFAULT     POSIX_SPAWN_ALIGN_DEFAULT
# define SPAWN_ALIGN_FAULT       POSIX_SPAWN_ALIGN_FAULT
# define SPAWN_ALIGN_NOFAULT     POSIX_SPAWN_ALIGN_NOFAULT
# define SPAWN_ALIGN_MASK        0x03000000  /* Mask for align fault states below */
# define SPAWN_ASLR_INVERT 		 POSIX_SPAWN_ASLR_INVERT
# define SPAWN_NEWAPP	 		 POSIX_SPAWN_NEWAPP

# define SPAWN_FDCLOSED          (-1)
# define SPAWN_FDOPEN            (-2)
# define SPAWN_NEWPGROUP         0

extern pid_t spawn(const char *__path, int __fd_count, const int __fd_map[],
        const struct inheritance *__inherit, char * const __argv[], char * const __envp[]);
extern pid_t spawnp(const char *__file, int __fd_count, const int __fd_map[],
        const struct inheritance *__inherit, char * const __argv[], char * const __envp[]);

#endif  /* defined(__EXT_QNX) */

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/spawn.h $ $Rev: 822471 $")
#endif
