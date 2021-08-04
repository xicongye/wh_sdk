#################################################################################################
# 
#       PROJECT :       WH
#
#       FILENAME:       Makefile
#
#       FUNCTION:       Common Makefile Script 
#
#       AUTHOR:         yexc
#
#       DATE:           2018/10/26
#
#################################################################################################

HEADERS := $(patsubst %.h,$(PROGRAM_DIR)/%.h,$(HEADERS)) 
HEADERS += $(INCLUDE_DIR)/*.h
HEADERS += $(INCLUDE_DIR)/core/*.h
HEADERS += $(INCLUDE_DIR)/device/*.h
HEADERS += $(RELEASE_STARTUP_DIR)/mmu.h
C_SRCS := $(patsubst %.c,$(PROGRAM_DIR)/%.c,$(C_SRCS))
ASM_SRCS := $(patsubst %.S,$(PROGRAM_DIR)/%.S,$(ASM_SRCS))
include $(BSP_BASE)/wh_lib/wh_lib.mk
include $(BSP_BASE)/libwrap/libwrap.mk
LDFLAGS += -L$(RELEASE_DIR) $(LIB_FILE)

ASM_SRCS += $(RELEASE_STARTUP_DIR)/start.S
ASM_SRCS += $(RELEASE_STARTUP_DIR)/trap_entry.S
C_SRCS += $(BOARD_STARTUP_DIR)/init.c 
C_SRCS += $(BOARD_STARTUP_DIR)/putchar.c

LINKER_SCRIPT := $(RELEASE_STARTUP_DIR)/$(LINK_TARGET).lds
INCLUDES += -I$(BSP_BASE)/include -I$(RELEASE_DIR) -I$(RELEASE_STARTUP_DIR)
LDFLAGS += -T $(LINKER_SCRIPT) -nostartfiles

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)
LINK_OBJS += $(ASM_OBJS) $(C_OBJS)
LINK_DEPS += $(LINKER_SCRIPT)
CLEAN_OBJS += $(LINK_OBJS)

CFLAGS += -g
CFLAGS += -march=$(ARCH)
CFLAGS += -mabi=$(ABI)
CFLAGS += -mcmodel=medany
CFLAGS += -Wl,-Map,$(PROGRAM_DIR)/$(TARGET).map

PLATFORM ?= BOARD

ifeq ($(PLATFORM), BOARD)
CFLAGS += -DON_BOARD
else ifeq ($(PLATFORM), SPIKE)
CFLAGS += -DON_SPIKE
else ifeq ($(PLATFORM), VCS)
CFLAGS += -DON_VCS
endif


ifeq ($(DCACHE_EN), 1)
CFLAGS += -DENABLE_DCACHE
else
endif

ifeq ($(CLKGATE_EN), 1)
CFLAGS += -DENABLE_CLKGATE
else
endif

# Generate ELF file, ASM file, MEM file, HEX file, MAP file, ELF information file
software: \
          clean \
          $(RELEASE_STARTUP_DIR)/build-setting-stamp \
          $(PROGRAM_DIR)/$(TARGET).elf \
          $(PROGRAM_DIR)/$(TARGET).bin \
          $(PROGRAM_DIR)/$(TARGET).asm \
          $(OUTPUT_DIR)/$(TARGET)/build-coe-stamp  \
          PRINT_SIZE

$(RELEASE_STARTUP_DIR)/build-setting-stamp: $(RELEASE_DIR)/setting.mk $(PROGRAM_DIR)/Makefile $(SDK_ROOT)/make_env_var $(SDK_ROOT)/Makefile
	rm -rf $(RELEASE_STARTUP_DIR)
	rm -rf $(RELEASE_DIR)/build
	### initial startup files ###
	mkdir $(RELEASE_STARTUP_DIR)
	cp $(BSP_BASE)/env/no_change/dcache.lds    $(abspath $(RELEASE_STARTUP_DIR)) 
	cp $(BSP_BASE)/env/no_change/flash.lds     $(abspath $(RELEASE_STARTUP_DIR)) 
	cp $(BSP_BASE)/env/no_change/dhrystone.lds $(abspath $(RELEASE_STARTUP_DIR)) 
	cp $(BSP_BASE)/env/no_change/start.S       $(abspath $(RELEASE_STARTUP_DIR)) 
	cp $(BSP_BASE)/env/no_change/trap_entry.S  $(abspath $(RELEASE_STARTUP_DIR)) 
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/flash.lds
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/flash.lds
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/dhrystone.lds	
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/dhrystone.lds
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/dcache.lds
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'          $(abspath $(RELEASE_STARTUP_DIR))/dcache.lds
	sed -i 's/DTIM_BASE/$(DTIM_BASE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/flash.lds
	sed -i 's/DTIM_SIZE/$(DTIM_SIZE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/flash.lds
	sed -i 's/DTIM_BASE/$(DTIM_BASE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/dhrystone.lds	
	sed -i 's/DTIM_SIZE/$(DTIM_SIZE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/dhrystone.lds
	sed -i 's/CLINT_BASE/$(CLINT_BASE)/g'      $(abspath $(RELEASE_STARTUP_DIR))/start.S
	cp $(BSP_BASE)/env/no_change/mmu.h         $(abspath $(RELEASE_STARTUP_DIR))
	sed -i 's/CLK_FRQ/$(CLK_FRQ)/g'            $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/PLIC_BASE/$(PLIC_BASE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/mmu.h	
	sed -i 's/CLINT_BASE/$(CLINT_BASE)/g'      $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/MMIO_BASE/$(MMIO_BASE)/g'        $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/INT_NUM/$(INT_NUM)/g'            $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/CORE_NUM/$(CORE_NUM)/g'          $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/CEII_EN/$(CEII_EN)/g'            $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	sed -i 's/RTC_FRQ/$(RTC_FRQ)/g'            $(abspath $(RELEASE_STARTUP_DIR))/mmu.h
	touch $(RELEASE_STARTUP_DIR)/build-setting-stamp
	### initial build directory ###
	mkdir -p $(RELEASE_DIR)/build/core
	mkdir -p $(RELEASE_DIR)/build/device
	mkdir -p $(RELEASE_DIR)/build/libwarp/misc
	mkdir -p $(RELEASE_DIR)/build/libwarp/stdlib
	mkdir -p $(RELEASE_DIR)/build/libwarp/sys

ifeq ($(DTIM),1)
	cp $(RELEASE_STARTUP_DIR)/flash.lds $(RELEASE_STARTUP_DIR)/link.lds
else
	cp $(RELEASE_STARTUP_DIR)/dcache.lds $(RELEASE_STARTUP_DIR)/link.lds
endif

$(ASM_OBJS): %.o: %.S $(HEADERS) $(RELEASE_STARTUP_DIR)/build-setting-stamp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS) $(RELEASE_STARTUP_DIR)/build-setting-stamp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(PROGRAM_DIR)/$(TARGET).elf: $(LINK_OBJS) $(LINK_DEPS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $(PROGRAM_DIR)/$(TARGET).elf $(LDFLAGS)    #Generate ELF file, MAP file
	$(READELF) -a $(PROGRAM_DIR)/$(TARGET).elf >> $(PROGRAM_DIR)/$(TARGET).script   #Generate Script file

$(PROGRAM_DIR)/$(TARGET).asm: $(PROGRAM_DIR)/$(TARGET).elf
	$(OBJDUMP) -D $(PROGRAM_DIR)/$(TARGET).elf > $(PROGRAM_DIR)/$(TARGET).asm        #Generate ASM file

PRINT_SIZE: $(PROGRAM_DIR)/$(TARGET).elf
	$(SIZE) $(PROGRAM_DIR)/$(TARGET).elf

$(PROGRAM_DIR)/$(TARGET).bin: $(PROGRAM_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $(PROGRAM_DIR)/$(TARGET).elf $(PROGRAM_DIR)/$(TARGET).bin

$(OUTPUT_DIR)/$(TARGET)/build-coe-stamp: $(PROGRAM_DIR)/$(TARGET).elf
	rm -rf $(OUTPUT_DIR)/$(TARGET)
	mkdir -p $(OUTPUT_DIR)/$(TARGET)
	mkdir -p $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_raw
	cp -r $(PROGRAM_DIR)/* $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_raw
	$(ELF2HEX) --bit-width 8  --input $(PROGRAM_DIR)/$(TARGET).elf --output $(OUTPUT_DIR)/$(TARGET)/dpram_8.coe
	$(ELF2HEX) --bit-width 16 --input $(PROGRAM_DIR)/$(TARGET).elf --output $(OUTPUT_DIR)/$(TARGET)/dpram_16.coe
	$(ELF2HEX) --bit-width 32 --input $(PROGRAM_DIR)/$(TARGET).elf --output $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe
	$(ELF2HEX) --bit-width 64 --input $(PROGRAM_DIR)/$(TARGET).elf --output $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe
	$(ELF2HEX) --bit-width 128 --input $(PROGRAM_DIR)/$(TARGET).elf --output $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_bin_mem.coe
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_bin_mem.coe
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_128_bin_mem.coe
	touch $(OUTPUT_DIR)/$(TARGET)/build-coe-stamp

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS)
	rm -rf $(OUTPUT_DIR)/$(TARGET)
	rm -rf $(RELEASE_STARTUP_DIR)
	rm -rf $(BUILD_DIR)

