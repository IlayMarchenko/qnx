DEFCOMPILER_TYPE_x86_64=gcc

USE_ROOT_INCLUDE=$(call mk_use_list, usr/local/include usr/include)
USE_ROOT_LIB=$(call mk_use_list, $(CPUDIR)/lib $(CPUDIR)/usr/lib lib lib/w32api)

INSTALL_ROOT_AR=$(INSTALL_ROOT_win64)/$(CPUDIR)
INSTALL_ROOT_EX=$(INSTALL_ROOT_win64)/$(CPUDIR)
INSTALL_ROOT_SO=$(INSTALL_ROOT_win64)/$(CPUDIR)
INSTALL_ROOT_HDR=$(INSTALL_ROOT_win64)/usr/include

IMAGE_PREF_AR=lib

IMAGE_SUFF_AR=.a

IMAGE_PREF_EX=
IMAGE_SUFF_EX=.exe
IMAGE_PREF_SO=
IMAGE_SUFF_SO=.dll

WIN64_DEFS += -D__X86_64__ -D__LITTLEENDIAN__
CC_win64_x86_64_gcc += $(WIN64_DEFS)
AS_win64_x86_64_gcc += $(WIN64_DEFS) 
LR_win64_x86_64_gcc += $(WIN64_DEFS) 
LD_win64_x86_64_gcc += $(WIN64_DEFS) 

# So all Win64 apps get command line wildcarding.
SRCVPATH+=$(SRCVPATH_$(filter a so dll,$(VARIANT_LIST))_$(COMPILER_TYPE))
SRCS+=$(SRCS_$(filter a so dll,$(VARIANT_LIST))_$(COMPILER_TYPE))

SONAME=$(empty)

VERSION_TAG_SO=$(space)

# When doing a shared object, we also want to create/install an import library
BUILDNAME_IM=$(IMAGE_PREF_AR)$(NAME)$(VARIANT_TAG).dll.a
FULLNAME_IM=$(CURDIR)/$(BUILDNAME_IM)
INSTALLNAME_IM=$(INSTALL_ROOT_$(BUILD_TYPE))/lib/$(BUILDNAME_IM)
ld_SO=-Wl,--out-implib -Wl,$(FULLNAME_IM)
ld_DLL=$(ld_SO)
LD_win64_x86_64_gcc_qcc += $(ld_$(BUILD_TYPE))
LD_win64_x86_64_gcc_gcc += $(ld_$(BUILD_TYPE))
LD_win64_x86_64_gcc     += $(ld_$(BUILD_TYPE))

win64_install_extra_SO=-$(CP_HOST) $(BUILDNAME_IM) $(INSTALLNAME_IM) $(NEWLINE)
win64_install_extra_DLL=$(win64_install_extra_SO)
install_extra+=$(win64_install_extra_$(BUILD_TYPE))
