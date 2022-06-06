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
 *  termios.h   Terminal I/O system types
 *

 */
#ifndef _TERMIOS_H_INCLUDED
#define _TERMIOS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#include <_pack64.h>

#define NCCS    40

typedef unsigned char   cc_t;
typedef _Uint32t         speed_t;
typedef _Uint32t        tcflag_t;
struct termios {
    tcflag_t        c_iflag;    /* Input Modes */
    tcflag_t        c_oflag;    /* Ouput modes */
    tcflag_t        c_cflag;    /* Control Modes */
    tcflag_t        c_lflag;    /* Local Modes */
    cc_t            c_cc[NCCS]; /* Control Characters */
	_Uint32t		__reserved[3];
    speed_t         c_ispeed;   /* Input Baud rate */
    speed_t         c_ospeed;   /* Output baud rate */
};
/*
 * Input modes
 */

#define IGNBRK      ((tcflag_t)0x00000001)
#define BRKINT      ((tcflag_t)0x00000002)
#define IGNPAR      ((tcflag_t)0x00000004)
#define PARMRK      ((tcflag_t)0x00000008)
#define INPCK       ((tcflag_t)0x00000010)
#define ISTRIP      ((tcflag_t)0x00000020)
#define INLCR       ((tcflag_t)0x00000040)
#define IGNCR       ((tcflag_t)0x00000080)
#define ICRNL       ((tcflag_t)0x00000100)  /* map CR to NL on output (CRMOD) */
#define IXON        ((tcflag_t)0x00000400)
#define IXOFF       ((tcflag_t)0x00001000)
#if defined(__EXT_XOPEN_EX)
#define IUCLC       ((tcflag_t)0x00000200)
#define IXANY       ((tcflag_t)0x00000800)
#endif
#if defined(__EXT_UNIX_MISC)
#define IMAXBEL		((tcflag_t)0x00002000)
#endif
#define TC_IPOSIX   (BRKINT|ICRNL|IGNBRK|IGNPAR|INLCR|INPCK|ISTRIP|IXOFF|IXON|PARMRK)

/*
 * Ouput Modes
 */

#define OPOST       ((tcflag_t)0x00000001)
#if defined(__EXT_XOPEN_EX)
#define OLCUC       ((tcflag_t)0x00000002)
#define ONLCR       ((tcflag_t)0x00000004)  /* map NL to CRNL on output (CRMOD) */
#define OCRNL       ((tcflag_t)0x00000008)
#define ONOCR       ((tcflag_t)0x00000010)
#define ONLRET      ((tcflag_t)0x00000020)
#define OFILL       ((tcflag_t)0x00000040)
#define OFDEL       ((tcflag_t)0x00000080)
#define NLDLY       ((tcflag_t)0x00000100)
#define NL0              ((tcflag_t)0x000)
#define NL1              ((tcflag_t)0x100)          /* tty 37 */
#define CRDLY       ((tcflag_t)0x00000600)
#define CR0              ((tcflag_t)0x000)
#define CR1              ((tcflag_t)0x200)          /* tn 300 */
#define CR2              ((tcflag_t)0x400)          /* tty 37 */
#define CR3              ((tcflag_t)0x600)          /* concept 100 */
#define TABDLY      ((tcflag_t)0x00001800)
#define TAB0            ((tcflag_t)0x0000)
#define TAB1            ((tcflag_t)0x0800)          /* tty 37 */
#define TAB2            ((tcflag_t)0x1000)
#define TAB3            ((tcflag_t)0x1800)          /* expand tabs to spaces */
#define BSDLY       ((tcflag_t)0x00002000)
#define BS0             ((tcflag_t)0x0000)
#define BS1             ((tcflag_t)0x2000)
#define VTDLY       ((tcflag_t)0x00004000)
#define VT0             ((tcflag_t)0x0000)
#define VT1             ((tcflag_t)0x4000)
#define FFDLY       ((tcflag_t)0x00008000)
#define FF0             ((tcflag_t)0x0000)
#define FF1             ((tcflag_t)0x8000)
#endif
#define TC_OPOSIX (OPOST)

/*
 * Control Modes
 */

#define IHFLOW      ((tcflag_t)0x00000001)
#define OHFLOW      ((tcflag_t)0x00000002)
#define PARSTK      ((tcflag_t)0x00000004)
#define IIDLE       ((tcflag_t)0x00000008)

#define CSIZE       ((tcflag_t)0x00000030)
#define CS5               ((tcflag_t)0x00)
#define CS6               ((tcflag_t)0x10)
#define CS7               ((tcflag_t)0x20)
#define CS8               ((tcflag_t)0x30)
#define CSTOPB      ((tcflag_t)0x00000040)
#define CREAD       ((tcflag_t)0x00000080)
#define PARENB      ((tcflag_t)0x00000100)
#define PARODD      ((tcflag_t)0x00000200)
#define HUPCL       ((tcflag_t)0x00000400)
#define CLOCAL      ((tcflag_t)0x00000800)

#define TC_CPOSIX (CLOCAL|CREAD|CSIZE|CSTOPB|HUPCL|PARENB|PARODD)

/*
 * Local Modes
 */

