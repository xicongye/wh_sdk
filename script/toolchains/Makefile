PWD := $(abspath .)
TOOLCHAIN_SOURCE_PATH := $(abspath riscv-gnu-toolchain)
SPIKE_SOURCE_PATH := $(abspath riscv-isa-sim)
OPENOCD_SOURCE_PATH := $(abspath riscv-openocd)
ELF2HEX_SOURCE_PATH := $(abspath elf2hex)
PK_SOURCE_PATH := $(abspath riscv-pk)
RISCV_TESTS_SOURCE_PATH := $(abspath riscv-tests)

TOOLCHAIN_COMMIT_ID := 409b951ba6621f2f115aebddfb15ce2dd78ec24f
SPIKE_COMMIT_ID := 0ad0d9733b41e666172ff55ee946253c6dbdd080
OPENOCD_COMMIT_ID := aaf0620479bf8958040ab6483a579244584c9904
ELF2HEX_COMMIT_ID := f28a3103c06131ed3895052b1341daf4ca0b1c9c
PK_COMMIT_ID := 2efabd3e6604b8a9e8f70baf52f57696680c7855
RISCV_TESTS_COMMIT_ID := c1b75177a7bd0932aaa95f1a369b6c3e68cacdee

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
	@echo "  toolchina-install: checkout and build and install  "

toolchain-install:
	make checkout-riscv-gnu-toolchain
	make checkout-spike
	make checkout-openocd
	make checkout-elf2hex
	make checkout-pk
	make checkout-riscv-tests
	make build-riscv-gnu-toolchain
	make build-riscv-isa-sim
	make build-riscv-openocd
	make build-elf2hex
	make build-pk
	make build-riscv-tests

distclean:
	rm -rf riscv-gnu-toolchain riscv-isa-sim riscv-openocd elf2hex riscv-pk riscv-tests

### CheckOut repo ###
checkout-riscv-gnu-toolchain:
	sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo libtool bc zlib1g-dev libexpat-dev
	git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git $(TOOLCHAIN_SOURCE_PATH)
	cd $(TOOLCHAIN_SOURCE_PATH); git checkout --detach $(TOOLCHAIN_COMMIT_ID)
	cd $(TOOLCHAIN_SOURCE_PATH); git submodule update --init --recursive

checkout-spike:
	sudo apt-get install device-tree-compiler
	git clone https://github.com/riscv/riscv-isa-sim.git $(SPIKE_SOURCE_PATH)
	cd $(SPIKE_SOURCE_PATH); git checkout --detach $(SPIKE_COMMIT_ID)

checkout-openocd:
	sudo apt-get install make libtool pkg-config autoconf automake texinfo
	git clone https://github.com/riscv/riscv-openocd.git $(OPENOCD_SOURCE_PATH)
	cd $(OPENOCD_SOURCE_PATH); git checkout --detach $(OPENOCD_COMMIT_ID)

checkout-elf2hex:
	git clone https://github.com/sifive/elf2hex.git $(ELF2HEX_SOURCE_PATH)
	cd $(ELF2HEX_SOURCE_PATH); git checkout --detach $(ELF2HEX_COMMIT_ID)

checkout-pk:
	git clone https://github.com/riscv/riscv-pk.git $(PK_SOURCE_PATH)
	cd $(PK_SOURCE_PATH); git checkout --detach $(PK_COMMIT_ID)
	
checkout-riscv-tests:
	git clone https://github.com/riscv/riscv-tests.git $(RISCV_TESTS_SOURCE_PATH)
	cd $(RISCV_TESTS_SOURCE_PATH); git checkout --detach $(RISCV_TESTS_COMMIT_ID)
	

###### Build GCC/GDB #####
build-riscv-gnu-toolchain: $(TOOLCHAIN_SOURCE_PATH)/configure
	cd $(TOOLCHAIN_SOURCE_PATH)/riscv-gcc/gcc/config/riscv; rm t-elf-multilib; ./multilib-generator $(BARE_METAL_MULTILIBS_GEN) > t-elf-multilib
	rm -rf $(TOOLCHAIN_BUILD_PATH)/$@
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(TOOLCHAIN_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --enable-multilib --with-cmodel=medany; make -j$$(nproc); make linux -j$$(nproc)

###### Build Spike #####
build-riscv-isa-sim: $(SPIKE_SOURCE_PATH)/configure
	rm -rf $(TOOLCHAIN_BUILD_PATH)/$@
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(SPIKE_SOURCE_PATH)/configure --enable-histogram --prefix=$(TOOLCHAIN_INSTALL_PATH); make install -j$$(nproc)

###### Build OpenOCD #####
build-riscv-openocd: $(OPENOCD_SOURCE_PATH)/configure
	cd $(OPENOCD_SOURCE_PATH); ./bootstrap
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(OPENOCD_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH); make install -j$$(nproc)

	#cd $(TOOLCHAIN_BUILD_PATH); $(OPENOCD_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --enable-ftdi; make install -j$$(nproc)

###### Build ELF2HEX #####
build-elf2hex: $(ELF2HEX_SOURCE_PATH)/configure
	export PATH=$(TOOLCHAIN_BUILD_PATH)/bin:$$PATH
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(ELF2HEX_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --target=riscv64-unknown-elf; make install -j$$(nproc)
		
###### Build PK #####
build-pk: $(PK_SOURCE_PATH)/configure
	export PATH=$(TOOLCHAIN_BUILD_PATH)/bin:$$PATH
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(PK_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH) --host=riscv64-unknown-elf; make install -j$$(nproc)

###### Build riscv-tests ####
build-riscv-tests: $(RISCV_TESTS_SOURCE_PATH)/configure
	rm -rf $(TOOLCHAIN_BUILD_PATH)/$@
	mkdir -p $(TOOLCHAIN_BUILD_PATH)/$@
	cd $(TOOLCHAIN_BUILD_PATH)/$@; $(RISCV_TESTS_SOURCE_PATH)/configure --prefix=$(TOOLCHAIN_INSTALL_PATH)/riscv64-unknown-elf -with-xlen=64; make install -j$$(nproc)

