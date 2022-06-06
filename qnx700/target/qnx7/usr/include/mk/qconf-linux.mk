#
# Linux qconfig.mk file
#
ifndef BUILDENV
BUILDENV := qss
endif

LINUX_DEFS 		:= -D__LINUX__ -D__X86__ -D__LITTLEENDIAN__

#
# The base directories for the installation trees.
#
INSTALL_ROOT_nto	:= $(QNX_TARGET)
INSTALL_ROOT_linux	:=

#
# The base directories for accessing headers/libraries for various OS's.
#
USE_ROOT_nto		:= $(QNX_TARGET)
USE_ROOT_linux		:=

#
# QNX Recursive Make files
#
MKFILES_ROOT 		:= $(QNX_TARGET)/usr/include/mk

#
# The MG_HOST utilty is to "mark generated" any file that you'd normally
# consider a source file (something with a .c, .s, etc. extension),
# but is actually generated by a program. E.g., the kernel call
# source files in libc. It's purely for documentation purposes. 
#
MG_HOST = /bin/true
#
# Copy a space separated list of files (possibly with wildcards) to an
# installation directory.  Linux cp does not support creating any
# target directories, so call a simple script that tests first, and
# creates the target path as needed.
#
CP_HOST = $(QNX_HOST)/usr/bin/qnx_cp -fpc $(CP_HOST_OPTIONS)
#
# Create a symbolic link.  
#
LN_HOST = /bin/ln -sf $(LN_HOST_OPTIONS)
#
# Delete a space separated list of files (possibly with wildcards).
#
RM_HOST = /bin/rm -f $(RM_HOST_OPTIONS)
#
# Create an empty file
#
TOUCH_HOST = /bin/touch
#
# Print the full path of the current working directory to standard output.
# Due to differences in the outputs of shell builtin and binary pwd, we
# override PWD to be the binary output.
#
PWD_HOST = /bin/pwd
PWD := $(shell $(PWD_HOST))
#
# Generate a space separated list of files in a directory tree, ignoring
# anything in a CVS or RCS directory.
#
FL_HOST = $(MKFILES_ROOT)/flist-unix
#
# Generate an assembler definition file from an object file.
#
MKASMOFF_HOST = $(QNX_HOST)/usr/bin/mkasmoff 
#
# Mark something as a privledged executable (setuid)
#
MP_HOST = $(MKFILES_ROOT)/makepriv-unix

ECHO_HOST = /bin/echo
DATE_HOST = /bin/date +%Y/%m/%d-%T-%Z
USER_HOST := $(firstword $(filter /%, $(shell which -a id))) -un
HOST_HOST = /bin/hostname
FLEX_HOST = $(QNX_HOST)/usr/bin/flex
BISON_HOST = $(QNX_HOST)/usr/bin/bison
ELFNOTE_HOST = $(QNX_HOST)/usr/bin/elfnote

#
# CL_*  Compile and link
# CC_*  Compile C/C++ source to an object file
# AS_*  Assemble something to an object file
# AR_*  Generate an object file library (archive)
# LR_*  Link a list of objects/libraries to a relocatable object file
# LD_*  Link a list of objects/libraries to a executable/shared object
# UM_*  Add a usage message to an executable
# PB_*	Add PhAB resources to an executable using "phabbind"
#

#
# host system
#
LINUX_x86_GCC_DRIVER ?= i686-unknown-linux-gnu-gcc 
ifeq (, $(shell which $(LINUX_x86_GCC_DRIVER)))
LINUX_x86_GCC_DRIVER=gcc
endif

CL_HOST = $(LINUX_x86_GCC_DRIVER) $(LINUX_CPU_DEFS) $(LINUX_DEFS)
CC_HOST = $(LINUX_x86_GCC_DRIVER) -c $(LINUX_CPU_DEFS) $(LINUX_DEFS)
AS_HOST = $(LINUX_x86_GCC_DRIVER) -c $(LINUX_CPU_DEFS)
AR_HOST = ar -r
LD_HOST = $(LINUX_x86_GCC_DRIVER) $(LINUX_CPU_DEFS)
UM_HOST	= $(QNX_HOST)/usr/bin/usemsg
PB_HOST	= $(QNX_HOST)/usr/bin/phabbind

CD_nto_x86_gcc = qcc
CD_nto_x86_icc = qcc
CD_nto_x86_64_gcc = qcc
CD_nto_ppc_gcc = qcc
CD_nto_mips_gcc = qcc
CD_nto_sh_gcc = qcc
CD_nto_arm_gcc = qcc
CD_nto_aarch64_gcc = qcc
COMPILER_DRIVER = $(CD_$(OS)_$(CPU)_$(COMPILER_TYPE))

