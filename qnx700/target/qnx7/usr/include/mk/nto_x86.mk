ifneq ($(COMPILER_DRIVER),qcc)
ifneq ($(BUILDENV),iox)
CCVFLAG_shared = -fpic
ASVFLAG_shared = -fpic -Wa,--defsym -Wa,__PIC__=1
else
CCVFLAG_shared = -D__SLIB_DATA_INDIRECT
ASVFLAG_shared = -D__SLIB_DATA_INDIRECT
CCVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT
ASVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT
CCVFLAG_be += -mbig-endian -D__BIGENDIAN__
ASVFLAG_be += -mbig-endian -D__BIGENDIAN__
CCVFLAG_le += -D__LITTLEENDIAN__
ASVFLAG_le += -D__LITTLEENDIAN__
CCVFLAG_a =
endif
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_TIME_gcc)

CC_nto_x86_gcc += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_gcc += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
AR_nto_x86_gcc += -r
CC_nto_x86_gcc_qcc += -Wc,-Wall $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_gcc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
CC_nto_x86_icc_qcc += -Wc,-Wall $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_icc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 

CC_nto_x86_clang += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_clang += -c -Wall -pipe -O $(addprefix -I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
AR_nto_x86_clang += -r

LDBOOTSTRAP_nto_x86_gcc  = $(LR_nto_x86_gcc) -Wl,--no-keep-memory -nostartfiles -u_start
LDBOOTSTRAPPOST_nto_x86_gcc  = $(LRPOST_nto_x86_gcc)
LDBOOTSTRAP_nto_x86_gcc_qcc  = $(LR_nto_x86_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_x86_gcc_qcc  = $(LRPOST_nto_x86_gcc_qcc)
LDBOOTSTRAP_nto_x86_icc = $(LDBOOTSTRAP_nto_x86_gcc)
LDBOOTSTRAPPOST_nto_x86_icc = $(LDBOOTSTRAPPOST_nto_x86_gcc)
LDBOOTSTRAP_nto_x86_icc_qcc = $(LDBOOTSTRAP_nto_x86_gcc)
LDBOOTSTRAPPOST_nto_x86_icc_qcc = $(LDBOOTSTRAPPOST_nto_x86_gcc)
LDBOOTSTRAP_nto_x86_clang  = $(LR_nto_x86_clang) -Wl,--no-keep-memory -nostartfiles -u_start
LDBOOTSTRAPPOST_nto_x86_clang  = $(LRPOST_nto_x86_clang) 
