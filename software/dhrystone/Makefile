TARGET := dhrystone
ASM_SRCS := 
C_SRCS := 

DHRY_SRCS := dhry_1.c dhry_2.c
DHRY_SRCS := $(patsubst %.c,$(PROGRAM_DIR)/%.c,$(DHRY_SRCS))
#DHRY_CFLAGS := -O3 -DTIME -fno-inline -fno-builtin-printf -Wno-implicit
DHRY_CFLAGS := -O3 -DTIME -Wno-implicit #-flto

CFLAGS := -DITERATIONS=5000000
LDFLAGS := #-Wl,--wrap=printf

DHRY_OBJS := $(patsubst %.c,%.o,$(DHRY_SRCS))
LINK_OBJS := $(DHRY_OBJS)

$(DHRY_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(DHRY_CFLAGS) -c -o $@ $<

