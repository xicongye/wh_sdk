# Spike使用教程

## 1. 下载、编译spike和pk

下载、编译步骤可以看文档[How-to-build-toolchains](https://github.com/UCTECHIP/wh_sdk/blob/master/doc/How-to-build-toolchains.pdf)，这里不再赘述。

## 2. 使用spike+pk跑helloworld

`pk`是用于连接`spike`和宿主机的中间层，内部已经实现了一些`syscall`接口，可以执行静态链接的用户程序。

```
$ cat hello.c
#include <stdio.h>
int main(void)
{
   printf("Hello World!\n");
   return 0;
}
$ riscv64-unknown-elf-gcc hello.c -o hello
$ spike pk hello
bbl load
Hello World!
```

在运行上述命令之前，请确保已经把工具链路径加入到`PATH`环境变量中。

## 3. spike单步调试

`spike`内部实现了单步调试功能

```
$ spike -d pk hello		# 进入调试模式
$ : reg 0 a0 			# 查看core0的a0寄存器
$ : fregs 0 ft0 		# 查看core0的ft0寄存器
$ : mem 2020 			# 查看物理内存地址0x2020的数据
$ : mem 0 2020 			# 查看core0的虚拟内存地址0x2020的数据
$ : until pc 0 2020 	# 当PC=0x2020时停止执行
$ : until mem 2020 50a9907311096993 # 当mem[0x2020]=50a9907311096993时停止执行
```

## 4. 结合wh_sdk利用spike跑coremark

修改`make_env_var`文件：

```
$ cd wh_sdk
$ cat make_env_var
...
PROGRAM ?= coremark
...
```

编译、运行：

```
$ cd wh_sdk
$ make clean && make software PLATFORM=SPIKE && make run_sim
spike --isa=rv64imafdc --varch=vlen:128,elen:64,slen:128 -m0x40000000:0x50000000  software/coremark/coremark.elf
CoreMark Start...
2K performance run parameters for coremark.
CoreMark Size    : 666
Total ticks      : 29382600
Total time (secs): 18.805
Iterations/Sec   : 159.533
Iterations       : 3000
Compiler version : GCC10.1.0
Compiler flags   : -O2 
Memory location  : STACK
seedcrc          : 0xe9f5
[0]crclist       : 0xe714
[0]crcmatrix     : 0x1fd7
[0]crcstate      : 0x8e3a
[0]crcfinal      : 0xcc42
Correct operation validated. See readme.txt for run and reporting rules.
CoreMark 1.0 : 159.533 / GCC10.1.0 -O2  / STACK


Score:  3.191 CoreMark/MHz
Program has exited with code:0x0000000000000000
```

如果你要用自己编译的`spike`，可以直接修改`wh_sdk`目录下的`Makefile`文件，文件内部有个`SPIKE`变量

## 5. GDB与spike联合调试

`GDB`与`spike`联合调试需要使用三个终端，它们的操作分别是：

**终端1：运行spike**

```
$ cd wh_sdk
$ make clean && make software PLATFORM=SPIKE && make run_spike
```

**终端2：运行OpenOCD**

```
$ cd wh_sdk
$ make run_openocd PLATFORM=SPIKE
```

**终端3：运行GDB**

```
$ cd wh_sdk
$ make run_gdb PLATFORM=SPIKE
```

## 6. 利用spike生成性能分析报告

我们为`spike`新增了性能分析功能，下面以`coremark`程序为例，说明如何使用该特性：

#### 6.1 在需要测试的代码段前后设置监听标志位

```
asm volatile("csrwi 0x8ff, 0x1");  		// 开始标志
for (i=0; i<iterations; i++) {
   crc=core_bench_list(res,1);
   res->crc=crcu16(crc,res->crc);
   crc=core_bench_list(res,-1);
   res->crc=crcu16(crc,res->crc);
   if (i==0) res->crclist=res->crc;
} 
asm volatile("csrwi 0x8ff, 0x0"); 		// 结束标志
```

#### 6.2 修改_exit函数

为了让`spike`正常退出，需要修改`wh_bsp/libwrap/sys`目录下的`_exit.c`文件：

```
$ cd wh_sdk/wh_bsp/libwrap/sys
$ cat _exit.c
/* See LICENSE of license details. */

#include <unistd.h>
#include "platform.h"
extern void write_hex(int fd, unsigned long int hex);
extern volatile uint64_t tohost;   ////////////   修改这里 //////////////////
void __wrap__exit(int code)
{
  const char message[] = "\nProgram has exited with code:";

  write(STDERR_FILENO, message, sizeof(message) - 1); 
  write_hex(STDERR_FILENO, code);
  write(STDERR_FILENO, "\n", 1); 
  
#ifdef ON_SPIKE
  tohost = 1;      ////////////   修改这里 //////////////////
#endif
                         
  for (;;);
}
```

#### 6.3 重新编译程序

```
$ make software PLATFORM=SPIKE
```

#### 6.4 运行spike

```
$ make run_sim
```