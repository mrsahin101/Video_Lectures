# A timeline for Embedded Linux

## Busy Box
- Busybox : A collection of command-line utilites
- Created by Bruce Perens so that he could put the debian installer on single 1.44MiB floppy disk

## The Linux Router Project(LRP)
- in 1997 Dave Cinege used busybox to create Linux distribution on floppy disk that turns a PC into a router
- in 1998 David Taht and Greg Retkowski publish the first embedded Linux wireless router

## Flash Memory
- David Woodhouse begins work on the Memory Technology Devices(MTD) layer
- Axis create a robust file system for camera. Called JFFS(Journal Flash File System)

- After wards handheld pcs and mobiles came along.

## Embedded Linux gets easier : 2001 and onwards
- Move away from RYO(Roll Your Own) embedded Linux Distributions
    1. BuildRoot
    2. OpenEmbedded
    3. Poky
    4. Yocto

## Real-time : 1998 to present
- Early versions of Linux were not very good at real-time. 2006 PREEMPT_RT is appeared.
- FSM Labs paatented techniques used in both RTLinux and RTAI : Basically they implement real-time scheduler, and when scheduler runs idle task, they run linux in idlee task.
- Billions of devices running Embedded Linux. 