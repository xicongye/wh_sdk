#################################################################################################
#     
#	PROJECT :	WH
#
#	FUNCTION:	compile and disassembly the project 			
#
#	AUTHOR:		liaoll
#	EDITOR:		yexc
#
#	DATE:		2017/08/24
#	DATA:		2018/10/18
#
#
#################################################################################################

include ./make_env_var 
-include $(RELEASE_DIR)/setting.mk

#################################################################################################
#		Prints help message
#################################################################################################
.PHONY: all
all : help

help :
	@echo "**********************************************************************"
	@echo "*if you want to display this make command, you can use:"
	@echo "*	make help"
	@echo "*if you want to compile your project into executed file, you can use :"
	@echo "*	make software [ PROGRAM=hello ]"
	@echo "*if you want to upload your program into the board,you can use: "
	@echo "*	make upload [ PROGRAM=hello ]"
	@echo "*if you want to debug the program, you can use :"
	@echo "*	make run_openocd "
	@echo "*	make run_gdb [ PROGRAM=hello ] (another terminal)"
	@echo "**********************************************************************"


#################################################################################################
#		This section is for toolchain
#################################################################################################
CROSS_COMPILE ?= riscv64-unknown-elf

ifeq ($(RISCV_PATH),)
RISCV_GCC     := $(CROSS_COMPILE)-gcc
RISCV_GXX     := $(CROSS_COMPILE)-g++
RISCV_OBJDUMP := $(CROSS_COMPILE)-objdump
RISCV_OBJCOPY := $(CROSS_COMPILE)-objcopy
RISCV_GDB     := $(CROSS_COMPILE)-gdb
RISCV_AR      := $(CROSS_COMPILE)-ar
RISCV_SIZE    := $(CROSS_COMPILE)-size
RISCV_READELF := $(CROSS_COMPILE)-readelf
RISCV_AS      := $(CROSS_COMPILE)-as
SPIKE         := spike
RISCV_ELF2HEX := riscv64-unknown-elf-elf2hex
else
RISCV_GCC     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gcc)
RISCV_GXX     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-g++)
RISCV_OBJDUMP := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objdump)
RISCV_OBJCOPY := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-objcopy)
RISCV_GDB     := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-gdb)
RISCV_AR      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-ar)
RISCV_SIZE    := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-size)
RISCV_READELF := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-readelf)
RISCV_AS      := $(abspath $(RISCV_PATH)/bin/$(CROSS_COMPILE)-as)
SPIKE         := $(abspath $(RISCV_PATH)/bin/spike)
RISCV_ELF2HEX := $(abspath $(RISCV_PATH)/bin/riscv64-unknown-elf-elf2hex)
endif

ifeq ($(RISCV_OPENOCD_PATH),)
RISCV_OPENOCD := openocd
else
RISCV_OPENOCD := $(abspath $(RISCV_OPENOCD_PATH)/bin/openocd)
endif
#################################################################################################
#		This section is for Software Compilation
#################################################################################################

CC = $(RISCV_GCC)
ARCH = $(RISCV_ARCH)
ABI = $(RISCV_ABI)
AR = $(RISCV_AR)
READELF = $(RISCV_READELF)
OBJDUMP = $(RISCV_OBJDUMP)
OBJCOPY = $(RISCV_OBJCOPY)
AS = $(RISCV_AS)
SIZE = $(RISCV_SIZE)
ELF2HEX = $(RISCV_ELF2HEX)

#################################################################################################
#		This section is for uploading a program to Flash
#################################################################################################
ifeq ($(PLATFORM), BOARD)
OPENOCDCFG_NAME ?= openocd.cfg
else ifeq ($(PLATFORM), SPIKE)
OPENOCDCFG_NAME ?= spike.cfg
HOST_IP := localhost
else ifeq ($(PLATFORM), VCS)
OPENOCDCFG_NAME ?= openocd.cfg
endif
OPENOCDCFG ?= $(BOARD_STARTUP_DIR)/$(OPENOCDCFG_NAME)
OPENOCDARGS += -f $(OPENOCDCFG) 

GDB_UPLOAD_ARGS ?= --batch
GDB_PORT ?= 3333
GDB_UPLOAD_CMDS += -ex 'set remotetimeout 240'
GDB_UPLOAD_CMDS += -ex 'target extended-remote $(HOST_IP):$(GDB_PORT)'
GDB_UPLOAD_CMDS += -ex 'monitor reset halt'
#GDB_UPLOAD_CMDS += -ex 'monitor flash protect 0 64 last off'
GDB_UPLOAD_CMDS += -ex 'load'
GDB_UPLOAD_CMDS += -ex 'monitor resume'
#GDB_UPLOAD_CMDS += -ex 'monitor shutdown'
GDB_UPLOAD_CMDS += -ex 'quit'

GDBCMDS += -ex 'set remotetimeout 240'
GDBCMDS += -ex 'target extended-remote localhost:$(GDB_PORT)'

