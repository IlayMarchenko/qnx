#
# Win64 qconfig.mk file
#
BUILDENV := qss

override QNX_TARGET	:= $(shell '$(QNX_HOST)/usr/bin/canonical_dos_path.exe' '$(QNX_TARGET)')
override QNX_HOST	:= $(shell '$(QNX_HOST)/usr/bin/canonical_dos_path.exe' '$(QNX_HOST)')
ifneq ($(notdir $(patsubst %/,%,$(dir $(PWD)))), cygwin)
OS :=
endif

#
# The base directories for the installation trees.
#
INSTALL_ROOT_nto		:= $(QNX_TARGET)
INSTALL_ROOT_win64	:= /dev/null

#
# The base directories for accessing headers/libraries for various OS's.
#
USE_ROOT_nto		:= $(QNX_TARGET)
USE_ROOT_win64		:= 

MKFILES_ROOT := $(QNX_TARGET)/usr/include/mk

#
# The MG_HOST utilty is to "mark generated" any file that you'd normally
# consider a source file (something with a .c, .s, etc. extension),
# but is actually generated by a program. E.g., the kernel call
# source files in libc. It's purely for documentation purposes. 
#
MG_HOST = $(QNX_HOST)/usr/bin/true
#
# Copy a space separated list of files (possibly with wildcards) to an
# installation directory.
#
CP_HOST = $(QNX_HOST)/usr/bin/qnx_cp -vfpc $(CP_HOST_OPTIONS)
#
# Create a symbolic link.
#
LN_HOST = $(QNX_HOST)/usr/bin/ln-w -s $(LN_HOST_OPTIONS)
#
# Delete a space separated list of files (possibly with wildcards).
#
RM_HOST = $(QNX_HOST)/usr/bin/rm -f $(RM_HOST_OPTIONS)
#
# Create an empty file
#
TOUCH_HOST = $(QNX_HOST)/usr/bin/touch.exe
#
# Print the full path of the current working directory to standard output.
# Note: on mingw based system, make must work with dos style paths
# (e.g. c:/dir/file) since the compiler is a win64 native application.
PWD_HOST = $(QNX_HOST)/usr/bin/pwd.exe -W

#
# Generate a space separated list of files in a directory tree, ignoring
# anything in a CVS or RCS directory.
#
FL_HOST = sh $(MKFILES_ROOT)/flist-win64

#
# Generate an assembler definition file from an object files.
#
MKASMOFF_HOST = $(QNX_HOST)/usr/bin/mkasmoff 
#
# Mark something as a privledged executable (setuid)
#
MP_HOST = $(MKFILES_ROOT)/makepriv-nt
#
# Echo text to the console
#
ECHO_HOST = $(QNX_HOST)/usr/bin/echo
HOST_HOST = hostname
DATE_HOST = $(QNX_HOST)/usr/bin/date +%Y/%m/%d-%H:%M:%S-%Z
USER_HOST = $(ECHO_HOST) $(USERNAME)
FLEX_HOST = $(QNX_HOST)/usr/bin/flex.exe
BISON_HOST = $(QNX_HOST)/usr/bin/bison.exe
ELFNOTE_HOST = $(QNX_HOST)/usr/bin/elfnote.exe

#
# CL_*	Compile and link
# CC_*	Compile C/C++ source to an object file
# AS_*	Assemble something to an object file
# AR_*  Generate an object file library (archive)
# LR_*  Link a list of objects/libraries to a relocatable object file
# LD_*  Link a list of objects/libraries to a executable/shared object
# UM_*	Add a usage message to an executable
#

#
# host system
#
CL_HOST = gcc
CC_HOST = gcc -c
AS_HOST = gcc -c
AR_HOST = gcc -A
LD_HOST = gcc
UM_HOST = $(QNX_HOST)/usr/bin/usemsg

CD_nto = qcc
COMPILER_DRIVER = $(CD_$(OS))

dash:=-
comma:=,
gcc_ver_suffix=$(if $(GCC_VERSION),$(dash)$(GCC_VERSION))
gcc_ver_string=$(if $(GCC_VERSION),$(GCC_VERSION)$(comma))

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
AR_nto_x86_64_gcc_qcc = $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86_64 -a
UM_nto_x86_64_gcc_qcc = $(UM_nto_x86_64_gcc)


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

#
# Win64 X86 targets
#
CC_win64_x86_gcc = gcc -c
AS_win64_x86_gcc = gcc -c
LR_win64_x86_gcc = gcc -r
LD_win64_x86_gcc = gcc
AR_win64_x86_gcc = ar -r

# Force the current dir to be represented with drive
# (e.g. c:/... instead of /c/...)
CWD := $(shell $(PWD_HOST))
CURDIR := $(CWD)

ifndef QCONF_OVERRIDE

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
