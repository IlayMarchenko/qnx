ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic
ASVFLAG_shared = -fpic -Wa,--defsym -Wa,__PIC__=1
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_TIME_gcc)

CC_nto_aarch64_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wall
AS_nto_aarch64_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
AR_nto_aarch64_gcc += -r
LD_nto_aarch64_gcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_aarch64_gcc  = $(LR_nto_aarch64_gcc) -Wl,--no-keep-memory -nostartfiles -Wl,-u_start
LDBOOTSTRAPPOST_nto_aarch64_gcc  = $(LRPOST_nto_aarch64_gcc)

CC_nto_aarch64_clang += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wall 
AS_nto_aarch64_clang += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
AR_nto_aarch64_clang += -r 
LD_nto_aarch64_clang += -Wl,--no-keep-memory 
LDBOOTSTRAP_nto_aarch64_clang = $(LR_nto_aarch64_clang) -Wl,--no-keep-memory -nostartfiles -Wl,-u_start 
LDBOOTSTRAPPOST_nto_aarch64_clang = $(LRPOST_nto_aarch64_clang)

CC_nto_aarch64_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wc,-Wall
AS_nto_aarch64_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
LD_nto_aarch64_gcc_qcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_aarch64_gcc_qcc  = $(LR_nto_aarch64_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_aarch64_gcc_qcc  = $(LRPOST_nto_aarch64_gcc_qcc)
