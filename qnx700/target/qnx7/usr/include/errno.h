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

#ifndef _ERRNO_H_INCLUDED
#define _ERRNO_H_INCLUDED
#define _ERRNO_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__EXT_UNIX_MISC)
extern const char * const sys_errlist[];
extern const int sys_nerr;
#endif

extern int errno;
#ifndef errno
int *__get_errno_ptr(void) __attribute__((__const__));
# define errno (*__get_errno_ptr())
#endif

/* for c11 */
#ifdef __ERRNO_T
typedef __ERRNO_T errno_t;
#undef __ERRNO_T
#endif


__END_DECLS


/* --- Symbolic names of the error return conditions --- */

#define EOK              0  /* No error                                 */
#define EPERM            1  /* Operation not permitted                  */
#define ENOENT           2  /* No such file or directory                */
#define ESRCH            3  /* No such process                          */
#define EINTR            4  /* Interrupted function call                */
#define EIO              5  /* Input/output error                       */
#define ENXIO            6  /* No such device or address                */
#define E2BIG            7  /* Arg list too long                        */
#define ENOEXEC          8  /* Exec format error                        */
#define EBADF            9  /* Bad file descriptor                      */
#define ECHILD          10  /* No child processes                       */
#define EAGAIN          11  /* Resource temporarily unavailable         */
#define ENOMEM          12  /* Not enough memory                        */
#define EACCES          13  /* Permission denied                        */
#define EFAULT          14  /* Bad address                              */
#define ENOTBLK         15  /* Block device required                    */
#define EBUSY           16  /* Resource busy                            */
#define EEXIST          17  /* File exists                              */
#define EXDEV           18  /* Improper link                            */
#define ENODEV          19  /* No such device                           */
#define ENOTDIR         20  /* Not a directory                          */
#define EISDIR          21  /* Is a directory                           */
#define EINVAL          22  /* Invalid argument                         */
#define ENFILE          23  /* Too many open files in system            */
#define EMFILE          24  /* Too many open files                      */
#define ENOTTY          25  /* Inappropriate I/O control operation      */
#define ETXTBSY         26  /* Text file busy                           */
#define EFBIG           27  /* File too large                           */
#define ENOSPC          28  /* No space left on device                  */
#define ESPIPE          29  /* Invalid seek                             */
#define EROFS           30  /* Read-only file system                    */
#define EMLINK          31  /* Too many links                           */
#define EPIPE           32  /* Broken pipe                              */
#define EDOM            33  /* Domain error                             */
#define ERANGE          34  /* Result too large                         */
#define ENOMSG          35  /* No message of desired type               */
#define EIDRM           36  /* Identifier removed                       */
#define ECHRNG          37  /* Channel number out of range              */
#define EL2NSYNC        38  /* Level 2 not synchronized                 */
#define EL3HLT          39  /* Level 3 halted                           */
#define EL3RST          40  /* Level 3 reset                            */
#define ELNRNG          41  /* Link number out of range                 */
#define EUNATCH         42  /* Protocol driver not attached             */
#define ENOCSI          43  /* No CSI structure available               */
#define EL2HLT          44  /* Level 2 halted                           */
#define EDEADLK         45  /* Resource deadlock avoided                */
#define ENOLCK          46  /* No locks available                       */
#define ECANCELED       47  /* Operation canceled                       */
#define ENOTSUP         48  /* Not supported                            */

#define EDQUOT          49  /* Disc quota exceded                       */

#if 1 /* Convergent Error Returns */
#define EBADE           50  /* Invalid exchange                         */
#define EBADR           51  /* Invalid request descriptor               */
#define EXFULL          52  /* Exchange full                            */
#define ENOANO          53  /* No anode                                 */
#define EBADRQC         54  /* Invalid request code                     */
#define EBADSLT         55  /* Invalid slot                             */
#define EDEADLOCK       56  /* File locking deadlock                    */
#endif

#define EBFONT          57  /* Bad font file format                     */
#define EOWNERDEAD		58	/* Owner died holding lock					*/

#if 1 /* stream problems */
#define ENOSTR          60  /* Device not a stream                      */
#define ENODATA         61  /* No data (for no delay io)                */
#define ETIME           62  /* Timer expired                            */
#define ENOSR           63  /* Out of streams resources                 */
#endif

#define ENONET          64  /* Machine is not on network                */
#define ENOPKG          65  /* Package not installed                    */
#define EREMOTE         66  /* Too many levels of remote path           */
#define ENOLINK         67  /* The link has been severed                */
#define EADV            68  /* Advertise error                          */
#define ESRMNT          69  /* Srmount error                            */

