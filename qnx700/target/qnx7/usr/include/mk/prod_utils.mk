CCFLAGS_nto = -D_FILE_OFFSET_BITS=64
CCFLAGS_win64 = -D_FILE_OFFSET_BITS=64
CCFLAGS += $(CCFLAGS_$(OS))