#define ISIG        ((tcflag_t)0x00000001)
#define ICANON      ((tcflag_t)0x00000002)
#define ECHO        ((tcflag_t)0x00000008)
#define ECHOE       ((tcflag_t)0x00000010)
#define ECHOK       ((tcflag_t)0x00000020)
#define ECHONL      ((tcflag_t)0x00000040)
#define NOFLSH      ((tcflag_t)0x00000080)
#define TOSTOP      ((tcflag_t)0x00000100)
#if defined(__EXT_XOPEN_EX)
#define XCASE       ((tcflag_t)0x00000004)
#endif
#define IEXTEN      ((tcflag_t)0x00008000)
#if defined(__EXT_UNIX_MISC)
#define ECHOCTL		((tcflag_t)0x00000200)
#define ECHOKE      ((tcflag_t)0x00000800)
#endif

#define TC_LPOSIX (ECHO|ECHOE|ECHOK|ECHONL|ICANON|IEXTEN|ISIG|NOFLSH|TOSTOP)

/*
 * Special Control Character indices into c_cc[]
 */

#define VINTR   0
#define VQUIT   1
#define VERASE  2
#define VKILL   3
#define VEOF    4
#define VEOL    5
#define VEOL2   6
#define VSWTCH  7
#define VSTART  8
#define VSTOP   9
#define VSUSP   10
#define VDSUSP  11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE 14
#define VLNEXT  15
#define VMIN    16
#define VTIME   17

#define VFWD    18
#define VLOGIN  19
#define VPREFIX 20
#define VSUFFIX 24
#define VLEFT   28
#define VRIGHT  29
#define VUP     30
#define VDOWN   31
#define VINS    32
#define VDEL    33
#define VRUB    34
#define VCAN    35
#define VHOME   36
#define VEND    37
#define VSPARE3 38
#define VSPARE4 39

/*
 * Pre-Defined Baud rates used by cfgetospeed(), etc.
 */

#define _TIOS_B0      0
#define B0		     _TIOS_B0	
#define _TIOS_B50     50
#define B50          _TIOS_B50
#define _TIOS_B75     75
#define B75          _TIOS_B75
#define _TIOS_B110    110
#define B110         _TIOS_B110
#define _TIOS_B134    134
#define B134         _TIOS_B134
#define _TIOS_B150    150
#define B150         _TIOS_B150
#define _TIOS_B200    200
#define B200         _TIOS_B200
#define _TIOS_B300    300
#define B300         _TIOS_B300	
#define _TIOS_B600    600
#define B600         _TIOS_B600
#define _TIOS_B1200   1200
#define B1200        _TIOS_B1200
#define _TIOS_B1800   1800
#define B1800        _TIOS_B1800
#define _TIOS_B2400   2400
#define B2400        _TIOS_B2400
#define _TIOS_B4800   4800
#define B4800        _TIOS_B4800
#define _TIOS_B9600   9600
#define B9600        _TIOS_B9600
#define _TIOS_B19200  19200
#define B19200       _TIOS_B19200
#define _TIOS_EXTA    19200
#define EXTA         _TIOS_EXTA
#define _TIOS_B38400  38400u
#define B38400       _TIOS_B38400
#define _TIOS_EXTB    38400u
#define EXTB         _TIOS_EXTB

#define _TIOS_B57600  57600u
#define B57600       _TIOS_B57600
#define _TIOS_B76800  76800L
#define B76800       _TIOS_B76800
#define _TIOS_B115200 115200L
#define B115200      _TIOS_B115200

/*
 * Optional Actions for tcsetattr()
 */

#define TCSANOW     0x0001
#define TCSADRAIN   0x0002
#define TCSAFLUSH   0x0004

/*
 * queue_selectors for tcflush()
 */

#define TCIFLUSH    0x0000
#define TCOFLUSH    0x0001
#define TCIOFLUSH   0x0002

/*
 * Actions for tcflow()
 */

#define TCOOFF      0x0000
#define TCOON       0x0001
#define TCIOFF      0x0002
#define TCION       0x0003

#define TCOOFFHW    0x0004
#define TCOONHW     0x0005
#define TCIOFFHW    0x0006
#define TCIONHW     0x0007

__BEGIN_DECLS
/*
 *  POSIX 1003.1 Prototypes.
 */
extern speed_t cfgetispeed(const struct termios * __termios_p);
extern speed_t cfgetospeed(const struct termios * __termios_p);
extern int     cfsetispeed(struct termios * __termios_p, speed_t __speed);
extern int     cfsetospeed(struct termios * __termios_p, speed_t __speed);
extern int     tcdrain(int __fildes);
extern int     tcdropline(int __fildes, int __duration);
extern int     tcflow(int __fildes, int __action);
extern int     tcflush(int __fildes, int __queue_selector);
extern int     tcgetattr(int __fildes, struct termios * __termios_p);
extern int     tcsendbreak(int __fildes, int __duration);
extern int     tcsetattr(int __fildes, int __opt_act, const struct termios * __termios_p);

#if defined(__EXT_UNIX_MISC)
extern int     cfmakeraw(struct termios * __termios_p);
#endif

#if defined(__EXT_XOPEN_EX)
extern pid_t    tcgetsid(int __filedes);
extern int      tcsetsid(int __filedes, pid_t __pid);
#endif

#if defined(__EXT_QNX)
extern int     tcinject(int __fildes, char *__buf, int __n);
extern int     tcischars(int __filedes);
extern int     tcgetsize(int __fildes, int *__prows, int *__pcols);
extern int     tcsetsize(int __fildes, int __rows, int __cols);
#endif

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/termios.h $ $Rev: 822471 $")
#endif
