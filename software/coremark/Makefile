TARGET := coremark

C_SRCS := \
	core_list_join.c \
	core_main.c \
	core_matrix.c \
	core_state.c \
	core_util.c \
	core_portme.c \

HEADERS := \
	coremark.h \
	core_portme.h \

#CFLAGS := -O2 -fno-common -funroll-loops -finline-functions --param max-inline-insns-auto=20 -falign-functions=4 -falign-jumps=4 -falign-loops=4
CFLAGS := -O3 -funroll-all-loops -finline-limit=600 -ftree-dominator-opts -fno-if-conversion2 -fselective-scheduling -fno-code-hoisting
#CFLAGS := -O2
CFLAGS += -DFLAGS_STR=\""$(CFLAGS)"\"
CFLAGS += -DITERATIONS=3000 -DPERFORMANCE_RUN=1 -DMAIN_HAS_NOARGC=1 -DHAS_STDIO -DHAS_PRINTF -DHAS_TIME_H -DUSE_CLOCK -DHAS_FLOAT=1
CFLAGS += -I/home/yexicong/work/GEM5/stable/gem5/include
LDFLAGS := -L/home/yexicong/work/GEM5/stable/gem5/util/m5/build/riscv/out
LDFLAGS += -lm5
LDFLAGS += -Wl,--wrap=printf