dash:=-
comma:=,
gcc_ver_suffix=$(if $(GCC_VERSION),$(dash)$(GCC_VERSION))
gcc_ver_string=$(if $(GCC_VERSION),$(GCC_VERSION)$(comma))
clang_ver_suffix=$(if $(CLANG_VERSION),$(dash)$(CLANG_VERSION))
clang_ver_string=$(if $(CLANG_VERSION),$(CLANG_VERSION)$(comma))

#
# NTO X86 target 
#
CC_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) 
AS_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) 
AR_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-ar
LR_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) 
UM_nto_x86_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_x86_gcc = $(QNX_HOST)/usr/bin/ntox86-objcopy 

CC_nto_x86_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86 -c
AS_nto_x86_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86 -c
LR_nto_x86_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86 -r -Bstatic
LD_nto_x86_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86
AR_nto_x86_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86 -a
UM_nto_x86_gcc_qcc = $(UM_nto_x86_gcc)
OC_nto_x86_gcc_qcc = $(OC_nto_x86_gcc)

CC_nto_x86_icc = icc -c
AS_nto_x86_icc = icc -c
LR_nto_x86_icc = icc -r
LD_nto_x86_icc = icc
AR_nto_x86_icc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86 -a
UM_nto_x86_icc = $(UM_nto_x86_gcc)
OC_nto_x86_icc = $(OC_nto_x86_gcc)

CC_nto_x86_icc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86 -c
AS_nto_x86_icc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86 -c
LR_nto_x86_icc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86 -r
LD_nto_x86_icc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86
AR_nto_x86_icc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)icc_ntox86 -a
UM_nto_x86_icc_qcc = $(UM_nto_x86_gcc)
OC_nto_x86_icc_qcc = $(OC_nto_x86_gcc)

CC_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-clang$(clang_ver_suffix) 
AS_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-clang$(clang_ver_suffix) 
AR_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-ar $(if $(filter -flto,$(LDFLAGS)), --plugin $(QNX_HOST)/usr/lib/LLVMgold.so${CLANG_VERSION:+.${CLANG_VERSION}})
LR_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-clang$(clang_ver_suffix) -r -Wl,-Bstatic
LD_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-clang$(clang_ver_suffix) 
UM_nto_x86_clang = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_x86_clang = $(QNX_HOST)/usr/bin/ntox86-objcopy 

#
# NTO x86_64 target
#

CC_nto_x86_64_gcc = $(QNX_HOST)/usr/bin/ntox86_64-gcc$(gcc_ver_suffix)
AS_nto_x86_64_gcc = $(QNX_HOST)/usr/bin/ntox86_64-gcc$(gcc_ver_suffix)
AR_nto_x86_64_gcc = $(QNX_HOST)/usr/bin/ntox86_64-ar
LR_nto_x86_64_gcc = $(QNX_HOST)/usr/bin/ntox86_64-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_x86_64_gcc = $(QNX_HOST)/usr/bin/ntox86_64-gcc$(gcc_ver_suffix)
UM_nto_x86_64_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE

CC_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64 -c
AS_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64 -c
LR_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64 -r -Bstatic
LD_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64
AR_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64  -a
UM_nto_x86_64_gcc_qcc = $(UM_nto_x86_64_gcc)

CC_nto_x86_64_clang = $(QNX_HOST)/usr/bin/ntox86_64-clang$(clang_ver_suffix)
AS_nto_x86_64_clang = $(QNX_HOST)/usr/bin/ntox86_64-clang$(clang_ver_suffix)
AR_nto_x86_64_clang = $(QNX_HOST)/usr/bin/ntox86_64-ar $(if $(filter -flto,$(LDFLAGS)), --plugin $(QNX_HOST)/usr/lib/LLVMgold.so${CLANG_VERSION:+.${CLANG_VERSION}})
LR_nto_x86_64_clang = $(QNX_HOST)/usr/bin/ntox86_64-clang$(clang_ver_suffix) -r -Wl,-Bstatic
LD_nto_x86_64_clang = $(QNX_HOST)/usr/bin/ntox86_64-clang$(clang_ver_suffix)
UM_nto_x86_64_clang = $(UM_HOST) -s __USAGENTO -s __USAGE

#
# NTO PPC target 
#
CC_nto_ppc_gcc = $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) -c
AS_nto_ppc_gcc = $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) -c
AR_nto_ppc_gcc = $(QNX_HOST)/usr/bin/ntoppc-ar
LR_nto_ppc_gcc = $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_ppc_gcc = $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) 
UM_nto_ppc_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_ppc_gcc = $(QNX_HOST)/usr/ntoppc-objcopy

CC_nto_ppc_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc -c
AS_nto_ppc_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc -c
LR_nto_ppc_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc -r -Bstatic
LD_nto_ppc_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc
AR_nto_ppc_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc -a
UM_nto_ppc_gcc_qcc = $(UM_nto_ppc_gcc)
OC_nto_ppc_gcc_qcc = $(OC_nto_ppc_gcc)

