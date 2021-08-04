# wh_sdk开发文档

本文档主要针对如何对`wh_sdk`中某些文件进行特定的修改，以适应特定的需求。关于`wh_sdk`的基本使用方法已经在文档[WH-SDK-User-Guide-Release](https://github.com/UCTECHIP/wh_sdk/blob/master/doc/WH-SDK-User-Guide-Release.md)中给出，此处不再叙述。

## 1. wh_sdk的PLATFORM参数	

为了更具通用性，`WH-SDK`定义了一个`PLATFORM`参数，具体可选的参数有：`BOARD`（默认选项，生成的程序可以用于上板）、`SPIKE`（生成的程序可以用于`SPIKE`仿真）、`VCS`（生成的程序可以用于`VCS`仿真），这三者的不同之处在于`putchar`的实现，具体文件在`wh_bsp/env/LS_Board/LS_Startup/putchar.c`，为了配合`VCS`仿真，需要在仿真环境中监听`DCache`的总线行为，从而模拟出相应的串口行为。`script`目录下给出一个简单的`printf_monitor.v`模块实现。

## 2. wh_bsp目录结构

`wh_sdk`的整体目录已经在文档[WH-SDK-User-Guide-Release](https://github.com/UCTECHIP/wh_sdk/blob/master/doc/WH-SDK-User-Guide-Release.md)中列出，此处不再叙述，下面列一下`wh_bsp`目录：

```
* wh_bsp/            
  * env/          
        * LS_Board/  
     		* LS_Startup/				// 存放启动文件以及下载器的OpenOCD配置文件
     			* init.c					// 用于上电后初始化串口
     			* putchar.c					// putchar函数的实现
     			* jlink.cfg					// Jlink下载器的OpenOCD配置文件
     			* Olimex.cfg 				// Olimex下载器的OpenOCD配置文件
     			* openocd.cfg				// FT2232下载器的OpenOCD配置文件
     			* spike.cfg					// spike仿真器的OpenOCD配置文件
     		* Makefile					// Makefile构建文件
     		* WH64_DDR/
     			* setting.mk
     		* WH32_DDR/
     			* setting.mk
     		* spike64/
     			* setting.mk
  		* no_change/ 
  			* setting.mk         			// 配置文件模板
            * dcache.lds         			// DCache的链接脚本模板
            * dhrystone.lds      			// Dhrystone的链接脚本模板
            * flash.lds 					// 使用flash的链接脚本模板
            * mmu.h							// mmu模板
            * start.S            			// WH启动文件模板
            * trap_entry.S       			// 中断函数入口模板
  * include/     						// 所有内核、外设头文件
  		* core/								// 内核头文件
  		* device/							// 外设头文件
  		* bits.h
  		* const.h
  		* platform.h
  		* sections.h
  		* smp.h
  		* xcustom.h
  * libwrap/     						// 移植了一些Newlib的函数库
  		* misc/
  		* stdlib/
  		* sys/
  		* libwrap.mk
  * wh_lib/     
  		* core/							// 内核源文件
  		* device/						// 外设源文件
  		* wh_lib.mk 		
```

`wh_bsp`大概分为四个部分：

- 引导代码（存放在`env`中）

  为了适应不同配置的处理器实现，`wh_sdk`创建了一个`setting.mk`文件，用户直接修改`setting.mk`文件就可以对整个`wh_sdk`环境进行修改。

  >[WH-SDK-User-Guide-Release](https://github.com/UCTECHIP/wh_sdk/blob/master/doc/WH-SDK-User-Guide-Release.md)文档中有介绍如何修改`settting.mk`文件；
  >
  >`WH32_DDR`、`WH64_DDR`目录下,除了`setting.mk`文件外，其他的文件都是临时文件，在每次编译之前都会被重新生成；

- 内核和外设的头文件（存放在`include`中）

- `Newlib`函数的移植（存放在`libwrap`中）

- 内核和外设的源代码

## 3. no_change目录的作用

前面说到，每种不同的电路实现，对应的配置可能都不一样，主要的不同之处为：

- 支持的指令集不同

- 存储的起始地址和大小不同

- 可能使用`DTIM`或者`DCahce`

- 时钟频率不同

- `PLIC`基址不同

- `CLINT`基址不同

- 外设基址不同

- 中断数量不同

- 核的数量不同

- 可能支持`CEII`

- `VPU`的电路配置不同（这个选项作为一个参数传递给`SPIKE`）

- `MTIME`计数器的频率不同

为了让`wh_sdk`支持不同的配置，需要重新生成`no_change`目录中的文件，并且将文件复制到对应的位置。

> 如果用户想要修改 `dcache.lds/dhrystone.lds/flash.lds/mmu.h/start.S/trap_entry.S `这些文件，那么应该直接修改`no_change`目录下的文件，而不是修改 `WH32_DDR`、`WH64_DDR`目录

## 4. make_env_var文件的作用

```
$ cat make_env_var
#### user change ####
BOARD ?= LS_Board
RELEASE ?= spike64
SOFTWARE ?= software
PROGRAM ?= coremark
HOST_IP := 192.168.168.110

#### no change ####
LINK_TARGET ?= link
SDK_ROOT := $(abspath .)
BSP_BASE := $(abspath wh_bsp)
BOARD_DIR := $(abspath $(BSP_BASE)/env/$(BOARD))
RELEASE_DIR := $(BOARD_DIR)/$(RELEASE)
PROGRAM_DIR = $(abspath $(SOFTWARE)/$(PROGRAM))
OUTPUT_DIR = $(abspath output)
SCRIPT_DIR = $(abspath script)
WH_LIB = $(abspath wh_bsp/wh_lib)
INCLUDE_DIR = $(abspath wh_bsp/include)
SOFTWARE_DIR = $(abspath $(SOFTWARE))
RELEASE_STARTUP_DIR = $(abspath $(RELEASE_DIR)/startup)
BOARD_STARTUP_DIR := $(BOARD_DIR)/LS_Startup
BUILD_DIR := $(RELEASE_DIR)/build 
```

`make_env_var`文件定义了一些重要的`Makefile`参数，`BOARD`用于指定开发板型号，`wh_sdk`目前只有一个开发板`LS_Board`，`RELEASE`用于指定`setting.mk`文件的目录位置，`SOFTWARE`用于指定程序的目录位置，`PROGRAM`用于指定需要编译的程序，`HOST_IP`用于烧写程序时，给`GDB`传递的`IP`参数，其他参数则是衍生出来的变量。

### 4.1 程序烧录

结合`GDB`+`OpenOCD`，既可以实现同机的程序烧录，也可以实现异机的程序烧录，同机指的是`GDB`和`OpenOCD`都在同一台主机上运行，这种情况下，需要把`HOST_IP`修改成`HOST_IP := localhost`，如果是异机烧录，则需要将`HOST_IP`修改成`OpenOCD`所在主机的`IP`地址，例如把`HOST_IP`修改成`HOST_IP := 192.168.168.110`，需要注意的是，异机烧录要求两台主机接入同一个局域网内。

## 5. 为wh_sdk增加驱动程序

下面以为`wh_sdk`增加`I2C`驱动程序为例，说明整个修改流程。假设已有文件`i2c.c`和`i2c.h`：

### 5.1 将头文件复制到对应目录下

由于`i2c`属于外设，所以应该将`i2c.h`文件复制到`wh_bsp/include/device`目录下

### 5.2 包含新增的头文件

在`wh_bsp/include/device/device.h`文件中增加部分代码：

```
...
#include "device/gpio.h"
#include "device/i2c.h"				//需要增加的代码
#include "device/uart.h"
#include "device/spi.h"
#include "device/etimer.h"
#include "device/can.h"
...
```

### 5.3 将源文件复制到对应目录下

由于`i2c`属于外设，所以应该将`i2c.c`文件复制到`wh_bsp/wh_lib/device`目录下

## A 附录：

#### A.1 DCache使能位

某些电路版本会存在`DCache`使能的特性，在默认情况下`DCache`是关闭的，为了开启`DCache`，需要将`CSR`寄存器`mstatus`的`DD`比特置1，对于不同的电路版本，`mstatus.DD`可能是第25位，也可能是第23位，**具体需要看电路实现，这个可以查看`CSRFile.v`文件中`mstatus`寄存器是怎么实现的**。对于具有`DCache`使能特性的电路版本，大概需要如下五个修改步骤：

（1）根据电路实现，确定`DD`比特在`mstatus`寄存器的位置；

（2）根据电路实现，修改`wh_bsp/include/csr.h`文件中 的`MSTATUS_DD`宏定义；

（3）修改`wh_bsp/env/no_change/start.S`文件；启动文件把`DCache`使能的代码片段注释掉了，所以需要手动把注释去掉：

```
$ cat start.S
......
//#ifdef ON_BOARD
//#if defined(ENABLE_DCACHE)
//        li a0, MSTATUS_DD
//        csrrc x0, mstatus, a0
//#else
//        li a0, MSTATUS_DD
//        csrs mstatus, a0
//#endif
//#endif
......
```

（4）修改`setting.mk`文件（具体哪个`setting.mk`需要看`make_env_var`文件中的`RELEASE`变量是怎么定义的），将`DCACHE_EN`置1；

```
cat setting.mk
...
DCACHE_EN  := 1
...
```

（5）先执行`make dist-clean`，然后重新编译即可
