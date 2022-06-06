/* Definitions for AArch64 architecture running QNX/Neutrino.
   Copyright (C) 2015 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
"%{!shared: %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib/%{pg:m}%{p:m}crt1.o } \
%$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib/crti.o crtbegin.o%s "

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
"crtend.o%s %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib/crtn.o"

#undef LINK_SPEC
#define LINK_SPEC \
"%{h*} %{v:-V} \
 %{b} %{Wl,*:%*} \
 %{!r:--build-id=md5} \
 --warn-shared-textrel \
 " QNX_RELRO_SPEC " \
 %{static:-Bstatic} \
 %{shared} \
 %{symbolic:-Bsymbolic} \
 %{G:-G} %{MAP:-Map mapfile} \
 %{!shared: \
   %{!static: \
     %{rdynamic:-export-dynamic}} \
   --dynamic-linker /usr/lib/ldqnx-64.so.2} \
 -X %{EB:-EB} %{!EB:-EL} %{EL:-EL} "

#define QNX_SYSTEM_LIBDIRS \
"-L %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib/gcc/%v1.%v2.%v3 \
 -L %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib \
 -L %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/usr/lib \
 -L %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/opt/lib \
 -rpath-link %$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib/gcc/%v1.%v2.%v3:\
%$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/lib:\
%$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/usr/lib:\
%$QNX_TARGET/aarch64%{EB:be}%{!EB:le}/opt/lib "

#undef LINK_LIBGCC_SPEC
#define LINK_LIBGCC_SPEC \
  "%D " \
  QNX_SYSTEM_LIBDIRS

#undef  CPP_SPEC
#define CPP_SPEC \
 QNX_SYSTEM_INCLUDES "\
 %(cpp_cpu) \
 %{!EB:-D__LITTLEENDIAN__ -D__AARCH64EL__} \
 %{EB:-D__BIGENDIAN__ -D__AARCH64EB__} \
 %{posix:-D_POSIX_SOURCE} \
 %{pthread:}"

#undef  CC1_SPEC
#define CC1_SPEC "%{EB:-mbig-endian} %{!EB:-mlittle-endian}"

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()                \
do {                                            \
        NTO_TARGET_OS_CPP_BUILTINS();           \
} while (0)

