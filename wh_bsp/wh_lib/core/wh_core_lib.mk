##################################################################################################     
#
#       PROJECT :       WH
#
#       FILENAME:       Makefile
#
#       FUNCTION:       compile and disassembly the project                     
#
#       AUTHOR:         yexc
#
#       DATE:           2018/12/14
#
#################################################################################################

WH_CORE_LIB_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
WH_CORE_LIB_DIR := $(WH_CORE_LIB_DIR:/=)

WH_CORE_SRCS := \
	cgu.c \
	clint.c \
	int.c \
	plic.c \
	pmp.c \
        PTE.c \
	cacheSwitch.c \
	cpu.c \
	pmu.c

WH_CORE_ASMS := privilege.S

WH_CORE_ASMS := $(foreach f,$(WH_CORE_ASMS),$(WH_CORE_LIB_DIR)/$(f))
WH_CORE_ASMS_OBJS := $(WH_CORE_ASMS:.S=.o)

WH_CORE_SRCS := $(foreach f,$(WH_CORE_SRCS),$(WH_CORE_LIB_DIR)/$(f))
WH_CORE_SRCS_OBJS := $(WH_CORE_SRCS:.c=.o)

WH_CORE_OBJS := $(WH_CORE_ASMS_OBJS) $(WH_CORE_SRCS_OBJS)

WH_CORE_LIBWRAP := $(RELEASE_DIR)/libwhcore.a

LIB_FILE += -lwhcore

LINK_DEPS += $(WH_CORE_LIBWRAP)

CLEAN_OBJS += $(WH_CORE_OBJS)

$(WH_CORE_SRCS_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_CORE_ASMS_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_CORE_LIBWRAP): $(WH_CORE_OBJS)
	$(AR) rcs $@ $^