upload:
	$(RISCV_GDB) $(SOFTWARE)/$(PROGRAM)/$(TARGET).elf $(GDB_UPLOAD_ARGS) $(GDB_UPLOAD_CMDS)
	
run_sim:
	$(SPIKE) --isa=$(RISCV_ARCH) --varch=$(VARCH) -m0x40000000:0x50000000  $(SOFTWARE)/$(PROGRAM)/$(TARGET).elf

run_spike:
	$(SPIKE) --isa=$(RISCV_ARCH) --varch=$(VARCH) --rbb-port=9824 -m0x40000000:0x50000000  $(SOFTWARE)/$(PROGRAM)/$(TARGET).elf

run_openocd:
	$(RISCV_OPENOCD) $(OPENOCDARGS)

run_gdb:
	$(RISCV_GDB) $(SOFTWARE)/$(PROGRAM)/$(TARGET).elf -ex "target extended-remote $(HOST_IP):$(GDB_PORT)" -ex "load"
	
#################################################################################################
#		Create Release & Create Project & SCP
#################################################################################################

PRO_DIR = $(shell if [ -d $(PROGRAM_DIR) ]; then echo "exist"; else echo "no exist"; fi)
REL_DIR = $(shell if [ -d $(RELEASE_DIR) ]; then echo "exist"; else echo "no exist"; fi)
DATE = $(shell date)

create_project:
ifeq ($(PRO_DIR), exist)
	$(error $(PROGRAM_DIR) has existed, please remove it first)
else
	mkdir $(PROGRAM_DIR) 
	touch $(PROGRAM_DIR)/$(PROGRAM).c $(PROGRAM_DIR)/Makefile $(PROGRAM_DIR)/.gitignore
	
	@echo "Initialize C source file"
	@echo "/*********************************************************************************" >>  $(PROGRAM_DIR)/$(PROGRAM).c
	@echo "*" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       PROJECT:        $(RELEASE) " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       FILENAME:       $(PROGRAM).c " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       FUNCTION:       $(PROGRAM) driver " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       AUTHOR:         $(USER) " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       DATE:           $(DATE) " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       ISFINISH:       NO " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "* " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*       STATUS:  " >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "*********************************************************************************/" >>  $(PROGRAM_DIR)/$(PROGRAM).c

	@echo "#include \"platform.h\"" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "int main(void)" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "{" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "    /* write your code here */" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "    return 0;" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	@echo "}" >> $(PROGRAM_DIR)/$(PROGRAM).c 
	
	@echo "Initialize Makefile"
	@echo "TARGET := $(PROGRAM)" >> $(PROGRAM_DIR)/Makefile
	@echo "ASM_SRCS := " >> $(PROGRAM_DIR)/Makefile
	@echo "C_SRCS := $(PROGRAM).c" >> $(PROGRAM_DIR)/Makefile
	@echo "HEADERS := " >> $(PROGRAM_DIR)/Makefile
	@echo "CFLAGS := " >> $(PROGRAM_DIR)/Makefile
	@echo "LDFLAGS := " >> $(PROGRAM_DIR)/Makefile

	@echo "Initialize .gitignore"
	@echo "/*.o" >> $(PROGRAM_DIR)/.gitignore
	
	@echo "Done"
endif

dist-clean:
	make clean
	find . -name *.elf -delete
	find . -name *.o -delete
	find . -name *.a -delete
	find . -name *.map -delete
	find . -name *.asm -delete
	find . -name *.script -delete
	find . -name *.bin -delete
	rm -rf output
	rm -rf wh_bsp/env/LS_Board/WH32_DDR/build*
	rm -rf wh_bsp/env/LS_Board/WH32_DDR/startup
	rm -rf wh_bsp/env/LS_Board/spike/build*
	rm -rf wh_bsp/env/LS_Board/spike/startup
	rm -rf wh_bsp/env/LS_Board/spike64/build*
	rm -rf wh_bsp/env/LS_Board/spike64/startup
	rm -rf wh_bsp/env/LS_Board/WH64_DDR/build*
	rm -rf wh_bsp/env/LS_Board/WH64_DDR/startup
	rm -rf wh_bsp/env/LS_Board/WH_B_EXT/build*
	rm -rf wh_bsp/env/LS_Board/WH_B_EXT/startup
	rm -rf wh_bsp/env/LS_Board/WH_SETTING/build*
	rm -rf wh_bsp/env/LS_Board/WH_SETTING/startup

scp:
	scp -r $(OUTPUT_DIR)/$(TARGET)   $(USER)@192.168.168.197:~/project/WH/workspace/software 

PROGRAM_MK = $(shell if [ -f $(PROGRAM_DIR)/Makefile ]; then echo "exist"; else echo "no exist"; fi)

#ifeq ($(PROGRAM_MK), exist)
#include $(PROGRAM_DIR)/Makefile
#else
#$(error $(PROGRAM_DIR)/Makefile doesnot exist)
#endif

-include $(PROGRAM_DIR)/Makefile
include $(BOARD_DIR)/Makefile 
-include $(SCRIPT_DIR)/self-test.mk

