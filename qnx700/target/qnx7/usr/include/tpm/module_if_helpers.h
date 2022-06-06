/*
 * Copyright 2016, QNX Software Systems.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 */

#ifndef _TPM_MODULE_IF_HELPERS_H_INCLUDED
#define _TPM_MODULE_IF_HELPERS_H_INCLUDED

/* sorted headers from this project */
#ifndef _TPM_MODULE_IF_H_INCLUDED
#include "tpm/module_if.h"
#endif

/* sorted system headers */
#ifndef _ERRNO_H_INCLUDED
#include <errno.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDLIB_H_INCLUDED
#include <stdlib.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

#define tpm_msglog_noloc(module_if, flags, ...) \
            (module_if)->svc->msglog(module_if, flags, ##__VA_ARGS__)
/* in order to use this #define, __FILENAME__ should contain the string representation of the file name (ideally without the path) */
#define tpm_msglog(module_if, flags, ...) \
            (module_if)->svc->msglog_ex(&(svc_msglog_info_t){ module_if, flags, __FILENAME__, NULL, __LINE__ }, ##__VA_ARGS__)
/* in order to use this #define, __FILENAME__ should contain the string representation of the file name (ideally without the path) */
#define tpm_msglog_loc(module_if, flags, ...) \
            (module_if)->svc->msglog_ex(&(svc_msglog_info_t){ module_if, flags, __FILENAME__, __func__, __LINE__ }, ##__VA_ARGS__)
#define tpm_msglog_f(module_if, filename, flags, ...) \
            (module_if)->svc->msglog_ex(&(svc_msglog_info_t){ module_if, flags, filename, NULL, __LINE__ }, ##__VA_ARGS__)
#define tpm_msglog_linetracef(module_if, filename, msg) \
            (module_if)->svc->msglog_ex(&(svc_msglog_info_t){ module_if, TMLOG_INFO, filename, __func__, __LINE__ }, "DBG trace: %s", "" msg)
/* in order to use this #define, __FILENAME__ should contain the string representation of the file name (ideally without the path) */
#define tpm_msglog_linetrace(module_if, msg) \
            tpm_msglog_loc(module_if, TMLOG_INFO, "DBG trace: %s", "" msg)
/* in order to use this #define, __FILENAME__ should contain the string representation of the file name (ideally without the path) */
#define tmlog(flags, ...) tpm_msglog(module_if, flags, ##__VA_ARGS__)

static inline int
tpm_mod_if_exchange_helper(tpm_module_if_t *module_if, uint32_t version, uint32_t version_min, void *reserved)
{
    (void)reserved;

    if ((module_if == NULL) || (module_if->size < TPM_MOD_IF_CORE_SIZE)) {
        errno = EINVAL;
        return errno;
    }

    module_if->mod_if_version_used = version;
    module_if->mod_if_version_min = version_min;

    if ((module_if->svc_if_version_used < version_min) ||
        (module_if->svc_if_version_min > version)) {
        errno = ENOTSUP;
        return errno;
    }

    if (module_if->size < sizeof(*module_if)) {
        errno = ENOTSUP;
        return errno;
    }

    if ((module_if->svc == NULL) ||
        (module_if->mod == NULL) ||
        (module_if->dev == NULL)) {
        errno = EINVAL;
        return errno;
    }

    if ((module_if->svc->size < sizeof(*module_if->svc)) ||
        (module_if->mod->size < sizeof(*module_if->mod)) ||
        (module_if->dev->size < sizeof(*module_if->dev))) {
        errno = ENOTSUP;
        return errno;
    }

    return EOK;
}

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _TPM_MODULE_IF_HELPERS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/tpm/public/tpm/module_if_helpers.h $ $Rev: 820218 $")
#endif
