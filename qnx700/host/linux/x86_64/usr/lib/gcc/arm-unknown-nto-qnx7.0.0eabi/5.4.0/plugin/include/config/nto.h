/* Base configuration for all QNX Neutrino targets
   Copyright (C) 2006
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

#undef TARGET_NEUTRINO
#define TARGET_NEUTRINO 1

#undef GCC_DRIVER_HOST_INITIALIZATION
#define GCC_DRIVER_HOST_INITIALIZATION \
do { \
    char *qnx_host = getenv ("QNX_HOST"); \
    char *qnx_target = getenv ("QNX_TARGET"); \
    if (qnx_host == NULL && qnx_target == NULL) \
      fatal_error (input_location, "error: environment variables QNX_HOST and QNX_TARGET not defined"); \
    if (qnx_host == NULL) \
      fatal_error (input_location, "error: environment variable QNX_HOST not defined"); \
    if (qnx_target == NULL) \
      fatal_error (input_location, "error: environment variable QNX_TARGET not defined"); \
    standard_libexec_prefix = concat (qnx_host, "/usr/lib/gcc/", NULL); \
    standard_exec_prefix = concat (qnx_host, "/usr/lib/gcc/", NULL); \
    standard_startfile_prefix = concat (qnx_host, "/usr/lib/", NULL); \
    standard_bindir_prefix = concat (qnx_host, "/usr/bin/", NULL); \
    tooldir_base_prefix = concat (qnx_host, "/usr/", NULL); \
    add_prefix (&exec_prefixes, standard_bindir_prefix, NULL, PREFIX_PRIORITY_LAST, 0, 0); \
} while (0)

#define QNX_SYSTEM_INCLUDES \
"%{!nostdinc: \
-isystem %$QNX_HOST/usr/lib/gcc/" DEFAULT_TARGET_MACHINE "/%v1.%v2.%v3/include \
-isysroot %$QNX_TARGET/}"

#if QNX_ENABLE_RELRO
#define QNX_RELRO_SPEC "-zrelro -znow"
#else
#define QNX_RELRO_SPEC ""
#endif

#define DEFAULT_STDLIB_SPEC "|!stdlib=*"
#if DEFAULT_STDLIB_LIBSTDCXX
#define NTO_EXTRA_LIBSTDCXX_SPEC DEFAULT_STDLIB_SPEC
#define NTO_EXTRA_LIBCXX_SPEC ""
#elif DEFAULT_STDLIB_LIBCXX
#define NTO_EXTRA_LIBCXX_SPEC DEFAULT_STDLIB_SPEC
#define NTO_EXTRA_LIBSTDCXX_SPEC ""
#else
#define NTO_EXTRA_LIBSTDCXX_SPEC ""
#define NTO_EXTRA_LIBCXX_SPEC ""
#endif

#undef CPLUSPLUS_CPP_SPEC
#define CPLUSPLUS_CPP_SPEC \
CPP_SPEC \
"%{!nostdinc++: \
%{stdlib=libcpp|stdlib=libcpp-ne: \
 -isystem %$QNX_TARGET/usr/include/cpp/c/ \
 -isystem %$QNX_TARGET/usr/include/cpp \
} \
%{stdlib=libcpp-ne: -D_NO_EX } \
%{stdlib=libc++" NTO_EXTRA_LIBCXX_SPEC ": \
 -isystem %$QNX_TARGET/usr/include/c++/v1 \
} \
%{stdlib=libstdc++" NTO_EXTRA_LIBSTDCXX_SPEC ": \
 -isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3 \
 -isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3/" DEFAULT_TARGET_MACHINE " \
 -isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3/backward \
} \
}" 

/* Don't assume anything about the header files.  */
#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C

/* Allow stabs and dwarf, and make dwarf the default for Neutrino */
#undef PREFERRED_DEBUGGING_TYPE
#undef DBX_DEBUGGING_INFO
#undef DWARF_DEBUGGING_INFO
#undef DWARF2_DEBUGGING_INFO

#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG
#define DBX_DEBUGGING_INFO
#define DWARF_DEBUGGING_INFO 1
#define DWARF2_DEBUGGING_INFO 1

#define SUPPORTS_WEAK 1

#undef MD_EXEC_PREFIX
#undef MD_STARTFILE_PREFIX

#ifdef HAVE_GNU_INDIRECT_FUNCTION
#define GNU_INDIRECT_FUNCTION if (HAVE_GNU_INDIRECT_FUNCTION) \
				 builtin_define ("__GNU_INDIRECT_FUNCTION__");
#else
#define GNU_INDIRECT_FUNCTION
#endif

#define NTO_TARGET_OS_CPP_BUILTINS()		\
do {                                            \
        builtin_define ("__QNX__");             \
        builtin_define ("__QNXNTO__");          \
        builtin_define ("__ELF__");             \
        builtin_assert ("system=posix");        \
        builtin_assert ("system=qnx");          \
        builtin_assert ("system=nto");          \
        builtin_assert ("system=qnxnto");       \
        builtin_define ("__PRAGMA_PACK_PUSH_POP__");	\
	GNU_INDIRECT_FUNCTION			\
    } while (0)

/* Don't set libgcc.a's gthread/pthread symbols to weak, as our
   libc has them as well, and we get problems when linking static,
   as libgcc.a will get a symbol value of 0.  */
#define GTHREAD_USE_WEAK 0

#undef THREAD_MODEL_SPEC
#define THREAD_MODEL_SPEC "posix"

/* Under Neutrino, there is one set of header files for all targets. wchar_t is
   defined as a 32 bit unsigned integer */
#undef WCHAR_TYPE
#define WCHAR_TYPE "unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

#undef WINT_TYPE
#define WINT_TYPE "int"

#undef WINT_TYPE_SIZE
#define WINT_TYPE_SIZE 32

#define TARGET_POSIX_IO

/* Determine what functions are present at the runtime;
   all new versions of QNX have C99 functions.  */
#undef TARGET_LIBC_HAS_FUNCTION
#define TARGET_LIBC_HAS_FUNCTION default_libc_has_function

#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""

#undef LINK_GCC_C_SEQUENCE_SPEC
#define LINK_GCC_C_SEQUENCE_SPEC \
  "%{static:--start-group} %G %L %{static:--end-group}%{!static:%G}"

#if defined(HAVE_LD_EH_FRAME_HDR)
#define LINK_EH_SPEC "%{!static:--eh-frame-hdr} "
#endif

/* Remove the default C++ headers so we can select via -stdlib */
#undef GPLUSPLUS_INCLUDE_DIR
#undef GPLUSPLUS_TOOL_INCLUDE_DIR
#undef GPLUSPLUS_BACKWARD_INCLUDE_DIR

/* Define LIBSTDCXX so we can select the implementation baded on -stdlib */
extern const char *nto_select_libstdcxx(void);
#define LIBSTDCXX nto_select_libstdcxx()
#define LIBSTDCXX_PROFILE LIBSTDCXX
extern const char *nto_select_libstdcxx_static(void);
#define LIBSTDCXX_STATIC nto_select_libstdcxx_static()

extern void nto_handle_cxx_option (size_t code, const char *arg);
#define TARGET_HANDLE_CXX_OPTION nto_handle_cxx_option

#undef LIB_SPEC
#define LIB_SPEC \
  "%{!symbolic: -lc -Bstatic %{shared:-lcS} %{" PIE_SPEC ":-lcS} %{" NO_PIE_SPEC ":-lc}}"
