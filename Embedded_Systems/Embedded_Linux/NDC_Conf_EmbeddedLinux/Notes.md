# FUNDAMENTALS OF EMBEDDED LINUX
- Linux is mostly running on Embedded Systems.

## What is Embedded Computing?
- No formal definition
- Characteristic Include
    1. Single Use
    2. Not end user programmable
    3. designed for price - so minimum hardware necessary
    4. Has power constraints.
    5. Has power dissipation constraints. E.g. No cooling fan

## What kind of Computer ?
- Microcontroller(MCU)
    1. small, low power, low performance
    2. CPU, RAM, flash storage all one one chip
- Microprocessor(MPU)
    1. CPU, RAM and storage and peripherals on separate cips
    2. High power, high performance, hight cost
    3. Mostly x86 architecture
- System on Chip(SOC)
    1. MPU with on-chip peripherals
    2. Mostly ARM architecture

- Single Board Computer(SBC) : Ready to go
- System on Module(SOM) : custom designed base board
- Custom Hardware : Board designed for specific purpose

## Why Embedded Linux ?
- **Moore Law** : Complex hardware requires complex software
- **Free** : you have the freedom to get and modify the code.
- **Functional** : Supports a very wide range of hardware
- **Up to date** : the kernel has a 10 week release cycle

## Minimum Hardware Specification
- 32 or 64-bit processor architecture with Memory Management unit(MMU), ARM, x86, RISC-V
- Atleast 16MB RAM
- Atleast 4MB storage.

## Pain Points
- Lack of support particular hardware
- The rapid update cycle does not fit well with slower cycle for embedded projects
- SOC/SOM/SBC vendors do not always push fixes and feautures as quickly as we would like

## Boards need Board Support Packages
- The Board Support Package(BSP) is everything you need to run Linux on a particular board
    1. **Bootloader**
    2. **Linux Kernel**
    3. **Kernel drivers specific to the board**
    4. **Device Tree** (ARM)
    5. **Libraries to support vendor-specific components such as accelerated graphics**
    6. **Boot scripts and run-time configuration files**
    7. **Firmware binaries for on-chip peripherals**

- Every embedded Linux project has these four elements
    1. **ToolChain** : To compile all the other elements
    2. **Bootloader** : To initialize the board and load the kernel
    3. **Kernel** : To manage system resources
    4. **Root filesystem** : To run applications

- Bootloader has 2 role 
    1. Initialize the board
    2. Load a Linux kernel

## Device Tree
- The kernel needs to know details about hardware.
    1. to decide which drivers to initialize
    2. to configure device parameters such as register addresses and IRQ
- Source of information.

## Root filesystem
- The user space part of the operating system
- System libraries
- Configuration files

## Embedded build systems
- This systems are automating building of embedded linux
- **Buildroot** -> Small, menu driven
- **OpenWrt** -> A variant of Buildroot for network devices
- **OpenEmbedded** -> General purpose
- **Yocto project** : General purpose, wide industry support, complex

### Yocto project : 
- Consist of :
    1. **oe-core** : shared with OpenEmbedded
    2. **BitBake** : shared with OpenEmbedded
    3. **Poky** : the distribution metadata
    4. **Toaster** : A graphical user interface for Yocto
    5. **Reference BSP** : Including Beaglebone
    6. **Documentation** : Which is extensive.

## Real-time
- Real time : Computation that must be completed before a deadline.
- Linux has different scheduling policies. 
    1. SCHED_NORMAL -> Completly Fair Scheduler. Tries to give each thread a fair share of CPU Time -> Non Real Time
    2. SCHED_FIFO -> Threads have static prioirties between 1 and 99 -> Real time

- Linux is source of non-determinism. Enabling kernel preemption is a big help
- CONFIG_PREEMPT -> Reduces jitter to milliseconds, Enabled on most embedded kernels
- PREEMPT_RT -> Reduces jitter to 10 s microseconds or less. Only just been integrated to mainlin Linux(after 10 years of effort)
- Package managers are not use in embedded world usually.