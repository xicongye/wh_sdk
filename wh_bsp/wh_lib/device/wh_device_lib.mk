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

WH_DEVICE_LIB_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
WH_DEVICE_LIB_DIR := $(WH_DEVICE_LIB_DIR:/=)

DEVICE_SOURCE_DIR := $(WH_DEVICE_LIB_DIR)
DEVICE_BUILD_DIR := $(RELEASE_DIR)/build/device

WH_DEVICE_ASMS := $(wildcard $(DEVICE_SOURCE_DIR)/*.S)
WH_DEVICE_ASMS_OBJS := $(patsubst $(DEVICE_SOURCE_DIR)/%.S,$(DEVICE_BUILD_DIR)/%.o,$(WH_DEVICE_ASMS))

WH_DEVICE_SRCS := $(wildcard $(DEVICE_SOURCE_DIR)/*.c)
WH_DEVICE_SRCS_OBJS := $(patsubst $(DEVICE_SOURCE_DIR)/%.c,$(DEVICE_BUILD_DIR)/%.o,$(WH_DEVICE_SRCS))

WH_DEVICE_OBJS := $(WH_DEVICE_ASMS_OBJS) $(WH_DEVICE_SRCS_OBJS)

WH_DEVICE_LIBWRAP := $(RELEASE_DIR)/libwhdevice.a

LIB_FILE += -lwhdevice

LINK_DEPS += $(WH_DEVICE_LIBWRAP)

CLEAN_OBJS += $(WH_DEVICE_OBJS)

$(WH_DEVICE_SRCS_OBJS): $(DEVICE_BUILD_DIR)/%.o: $(DEVICE_SOURCE_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_DEVICE_ASMS_OBJS): $(DEVICE_BUILD_DIR)/%.o: $(DEVICE_SOURCE_DIR)/%.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_DEVICE_LIBWRAP): $(WH_DEVICE_OBJS)
	$(AR) rcs $@ $^


