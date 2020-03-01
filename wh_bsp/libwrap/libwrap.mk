#################################################################################################                   
#     
#       PROJECT :       WH
#
#       FILENAME:       Makefile
#
#       FUNCTION:       compile and disassembly the project                     
#
#       AUTHOR:         yexc
#
#       DATE:           2018/10/26
#
#################################################################################################

LIBWRAP_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
LIBWRAP_DIR := $(LIBWRAP_DIR:/=)

LIBWRAP_SRCS := \
	sys/open.c \
	sys/lseek.c \
	sys/read.c \
	sys/write.c \
	sys/fstat.c \
	sys/stat.c \
	sys/close.c \
	sys/link.c \
	sys/unlink.c \
	sys/execve.c \
	sys/fork.c \
	sys/getpid.c \
	sys/kill.c \
	sys/wait.c \
	sys/isatty.c \
	sys/times.c \
	sys/sbrk.c \
	sys/_exit.c \
	sys/puts.c \
	misc/write_hex.c \
	sys/gettimeofday.c \
	sys/printf.c

LIBWRAP_SRCS := $(foreach f,$(LIBWRAP_SRCS),$(LIBWRAP_DIR)/$(f))
LIBWRAP_OBJS := $(LIBWRAP_SRCS:.c=.o)

LIBWRAP_SYMS :=  free \
	_open _lseek _read _write _fstat _stat _close _link _unlink \
	_execve _fork _getpid _kill _wait \
	_isatty _times _sbrk _exit puts gettimeofday

LIBWRAP := $(LIBWRAP_DIR)/libwrap.a

LINK_DEPS += $(LIBWRAP)

LDFLAGS += $(foreach s,$(LIBWRAP_SYMS),-Wl,--wrap=$(s))

# TO DO
LDFLAGS += -L$(LIBWRAP_DIR) -Wl,--start-group -lwrap -lc -Wl,--end-group

CLEAN_OBJS += $(LIBWRAP_OBJS)

$(LIBWRAP_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBWRAP): $(LIBWRAP_OBJS)
	$(AR) rcs $@ $^