#
# NTO MIPS target
#
CC_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) -c
AS_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) -c
AR_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-ar
LR_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) 
UM_nto_mips_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_mips_gcc = $(QNX_HOST)/usr/bin/ntomips-objcopy

CC_nto_mips_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips -c
AS_nto_mips_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips -c
LR_nto_mips_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips -r -Bstatic
LD_nto_mips_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips
AR_nto_mips_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips -a
UM_nto_mips_gcc_qcc = $(UM_nto_mips_gcc)
OC_nto_mips_gcc_qcc = $(OC_nto_mips_gcc)

#
# NTO ARM target
#
CC_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) -c
AS_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) -c
AR_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-ar
LR_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) 
UM_nto_arm_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_arm_gcc = $(QNX_HOST)/usr/bin/ntoarm-objcopy 

CC_nto_arm_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm -c
AS_nto_arm_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm -c
LR_nto_arm_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm -r -Bstatic
LD_nto_arm_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm
AR_nto_arm_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm -a
UM_nto_arm_gcc_qcc = $(UM_nto_arm_gcc)
OC_nto_arm_gcc_qcc = $(OC_nto_arm_gcc)

#
# NTO ARMv7 target
#
CC_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-gcc$(gcc_ver_suffix) -c
AS_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-gcc$(gcc_ver_suffix) -c
AR_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-ar
LR_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-gcc$(gcc_ver_suffix) 
UM_nto_arm_gcc_v7 = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_arm_gcc_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-objcopy 

CC_nto_arm_gcc_qcc_v7 = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarmv7 -c
AS_nto_arm_gcc_qcc_v7 = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarmv7 -c
LR_nto_arm_gcc_qcc_v7 = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarmv7 -r -Bstatic
LD_nto_arm_gcc_qcc_v7 = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarmv7
AR_nto_arm_gcc_qcc_v7 = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarmv7 -a
UM_nto_arm_gcc_qcc_v7 = $(UM_nto_arm_gcc_v7)
OC_nto_arm_gcc_qcc_v7 = $(OC_nto_arm_gcc_v7)

CC_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-clang$(clang_ver_suffix) -c
AS_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-clang$(clang_ver_suffix) -c
AR_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-ar $(if $(filter -flto,$(LDFLAGS)), --plugin $(QNX_HOST)/usr/lib/LLVMgold.so${CLANG_VERSION:+.${CLANG_VERSION}})
LR_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-clang$(clang_ver_suffix) -r -Wl,-Bstatic
LD_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-clang$(clang_ver_suffix) 
UM_nto_arm_clang_v7 = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_arm_clang_v7 = $(QNX_HOST)/usr/bin/ntoarmv7-objcopy 

#
# NTO ARM 64bit target
#
CC_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-gcc$(gcc_ver_suffix) -c
AS_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-gcc$(gcc_ver_suffix) -c
AR_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-ar
LR_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-gcc$(gcc_ver_suffix)
UM_nto_aarch64_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_aarch64_gcc = $(QNX_HOST)/usr/bin/ntoaarch64-objcopy

CC_nto_aarch64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoaarch64 -c
AS_nto_aarch64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoaarch64 -c
LR_nto_aarch64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoaarch64 -r -Bstatic
LD_nto_aarch64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoaarch64
AR_nto_aarch64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoaarch64 -a
UM_nto_aarch64_gcc_qcc = $(UM_nto_aarch64_gcc)
OC_nto_aarch64_gcc_qcc = $(OC_nto_aarch64_gcc)

CC_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-clang$(clang_ver_suffix) -c
AS_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-clang$(clang_ver_suffix) -c
AR_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-ar $(if $(filter -flto,$(LDFLAGS)), --plugin $(QNX_HOST)/usr/lib/LLVMgold.so${CLANG_VERSION:+.${CLANG_VERSION}})
LR_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-clang$(clang_ver_suffix) -r -Wl,-Bstatic
LD_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-clang$(clang_ver_suffix) 
UM_nto_aarch64_clang = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_aarch64_clang = $(QNX_HOST)/usr/bin/ntoaarch64-objcopy 

#
# NTO SH target
#
CC_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) -c
AS_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) -c
AR_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-ar
LR_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) -r -Wl,-Bstatic
LD_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) 
UM_nto_sh_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE
OC_nto_sh_gcc = $(QNX_HOST)/usr/bin/ntosh-objcopy

CC_nto_sh_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh -c
AS_nto_sh_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh -c
LR_nto_sh_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh -r -Bstatic
LD_nto_sh_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh
AR_nto_sh_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh -a
UM_nto_sh_gcc_qcc = $(UM_nto_sh_gcc)
OC_nto_sh_gcc_qcc = $(OC_nto_sh_gcc)

#
# Linux x86 target
#

