/* Definitions for AMD x86-64 running QNX/Neutrino.
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

#define TARGET_OS_CPP_BUILTINS()				\
  do								\
    {								\
	NTO_TARGET_OS_CPP_BUILTINS();				\
	if (TARGET_64BIT)					\
	  builtin_define_std ("__X86_64__");			\
	else							\
	  builtin_define_std ("__X86__");			\
        builtin_define ("__LITTLEENDIAN__");			\
    }								\
  while (0)

#undef CPP_SPEC
#define CPP_SPEC \
QNX_SYSTEM_INCLUDES \
" %(cpp_cpu) \
 %{posix:-D_POSIX_SOURCE} %{pthread:}"

#undef ASM_SPEC
#define ASM_SPEC "%{v:-V} %{Qy:} %{!Qn:-Qy} %{n} %{T} %{Ym,*} %{Yd,*} \
 %{Wa,*:%*} %{m32:--32} %{m64:--64} \
 %{!mno-sse2avx:%{mavx:-msse2avx}} %{msse2avx:%{!mavx:-msse2avx}}"

#if TARGET_64BIT_DEFAULT
#define SPEC_32 "m32"
#define SPEC_64 "!m32"
#else
#define SPEC_32 "!m64"
#define SPEC_64 "m64"
#endif

#define NTO_DYNAMIC_LINKER32 "/usr/lib/ldqnx.so.2"
#define NTO_DYNAMIC_LINKER64 "/usr/lib/ldqnx-64.so.2"

#undef	LINK_SPEC
#define LINK_SPEC "%{" SPEC_64 ":-m elf_x86_64} %{" SPEC_32 ":-m i386nto} \
  %{h*} %{v:-V} \
  %{b} \
  %{!r:--build-id=md5} \
  --warn-shared-textrel \
  " QNX_RELRO_SPEC " \
  %{shared:-G -dy -z text} \
  %{symbolic:-Bsymbolic -G -dy -z text} \
  %{G:-G} \
  %{shared:-shared} \
  %{!shared: \
    %{!static: \
      %{rdynamic:-export-dynamic} \
      %{" SPEC_32 ":%{!dynamic-linker:-dynamic-linker " NTO_DYNAMIC_LINKER32 "}} \
      %{" SPEC_64 ":%{!dynamic-linker:-dynamic-linker " NTO_DYNAMIC_LINKER64 "}}} \
    %{static:-static}} "

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
"%{!shared: \
  %{!symbolic: \
    %{pg: \
      %{" SPEC_32 ": %$QNX_TARGET/x86/lib/mcrt1.o%s} \
      %{" SPEC_64 ": %$QNX_TARGET/x86_64/lib/mcrt1.o%s}} \
    %{!pg: \
      %{p: \
       %{" SPEC_32 ": %$QNX_TARGET/x86/lib/mcrt1.o%s} \
       %{" SPEC_64 ": %$QNX_TARGET/x86_64/lib/mcrt1.o%s}}} \
    %{!p: %{!pg: \
       %{" SPEC_32 ": %$QNX_TARGET/x86/lib/crt1%{" PIE_SPEC ":S}.o%s} \
       %{" SPEC_64 ": %$QNX_TARGET/x86_64/lib/crt1.o%s}}} \
    }} \
    %{" SPEC_32 ": %$QNX_TARGET/x86/lib/crti.o%s} \
    %{" SPEC_64 ": %$QNX_TARGET/x86_64/lib/crti.o%s} \
    crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
"crtend.o%s \
  %{" SPEC_32 ": %$QNX_TARGET/x86/lib/crtn.o%s} \
  %{" SPEC_64 ": %$QNX_TARGET/x86_64/lib/crtn.o%s} "

#define QNX_SYSTEM_LIBDIRS \
"%{" SPEC_32 ": \
  -L %$QNX_TARGET/x86/lib/gcc/%v1.%v2.%v3 \
  -L %$QNX_TARGET/x86/lib \
  -L %$QNX_TARGET/x86/usr/lib \
  -L %$QNX_TARGET/x86/opt/lib \
  -rpath-link %$QNX_TARGET/x86/lib/gcc/%v1.%v2.%v3:\
%$QNX_TARGET/x86/lib:\
%$QNX_TARGET/x86/usr/lib:\
%$QNX_TARGET/x86/opt/lib} \
 %{" SPEC_64 ": \
  -L %$QNX_TARGET/x86_64/lib/gcc/%v1.%v2.%v3 \
  -L %$QNX_TARGET/x86_64/lib \
  -L %$QNX_TARGET/x86_64/usr/lib \
  -L %$QNX_TARGET/x86_64/opt/lib \
  -rpath-link %$QNX_TARGET/x86_64/lib/gcc/%v1.%v2.%v3:\
%$QNX_TARGET/x86_64/lib:\
%$QNX_TARGET/x86_64/usr/lib:\
%$QNX_TARGET/x86_64/opt/lib} "

#undef LINK_LIBGCC_SPEC
#define LINK_LIBGCC_SPEC \
  "%D " \
  QNX_SYSTEM_LIBDIRS

#if TARGET_64BIT_DEFAULT
#define MULTILIB_DEFAULTS { "m64" }
#else
#define MULTILIB_DEFAULTS { "m32" }
#endif
