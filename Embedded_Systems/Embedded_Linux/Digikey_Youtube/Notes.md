# INTRODUCTION TO EMBEDDED LINUX
- Linux is so popular for IOT Devices.

- Comparision
    1. **Bare-Metal Programming** : Little or no software overhead, Low power requirment, High control of hardware, Single purpose, simple application, hardware-dependent, strict timing
    2. **Real-time Opearting System(RTOS)** : Scheduler overhead, More powerfull microcontroller, High control of hardware, MultiThreading, Some common libraries, Multiple Tasks, networking, user interface.
    3. **Embedded General Purpose Operating System(GPOS)** : Large overhead(scheduler, memory management, background tasks), Microprocessor usually required(and often External RAM and Non-Volatile RAM), Low direct control of hardware, Multiple threads and processes, many common libraries, Multiple complex tasks

- To tailor linux to our needs, we can build our own linux.
- To create own single board computer pcb it is difficult, and for each hardware we should create driver. So this is usually not preferable.
- Methods to work with single board computers
    1. Just use already created image. -> Easiest
    2. Manually write all files yourself. -> Extra hard mode
    3. Use tool to generate files -> Regular hard mode.
        1. Build Root -> Easy use, limited configuration
        2. Open-WRT -> Focused on networking
        3. Yocto Project -> Sleep learning cure, Customizable, Active Community.

- Usually we test develop binary files on host computer, then bring binaries on embedded board.
- Yocto project offical Linux foundation project for embedded system.
- **MetaData** : Files containing information about how to build an image
- **Recipe** : File with instructions to build one or more packages
- **Layer** : Directory containing grouped metadata
- **Board Support Package(BSP)** : Layer that defines how to build for board. Usually maintained by vendor.
- **Distribution** : specific implementattion of linux.
- **Machine** : defines the architecture, pins, buses, BSP.
- **Image** : output of build process.(Bootable and executable Linux OS)

![Register Model](.//Images/Yocto.PNG)
- We configure meta data. Build system install required packages for us and test it. Then build the image for us.

- poky is not yocto projet. It is reference distrobution.
- When working with yocto project, BSP and other packages should align with specific given yocto version. Otherwise it won't compile.
- OpenEmbedded is one of collaborators of yocto project.
- When we working with yocto project, we want to work with long term support packages.
- When we running build in yocto project, we can configure the image. We can say let it be minimal or with sdk, etc...

## Boot Process
- When microprocessor boots up, it boots in a few stages.
- For stm32mp1 -> first it executes rom code and looks for **First Stage BootLoader(FSL)**, **Second Stage Boot Loader(SSBL)** then it launches the kernel.
- Usually First Stage Bootloader is redundant
- SSBL is usually u-boot.

![Boot Stages](.//Images/Boot_Stages.PNG)
- When creating sdcard image, we must disect sd card into partition for given parts.
- The powerfull about Yocto project, we can create custom layers. Layers can be used to install packages, drivers etc.
- Device tree is used to enable what to be enabled when booting. Like devices, sensors, etc..
- Some low level stuff might not work well on Linux. Its rather prefered to add it into kernel to make it work properly. Because linux handles everything as file, using file structure sometimes is not practicable.
- You can take a look **Yocto Project Software Development Kit(SDK) Developers Guide**. or Check out vendor SDK.