CC_linux_x86_gcc = $(LINUX_x86_GCC_DRIVER) -c $(LINUX_DEFS) $(LINUX_CPU_DEFS)
AS_linux_x86_gcc = $(LINUX_x86_GCC_DRIVER) -c $(LINUX_CPU_DEFS)
AR_linux_x86_gcc = ar -r
LR_linux_x86_gcc = $(LINUX_x86_GCC_DRIVER) -r -Wl,-Bstatic $(LINUX_CPU_DEFS)
LD_linux_x86_gcc = $(LINUX_x86_GCC_DRIVER) $(LINUX_CPU_DEFS)
OC_linux_x86_gcc = objcopy 
UM_linux_x86_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE

CC_linux_x86_clang = clang -c $(LINUX_DEFS) $(LINUX_CPU_DEFS)
AS_linux_x86_clang = clang -c $(LINUX_CPU_DEFS)
AR_linux_x86_clang = ar -r
LR_linux_x86_clang = clang -r -Wl,-Bstatic $(LINUX_CPU_DEFS)
LD_linux_x86_clang = clang $(LINUX_CPU_DEFS)
OC_linux_x86_clang = objcopy 
UM_linux_x86_clang = $(UM_HOST) -s __USAGENTO -s __USAGE

#
# Linux x86_64 target
#

LINUX_x86_64_GCC_DRIVER ?= x86_64-unknown-linux-gnu-gcc 
ifeq (, $(shell which $(LINUX_x86_64_GCC_DRIVER)))
LINUX_x86_64_GCC_DRIVER=gcc
endif

CC_linux_x86_64_gcc = $(LINUX_x86_64_GCC_DRIVER) -c $(LINUX_DEFS) $(LINUX_CPU_DEFS)
AS_linux_x86_64_gcc = $(LINUX_x86_64_GCC_DRIVER) -c $(LINUX_CPU_DEFS)
AR_linux_x86_64_gcc = ar -r
LR_linux_x86_64_gcc = $(LINUX_x86_64_GCC_DRIVER) -r -Wl,-Bstatic $(LINUX_CPU_DEFS)
LD_linux_x86_64_gcc = $(LINUX_x86_64_GCC_DRIVER) $(LINUX_CPU_DEFS)
OC_linux_x86_64_gcc = objcopy 
UM_linux_x86_64_gcc = $(UM_HOST) -s __USAGENTO -s __USAGE

#
# Win32 x86 target
#

WIN32_GCC_DRIVER ?= i686-mingw32msvc

CC_win32_x86_gcc = $(WIN32_GCC_DRIVER)-gcc -c
AS_win32_x86_gcc = $(WIN32_GCC_DRIVER)-gcc -c
LR_win32_x86_gcc = $(WIN32_GCC_DRIVER)-gcc -r
LD_win32_x86_gcc = $(WIN32_GCC_DRIVER)-gcc
AR_win32_x86_gcc = $(WIN32_GCC_DRIVER)-ar -r

#
# Win64 x86_64 target
#

WIN64_GCC_DRIVER ?= x86_64-w64-mingw32

CC_win64_x86_64_gcc = $(WIN64_GCC_DRIVER)-gcc -c
AS_win64_x86_64_gcc = $(WIN64_GCC_DRIVER)-gcc -c
LR_win64_x86_64_gcc = $(WIN64_GCC_DRIVER)-gcc -r
LD_win64_x86_64_gcc = $(WIN64_GCC_DRIVER)-gcc
AR_win64_x86_64_gcc = $(WIN64_GCC_DRIVER)-ar -r

#
# Darwin x86_64 target
#

DARWIN_GCC_DRIVER ?=  x86_64-apple-darwin

CC_darwin_x86_64_gcc = $(DARWIN_GCC_DRIVER)-gcc -c
AS_darwin_x86_64_gcc = $(DARWIN_GCC_DRIVER)-gcc -c
LR_darwin_x86_64_gcc = $(DARWIN_GCC_DRIVER)-gcc -r
LD_darwin_x86_64_gcc = $(DARWIN_GCC_DRIVER)-gcc -Wl,-Z
AR_darwin_x86_64_gcc = $(DARWIN_GCC_DRIVER)-ar -r

ifndef QCONF_OVERRIDE

CWD := $(shell $(PWD_HOST))
roots:=$(filter $(ROOT_DIR) cvs src qssl, $(subst /, ,$(CWD)))
ifneq ($(roots),)
root:=$(word $(words $(roots)), $(roots))
src_root := $(patsubst %/,%,$(subst !,/,$(dir $(subst !$(root)!,!$(root)/, $(subst /,!, $(CWD))))))
QCONF_OVERRIDE=$(src_root)/qconf-override.mk
endif
endif
ifneq ($(QCONF_OVERRIDE),)
-include $(QCONF_OVERRIDE)
endif