#define ECOMM           70  /* Communication error on send              */
#define EPROTO          71  /* Protocol error                           */
#define EMULTIHOP       74  /* multihop attempted                       */
#define EBADMSG         77  /* Bad message                              */
#define ENAMETOOLONG    78  /* Filename too long                        */
#define EOVERFLOW       79  /* Value too large to be stored in datatype */
#define ENOTUNIQ        80  /* Given name not unique                    */
#define EBADFD          81  /* FD invalid for this operation            */
#define EREMCHG         82  /* Remote address changed                   */

/* --- Shared library errors --- */

#define ELIBACC         83  /* Can't access shared library              */
#define ELIBBAD         84  /* Accessing a corrupted shared lib         */
#define ELIBSCN         85  /* .lib section in a.out corrupted          */
#define ELIBMAX         86  /* Attempting to link in too many libs      */
#define ELIBEXEC        87  /* Attempting to exec a shared lib          */
#define EILSEQ          88  /* Illegal byte sequence.                   */

/* ----------------------------- */

#define ENOSYS          89  /* Function not implemented                 */
#define ELOOP           90  /* Too many levels of symbolic links or prefixes */
#define ERESTART        91  /* Restartable system call                  */
#define ESTRPIPE        92  /* if pipe/FIFO, don't sleep in stream head */
#define ENOTEMPTY       93  /* Directory not empty                      */
#define EUSERS          94  /* Too many users (for UFS)                 */
#define ENOTRECOVERABLE	95  /* Mutex-protected state not recoverable    */

#define EOPNOTSUPP      103 /* Operation not supported                  */
#define EFPOS			110 /* File position error                      */

#define ESTALE          122 /* Potentially recoverable i/o error        */

/* --- Sockets --- */

/* non-blocking and interrupt i/o */
/*        EAGAIN           35        */    /* Resource temporarily unavailable */
/*        EWOULDBLOCK      35        */    /* Operation would block */
#define EWOULDBLOCK    EAGAIN              /* Operation would block */
#define EINPROGRESS       236              /* Operation now in progress */
#define EALREADY      237              /* Operation already in progress POSIX conformance */

/* ipc/network software -- argument errors */
#define ENOTSOCK        238                /* Socket operation on non-socket */
#define EDESTADDRREQ    239                /* Destination address required */
#define EMSGSIZE        240                /* Message too long */
#define EPROTOTYPE      241                /* Protocol wrong type for socket */
#define ENOPROTOOPT     242                /* Protocol not available */
#define EPROTONOSUPPORT 243                /* Protocol not configured or not supported */
#define ESOCKTNOSUPPORT 244                /* Socket type not supported */
#define EPFNOSUPPORT    246                /* Protocol family not supported */
#define EAFNOSUPPORT    247                /* Address family not supported by protocol family */
#define EADDRINUSE      248                /* Address already in use */
#define EADDRNOTAVAIL   249                /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN        250                /* Network is down */
#define ENETUNREACH     251                /* Network is unreachable */
#define ENETRESET       252                /* Network dropped connection on reset */
#define ECONNABORTED    253                /* Software caused connection abort */
#define ECONNRESET      254                /* Connection reset by peer */
#define ENOBUFS         255                /* No buffer space available */
#define EISCONN         256                /* Socket is already connected */
#define ENOTCONN        257                /* Socket is not connected */
#define ESHUTDOWN       258                /* Can't send after socket shutdown */
#define ETOOMANYREFS    259                /* Too many references: can't splice */
#define ETIMEDOUT       260                /* Connection timed out */
#define ECONNREFUSED    261                /* Connection refused */

/*      ELOOP          62        */        /* Too many levels of symbolic links */
/*      ENAMETOOLONG   63        */        /* File name too long */

#define EHOSTDOWN        264                /* Host is down */
#define EHOSTUNREACH     265                /* No route to host */

/* Network File System */
/*      ESTALE           70     */          /* Stale NFS file handle */
/*      EREMOTE          71     */          /* Too many levels of remote in path */
#define EBADRPC         272                 /* RPC struct is bad */
#define ERPCMISMATCH    273                 /* RPC version wrong */
#define EPROGUNAVAIL    274                 /* RPC prog. not avail */
#define EPROGMISMATCH   275                 /* Program version wrong */
#define EPROCUNAVAIL    276                 /* Bad procedure for program */


/* --- QNX specific --- */

#define ENOREMOTE       300 /* Must be done on local machine           */
#define ENONDP          301 /* Need an NDP (8087...) to run            */
#define EBADFSYS        302 /* Corrupted file system detected          */
#define EMORE           309 /* More to do; send message again          */
#define ECTRLTERM       310 /* Remap to controlling terminal           */
#define ENOLIC          311 /* No license                              */
#define ESRVRFAULT      312 /* Server fault on msg pass                */
#define EENDIAN         313 /* Endian not supported                    */
#define ESECTYPEINVAL   314 /* Security type invalid                   */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/errno.h $ $Rev: 820925 $")
#endif
