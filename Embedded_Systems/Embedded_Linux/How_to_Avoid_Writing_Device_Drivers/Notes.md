# How to Avoid Writing Device Drivers for Embedded Linux
- Info about device drivers and how to do it in User Space

- Conventional device driver model is kernel accessing hardware.
- In Linux, almost everything is a file
- Application interact with drivers via POSIX functions **open**, **read**, **write**, **ioctl**

## Userspace drivers
- Writing kernel device driver can be difficult
- It is time consuming to write kernel device drivers
- When bug introduced in kernel code are serious. 
- There are generic drivers that allow ou to write most of the code in userspace.
- There are two types of main interface
    1. Device nodes in **/dev**
    2. Driver attributes, exported via sysfs : For example **/sys/class/gpio**

- There are two userspace drivers
    1. **gpiolib** : old but scriptable interface using sysfs
    2. **gpio-cdev** : New, higher performance method using character device nodes /dev/gpiochip0*

## gpiolib interface
![SysFS](.//Images/sysfs.PNG)
![SysFS](.//Images/gpiochip.PNG)
![SysFS](.//Images/gpio_io.PNG)

- If the GPIO can generate interrupts, the file *edge** can be used to control interrupt handling.
- edge = ["none", "rising", "falling", "both"]
- From script we can poll for interrupt.

## gpio-cdev interface
- One device node per GPIO register named /dev/gpiochip*
- Access the GPIO pins using **ioctl(2)**
- This is more robust
- It has event mechanism, it tied to interrupt mechanism


![SysFS](.//Images/gpio-dev1.PNG)
![SysFS](.//Images/gpio-dev2.PNG)

- Used defined I/O : UIO
    1. Generic kernel driver that allows you to write userspace drivers
    2. Access device registers and handle interrupts from userspace

- User-space drivers are not always the best solution
    1. User-space programs can be killedd; kernel drivers cant
    2. Kernel drivers can use advanced locking techniques - spinlocks, rwlocks, rcu, etc
    3. Kernel drivers have direct access to DMA channels and interrupts
    4. A kernel driver can fit in to a subsystem

