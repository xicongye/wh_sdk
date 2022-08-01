PWD := $(abspath .)
TOOLCHAIN_SOURCE_PATH := $(abspath riscv-gnu-toolchain)
TOOLCHAIN_COMMIT_ID := 409b951ba6621f2f115aebddfb15ce2dd78ec24f

SPIKE_SOURCE_PATH := $(abspath riscv-isa-sim)

OPENOCD_SOURCE_PATH := $(abspath riscv-openocd)

ELF2HEX_SOURCE_PATH := $(abspath elf2hex)

PK_SOURCE_PATH := $(abspath riscv-pk)

RISCV_TESTS_SOURCE_PATH := $(abspath riscv-tests)

TOOLCHAIN_INSTALL_PATH := $(PWD)/toolchain-install
TOOLCHAIN_BUILD_PATH := $(PWD)/toolchain-build

BARE_METAL_MULTILIBS_GEN := \
	rv32i-ilp32-- \
	rv32ic-ilp32-- \
	rv32im-ilp32-- \
	rv32iac-ilp32-- \
	rv32imc-ilp32-- \
	rv32ima-ilp32-- \
	rv32imac-ilp32-- \
	rv32imfc-ilp32f-- \
	rv32imafc-ilp32f-- \
	rv32imfdc-ilp32d-- \
	rv32imafdc-ilp32d-- \
	rv64i-lp64-- \
	rv64ic-lp64-- \
	rv64im-lp64-- \
	rv64iac-lp64-- \
	rv64imc-lp64-- \
	rv64ima-lp64-- \
	rv64imac-lp64-- \
	rv64imfdc-lp64d-- \
	rv64imafdc-lp64d-- \

all:
	@echo "build something"


###### Build GCC/GDB #####
checkout-riscv-gnu-toolchain:
	git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git $(TOOLCHAIN_SOURCE_PATH)
	cd $(TOOLCHAIN_SOURCE_PATH); git checkout --detach $(TOOLCHAIN_COMMIT_ID)
	cd $(TOOLCHAIN_SOURCE_PATH); git submodule update --init --recursive

$(TOOLCHAIN_SOURCE_PATH)/configure: checkout-riscv-gnu-toolchain

build-riscv-gnu-toolchain: $(TOOLCHAIN_SOURCE_PATH)/configure
	cd $(TOOLCHAIN_SOURCE_PATH)/riscv-gcc/gcc/config/riscv; rm t-elf-multilib; ./multilib-generator $(BARE_METAL_MULTILIBS_GEN) > t-elf-multilib
	rm -rf $(TOOLCHAIN_BUILD_PATH)/$@
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(TOOLCHAIN_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --enable-multilib --with-cmodel=medany; make -j$$(nproc); make linux -j$$(nproc)



###### Build Spike #####
build-riscv-isa-sim:
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(SPIKE_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH); make install -j$$(nproc)

###### Build OpenOCD #####
build-riscv-openocd:
	cd $(OPENOCD_SOURCE_PATH); ./bootstrap
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(OPENOCD_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH); make install -j$$(nproc)

	#cd $(TOOLCHAIN_BUILD_PATH); $(OPENOCD_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --enable-ftdi; make install -j$$(nproc)

###### Build ELF2HEX #####
build-elf2hex:
	export PATH=$(TOOLCHAIN_BUILD_PATH)/bin:$$PATH
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(ELF2HEX_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --target=riscv64-unknown-elf; make install -j$$(nproc)
		
###### Build PK #####
build-pk:
	export PATH=$(TOOLCHAIN_BUILD_PATH)/bin:$$PATH
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(PK_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --host=riscv64-unknown-elf; make install -j$$(nproc)

###### Build riscv-tests ####
build-riscv-tests:
	rm -rf $(TOOLCHAIN_BUILD_PATH)/$@
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(RISCV_TESTS_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH)/riscv64-unknown-elf -with-xlen=64; make install -j$$(nproc)


