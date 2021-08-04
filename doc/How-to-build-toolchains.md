# 工具构建说明

## 1. 构建环境

本文档使用的构建环境为`Ubuntu 16.04`，所以建议用户也使用`Ubuntu 16.04`作为安装环境。

## 2. RISC-V GNU工具链编译

### 2.1 需要预先安装的依赖库

```
$ sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
```

### 2.2 获取工具链源码

```
$ git clone https://github.com/UCTECHIP/riscv-gnu-toolchain.git
$ cd riscv-gnu-toolchain
$ git checkout uctechip
$ git submodule update --init --recursive
```

### 2.3 获取工具链patch

```
$ cd riscv-gnu-toolchain
$ git clone https://github.com/UCTECHIP/patch-for-riscv-gnu-toolchain.git
```

### 2.4 打上patch

```
$ cd riscv-gnu-toolchain/riscv-gcc
$ git apply patch-for-riscv-gcc/*.patch
```

```
$ cd riscv-gnu-toolchain/riscv-binutils
$ git apply patch-for-riscv-binutils-gdb/*.patch
```

### 2.5 构建说明

**注意：`prefix`指向的是工具链需要安装的路径，默认的安装路径是`/opt/riscv`，如果需要指定其他安装路径，直接修改`prefix`即可**

#### 2.5.1 构建使用Newlib函数库的工具链

如果想要构建使用`Newlib`函数库的工具链，请执行如下步骤：

```
$ cd riscv-gnu-toolchain
$ mkdir build && cd build
$ ../configure --prefix=/opt/riscv --enable-multilib
$ make
$ make install
```

`--enable-multilib`指的是同时构建RV32和RV64的函数库，默认构建组合有：

`march=rv32i/mabi=ilp32`
`march=rv32im/mabi=ilp32` 
`march=rv32iac/mabi=ilp32` 
`march=rv32imac/mabi=ilp32` 
`march=rv32imafc/mabi=ilp32f` 
`march=rv64imac/mabi=lp64` 
`march=rv64imafdc/mabi=lp64d`

如果默认的构建组合里面没有你想要的组合，例如你需要配置`rv64imafdcv`指令的工具链，那么可以这样配置：

`../configure --prefix=/opt/riscv --with-arch=rv64imafdcv --with-abi=lp64d`

#### 2.5.2 构建使用Glibc函数库的工具链

虽然`Glibc`函数库也可以使用`--enable-multilib`选项构建支持多种不同指令集组合，但是不建议这样使用，我们推荐直接使用`--with-arch`和`--with-abi`选项构建对应的工具链，如果想要构建使用`rv32gc`的`Glibc`函数库的工具链，请执行如下步骤：

```
$ cd riscv-gnu-toolchain
$ mkdir build && cd build
$ ../configure --prefix=/opt/riscv --with-arch=rv32gc --with-abi=ilp32d
$ make linux
$ make install
```

如果想要构建使用`rv64gcv`的`Glibc`函数库的工具链，请执行如下步骤：

```
$ cd riscv-gnu-toolchain
$ mkdir build && cd build
$ ../configure --prefix=/opt/riscv --with-arch=rv64gcv --with-abi=lp64d
$ make linux 
$ make install
```

## 3. RISC-V OpenOCD编译

### 3.1 安装依赖库

```
$ sudo apt-get install make libtool pkg-config texinfo
```

### 3.2 下载源码

```
$ git clone https://github.com/UCTECHIP/riscv-openocd.git
```

### 3.3 构建说明

```
$ cd riscv-openocd
$ ./bootstrap
$ ./configure --prefix=/opt/riscv --enable-ftdi
$ make -j$(nproc)
$ make install
```

>如果想让`spike`与`gdb`联合调试，还需要增加参数 `--enable-remote-bitbang`

## 4. Spike和PK编译

`Spike`是一个RISC-V指令模拟器，它能够模拟实现一个或多个RISC-V硬件线程的功能模型，`pk`指的是RISC-V Proxy Kernel，即RISC-V的代理内核，用于给RISC-ELF提供执行环境。**`pk`的构建需要用到`riscv-gnu-toolchain`，所以在构建`pk`之前必须先构建`riscv-gnu-toolchain`。**

### 4.1 安装依赖库

```
$ sudo apt-get install device-tree-compile
```

### 4.2 下载源码

```
$ git clone https://github.com/UCTECHIP/riscv-isa-sim.git
```

```
$ git clone https://github.com/UCTECHIP/riscv-pk.git
```

### 4.3 构建说明

```
$ cd riscv-isa-sim 
$ git checkout uctechip
$ mkdir build 
$ cd build
$ ../configure --prefix=/opt/riscv --enable-histogram
$ make 
$ make install
```

```
$ cd riscv-pk
$ mkdir build 
$ cd build
$ ../configure --prefix=/opt/riscv --host=riscv64-unknown-elf
$ make 
$ make install
```

如果在编译`pk`时出现无法找到`riscv64-unknown-elf-gcc`，请将之前编译好的工具链路径加入到`PATH`环境变量中，例如`export PATH=/home/common/riscv-tools/install/tools-for-vector-insts/bin:$PATH`

## 5. ELF2HEX编译

`elf2hex`工具可以将ELF文件转成电路仿真中可以直接使用的HEX文件。**`elf2hex`的构建需要用到`riscv-gnu-toolchain`，所以在构建`elf2hex`之前必须先构建`riscv-gnu-toolchain`。**

### 5.1 下载源码

```
$ git clone https://github.com/UCTECHIP/elf2hex.git
```

### 5.2 构建说明

```
$ cd elf2hex
$ mkdir build
$ cd build
$ ../configure --prefix=/opt/riscv --target=riscv64-unknown-elf
$ make
$ make install
```

如果在编译`elf2hex`时出现无法找到`riscv64-unknown-elf-gcc`，请将之前编译好的工具链路径加入到`PATH`环境变量中，例如`export PATH=/home/common/riscv-tools/install/tools-for-vector-insts/bin:$PATH`

## 6. QEMU编译

`riscv-gnu-toolchain`目录中已经包含了`qemu`源码，所以在构建完成工具链的基础上直接构建`qemu`即可：

```
$ cd riscv-gnu-toolchain/build
$ make build-qemu
$ make install
```
