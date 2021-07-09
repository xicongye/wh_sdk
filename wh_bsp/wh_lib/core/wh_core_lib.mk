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

CORE_SOURCE_DIR := $(WH_CORE_LIB_DIR)
CORE_BUILD_DIR := $(RELEASE_DIR)/build/core

WH_CORE_ASMS := $(wildcard $(CORE_SOURCE_DIR)/*.S)
WH_CORE_ASMS_OBJS := $(patsubst $(CORE_SOURCE_DIR)/%.S,$(CORE_BUILD_DIR)/%.o,$(WH_CORE_ASMS))

WH_CORE_SRCS := $(wildcard $(CORE_SOURCE_DIR)/*.c)
WH_CORE_SRCS_OBJS := $(patsubst $(CORE_SOURCE_DIR)/%.c,$(CORE_BUILD_DIR)/%.o,$(WH_CORE_SRCS))

WH_CORE_OBJS := $(WH_CORE_ASMS_OBJS) $(WH_CORE_SRCS_OBJS)

WH_CORE_LIBWRAP := $(RELEASE_DIR)/libwhcore.a

LIB_FILE += -lwhcore

LINK_DEPS += $(WH_CORE_LIBWRAP)

CLEAN_OBJS += $(WH_CORE_OBJS)

$(WH_CORE_SRCS_OBJS): $(CORE_BUILD_DIR)/%.o: $(CORE_SOURCE_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_CORE_ASMS_OBJS): $(CORE_BUILD_DIR)/%.o: $(CORE_SOURCE_DIR)/%.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_CORE_LIBWRAP): $(WH_CORE_OBJS)
	$(AR) rcs $@ $^


