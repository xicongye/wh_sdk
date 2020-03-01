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

WH_DEVICE_SRCS := \
	can.c \
	etimer2.c \
	etimer.c \
	gpio.c \
	i2c.c \
	oled.c \
	oledfont.c \
	qspi.c \
	spi.c \
	uart2.c \
	uart.c \
	vga.c \

WH_DEVICE_ASMS := 

WH_DEVICE_ASMS := $(foreach f,$(WH_DEVICE_ASMS),$(WH_DEVICE_LIB_DIR)/$(f))
WH_DEVICE_ASMS_OBJS := $(WH_DEVICE_ASMS:.S=.o)

WH_DEVICE_SRCS := $(foreach f,$(WH_DEVICE_SRCS),$(WH_DEVICE_LIB_DIR)/$(f))
WH_DEVICE_SRCS_OBJS := $(WH_DEVICE_SRCS:.c=.o)

WH_DEVICE_OBJS := $(WH_DEVICE_ASMS_OBJS) $(WH_DEVICE_SRCS_OBJS)

WH_DEVICE_LIBWRAP := $(RELEASE_DIR)/libwhdevice.a

LIB_FILE += -lwhdevice

LINK_DEPS += $(WH_DEVICE_LIBWRAP)

CLEAN_OBJS += $(WH_DEVICE_OBJS)

$(WH_DEVICE_SRCS_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_DEVICE_ASMS_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(WH_DEVICE_LIBWRAP): $(WH_DEVICE_OBJS)
	$(AR) rcs $@ $^

