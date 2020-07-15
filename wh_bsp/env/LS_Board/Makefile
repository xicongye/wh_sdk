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

# TODO
HEADERS := $(patsubst %.h,$(PROGRAM_DIR)/%.h,$(HEADERS))
C_SRCS := $(patsubst %.c,$(PROGRAM_DIR)/%.c,$(C_SRCS))
ASM_SRCS := $(patsubst %.S,$(PROGRAM_DIR)/%.S,$(ASM_SRCS))

include $(BSP_BASE)/wh_lib/wh_lib.mk
include $(BSP_BASE)/libwrap/libwrap.mk
LDFLAGS += -L$(RELEASE_DIR) $(LIB_FILE)

ENV_DIR = $(BSP_BASE)/env
BOARD_DIR = $(ENV_DIR)/$(BOARD)

ASM_SRCS += $(RELEASE_DIR)/start.S
ASM_SRCS += $(RELEASE_DIR)/trap_entry.S
C_SRCS += $(BOARD_DIR)/init.c $(BOARD_DIR)/putchar.c
LINKER_SCRIPT := $(RELEASE_DIR)/$(LINK_TARGET).lds
INCLUDES += -I$(BSP_BASE)/include

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
CFLAGS += -Wl,-Map,$(TARGET).map

PLATFORM ?= BOARD

ifeq ($(PLATFORM), BOARD)
CFLAGS += -DON_BOARD
else ifeq ($(PLATFORM), SPIKE)
CFLAGS += -DON_SPIKE
HOST_IP = localhost
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
software: clean pre_process $(TARGET).elf $(TARGET).asm PRINT_SIZE

pre_process: $(RELEASE_DIR)/setting.mk
	### initial link.lds ###
	cp $(BSP_BASE)/env/no_change/dcache.lds $(abspath $(RELEASE_DIR)) 
	cp $(BSP_BASE)/env/no_change/flash.lds $(abspath $(RELEASE_DIR)) 
	cp $(BSP_BASE)/env/no_change/dhrystone.lds $(abspath $(RELEASE_DIR)) 
	cp $(BSP_BASE)/env/no_change/start.S $(abspath $(RELEASE_DIR)) 
	cp $(BSP_BASE)/env/no_change/trap_entry.S $(abspath $(RELEASE_DIR)) 
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'  $(abspath $(RELEASE_DIR))/flash.lds
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'  $(abspath $(RELEASE_DIR))/flash.lds
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'  $(abspath $(RELEASE_DIR))/dhrystone.lds	
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'  $(abspath $(RELEASE_DIR))/dhrystone.lds
	sed -i 's/MEM_BASE/$(MEM_BASE)/g'  $(abspath $(RELEASE_DIR))/dcache.lds
	sed -i 's/MEM_SIZE/$(MEM_SIZE)/g'  $(abspath $(RELEASE_DIR))/dcache.lds
	sed -i 's/DTIM_BASE/$(DTIM_BASE)/g'  $(abspath $(RELEASE_DIR))/flash.lds
	sed -i 's/DTIM_SIZE/$(DTIM_SIZE)/g'  $(abspath $(RELEASE_DIR))/flash.lds
	sed -i 's/DTIM_BASE/$(DTIM_BASE)/g'  $(abspath $(RELEASE_DIR))/dhrystone.lds	
	sed -i 's/DTIM_SIZE/$(DTIM_SIZE)/g'  $(abspath $(RELEASE_DIR))/dhrystone.lds
	sed -i 's/CLINT_BASE/$(CLINT_BASE)/g' $(abspath $(RELEASE_DIR))/start.S
	### initial mmu.h ###
	cp $(BSP_BASE)/env/no_change/mmu.h      $(abspath $(INCLUDE_DIR))
	sed -i 's/CLK_FRQ/$(CLK_FRQ)/g'         $(abspath $(INCLUDE_DIR))/mmu.h
	sed -i 's/PLIC_BASE/$(PLIC_BASE)/g'     $(abspath $(INCLUDE_DIR))/mmu.h	
	sed -i 's/CLINT_BASE/$(CLINT_BASE)/g'   $(abspath $(INCLUDE_DIR))/mmu.h
	sed -i 's/MMIO_BASE/$(MMIO_BASE)/g'     $(abspath $(INCLUDE_DIR))/mmu.h
	sed -i 's/INT_NUM/$(INT_NUM)/g'         $(abspath $(INCLUDE_DIR))/mmu.h
	sed -i 's/CORE_NUM/$(CORE_NUM)/g'       $(abspath $(INCLUDE_DIR))/mmu.h
	sed -i 's/ECII_EN/$(ECII_EN)/g'         $(abspath $(INCLUDE_DIR))/mmu.h

ifneq ($(CORE_NUM),1)
ifneq ($(CORE_NUM),2)
    $(error CORE_NUM=$(CORE_NUM) doesnot support, must be 1 or 2)
endif
endif	

ifeq ($(DTIM),1)
ifeq ($(PROGRAM), dhrystone)
	cp $(RELEASE_DIR)/dhrystone.lds $(RELEASE_DIR)/link.lds
else ifeq ($(PROGRAM), dhrystone_sim)
	cp $(RELEASE_DIR)/dhrystone.lds $(RELEASE_DIR)/link.lds
else
	cp $(RELEASE_DIR)/flash.lds $(RELEASE_DIR)/link.lds
