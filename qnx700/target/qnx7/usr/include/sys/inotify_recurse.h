/*
 * $QNXLicenseC: $
 */


#ifndef _SYS_INOTIFY_RECURSE_H_
#define _SYS_INOTIFY_RECURSE_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>

__BEGIN_DECLS


extern int inotify_recurse_init(void);
extern ssize_t inotify_recurse_read(int fd, void * buffer, size_t len);
extern int inotify_recurse_close(int fd);
extern int inotify_recurse_add_watch(int fd, const char * path, size_t pathlen, uint32_t mask);
extern int inotify_recurse_rm_watch(int fd, int32_t wd);


__END_DECLS

#endif /* #ifndef _SYS_INOTIFY_RECURSE_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/sys/inotify_recurse.h $ $Rev: 780356 $")
#endif
