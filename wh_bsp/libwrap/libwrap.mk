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

LIBWRAP_SOURCE_DIR := $(LIBWRAP_DIR)
LIBWRAP_BUILD_DIR := $(RELEASE_DIR)/build/libwarp

LIBWRAP_MISC_SRCS := $(wildcard $(LIBWRAP_SOURCE_DIR)/misc/*.c)
LIBWRAP_STDLIB_SRCS := $(wildcard $(LIBWRAP_SOURCE_DIR)/stdlib/*.c)
LIBWRAP_SYS_SRCS := $(wildcard $(LIBWRAP_SOURCE_DIR)/sys/*.c)
LIBWRAP_SRCS := $(LIBWRAP_MISC_SRCS) $(LIBWRAP_STDLIB_SRCS) $(LIBWRAP_SYS_SRCS)
LIBWRAP_SRCS_OBJS := $(patsubst $(LIBWRAP_SOURCE_DIR)/%.c,$(LIBWRAP_BUILD_DIR)/%.o,$(LIBWRAP_SRCS))

LIBWRAP_SYMS :=  free \
	_open _lseek _read _write _fstat _stat _close _link _unlink \
	_execve _fork _getpid _kill _wait \
	_isatty _times _sbrk _exit puts _gettimeofday

LIBWRAP := $(RELEASE_DIR)/libwrap.a

LINK_DEPS += $(LIBWRAP)

LDFLAGS += $(foreach s,$(LIBWRAP_SYMS),-Wl,--wrap=$(s))

LDFLAGS += -L$(LIBWRAP_DIR) -Wl,--start-group -lwrap -lc -Wl,--end-group

CLEAN_OBJS += $(LIBWRAP_SRCS_OBJS)

$(LIBWRAP_SRCS_OBJS): $(LIBWRAP_BUILD_DIR)/%.o: $(LIBWRAP_SOURCE_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBWRAP): $(LIBWRAP_SRCS_OBJS)
	$(AR) rcs $@ $^