endif
else
	cp $(RELEASE_DIR)/dcache.lds $(RELEASE_DIR)/link.lds
endif


$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(TARGET).elf: $(PROGRAM_DIR) $(LINK_OBJS) $(LINK_DEPS) 
	rm -rf $(OUTPUT_DIR)/$(TARGET)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $(TARGET).elf $(LDFLAGS)    #Generate ELF file, MAP file
	cp $(TARGET).elf $(PROGRAM_DIR)
	mkdir -p $(OUTPUT_DIR)/$(TARGET)
	mv $(TARGET).elf $(OUTPUT_DIR)/$(TARGET)
	mv $(TARGET).map $(OUTPUT_DIR)/$(TARGET)
	$(READELF) -a $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf >> $(OUTPUT_DIR)/$(TARGET)/$(TARGET).script   #Generate Script file
	mkdir -p $(OUTPUT_DIR)/$(TARGET)/$(PROGRAM)_raw
	cp -r $(PROGRAM_DIR)/* $(OUTPUT_DIR)/$(TARGET)/$(PROGRAM)_raw



$(TARGET).asm: $(TARGET).elf
	$(OBJDUMP) -D $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf > $(OUTPUT_DIR)/$(TARGET)/$(TARGET).asm        #Generate ASM file
	#$(OBJDUMP) --source --all-headers --demangle --line-number --wide  -D $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf > $(OUTPUT_DIR)/$(TARGET)/hentai.asm     #Generate ASM file

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET)/$(TARGET).hex    #Generate HEX file

PRINT_SIZE: $(TARGET).elf
	$(SIZE) $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(OUTPUT_DIR)/$(TARGET)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET)/$(TARGET).bin  #Generate BIN file

$(TARGET).mem: $(TARGET).bin											#Generate MEM file
	xxd  -e -g 4  -cols 4   $(OUTPUT_DIR)/$(TARGET)/$(TARGET).bin > tmp_32.log
	awk '{printf "%8s\n", $$2}' tmp_32.log >  $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe
	rm tmp_32.log
	xxd  -e -g 8  -cols 8   $(OUTPUT_DIR)/$(TARGET)/$(TARGET).bin > tmp_64.log
	awk '{printf "%16s\n", $$2}' tmp_64.log >  $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe
	rm tmp_64.log
	xxd  -e -g 16 -cols 16  $(OUTPUT_DIR)/$(TARGET)/$(TARGET).bin > tmp_128.log
	awk '{printf "%32s\n", $$2}' tmp_128.log >  $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe
	rm tmp_128.log
	xxd  -e -g 1  -cols 1   $(OUTPUT_DIR)/$(TARGET)/$(TARGET).bin > tmp_8.log
	awk '{print $$2}' tmp_8.log >  $(OUTPUT_DIR)/$(TARGET)/dpram_8.coe
	rm tmp_8.log
	sed -i 's/\s/0/g' $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe
	sed -i 's/\s/0/g' $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe
	sed -i 's/\s/0/g' $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe
	sed -i 's/\s/0/g' $(OUTPUT_DIR)/$(TARGET)/dpram_8.coe
	# fill zero	
	awk '{print $1} END{for(i = NR + 1; i < 65536; i++) print "00000000000000000000000000000000"}' $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe > $(OUTPUT_DIR)/$(TARGET)/tmp_128.log
	mv $(OUTPUT_DIR)/$(TARGET)/tmp_128.log $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe
	awk '{print $1} END{for(i = NR + 1; i < 65536; i++) print "0000000000000000"}' $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe > $(OUTPUT_DIR)/$(TARGET)/tmp_64.log
	mv $(OUTPUT_DIR)/$(TARGET)/tmp_64.log $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe
	awk '{print $1} END{for(i = NR + 1; i < 65536; i++) print "00000000"}' $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe > $(OUTPUT_DIR)/$(TARGET)/tmp_32.log
	mv $(OUTPUT_DIR)/$(TARGET)/tmp_32.log $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe
	awk '{print $1} END{for(i = NR + 1; i < 65536; i++) print "00"}' $(OUTPUT_DIR)/$(TARGET)/dpram_8.coe > $(OUTPUT_DIR)/$(TARGET)/tmp_8.log
	mv $(OUTPUT_DIR)/$(TARGET)/tmp_8.log $(OUTPUT_DIR)/$(TARGET)/dpram_8.coe

#bin 
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_bin_mem.coe
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_bin_mem.coe
	$(SCRIPT_DIR)/gen_bin.pl $(OUTPUT_DIR)/$(TARGET)/dpram_128.coe > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_128_bin_mem.coe

#hex byte
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)/\4/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_hex_byte_mem_0.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)/\3/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_hex_byte_mem_1.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)/\2/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_hex_byte_mem_2.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_32.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)/\1/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_32_hex_byte_mem_3.coe

	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\8/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_0.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\7/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_1.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\6/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_2.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\5/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_3.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\4/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_4.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\3/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_5.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\2/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_6.coe
	cat $(OUTPUT_DIR)/$(TARGET)/dpram_64.coe | sed -r 's/(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)(\w\w)/\1/' > $(OUTPUT_DIR)/$(TARGET)/$(TARGET)_64_hex_byte_mem_7.coe

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS)
	rm -rf $(OUTPUT_DIR)/$(TARGET)


