ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic
ASVFLAG_shared = -fpic -Wa,--defsym -Wa,__PIC__=1
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_TIME_gcc)

CC_nto_x86_64_gcc += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_64_gcc += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES))
AR_nto_x86_64_gcc += -r
CC_nto_x86_64_gcc_qcc += -Wc,-Wall $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_64_gcc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES))

CC_nto_x86_64_clang += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_64_clang += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES))
AR_nto_x86_64_clang += -r 

LDBOOTSTRAP_nto_x86_64_gcc  = $(LR_nto_x86_64_gcc) -Wl,--no-keep-memory -nostartfiles -u_start
LDBOOTSTRAPPOST_nto_x86_64_gcc  = $(LRPOST_nto_x86_64_gcc)
LDBOOTSTRAP_nto_x86_64_clang  = $(LR_nto_x86_64_clang) -Wl,--no-keep-memory -nostartfiles -u_start
LDBOOTSTRAPPOST_nto_x86_64_clang  = $(LRPOST_nto_x86_64_clang) 
LDBOOTSTRAP_nto_x86_64_gcc_qcc  = $(LR_nto_x86_64_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_x86_64_gcc_qcc  = $(LRPOST_nto_x86_64_gcc_qcc)
