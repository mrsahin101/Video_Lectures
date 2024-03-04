# ISLETIM SISTEMLERINE GIRIS
- Operating System : A program that acts as an intermediary between a user of a computer and computer hardware. Goals are :
    1. Execute user programs and make solving user problems easier.
    2. Make the computer system convenient to use
    3. Use the computer hardware in an efficent manner.
- Computer Systems can be divided into four components
    1. Hardware
    2. Operating System
    3. Application Programs
    4. Users

- Birincil Hafiza : RAM, Ikincil Hafiza : Diskler

![file permissions](./Images/OS_Layers.PNG)

- What operating System do? 
    1. Ease of use, User don't care about resource utilization
    2. Must keep all users happy for shared computers
    3. Workstations(Dedicated systems) have dedicated resources but frequently use shared resources such as **servers**
    4. Some computers have little or no UI.
    5. Handheld computers are resource poor, but optimized for usabilty and battery life.
    6. OS is resources allocator(Manages all resources)
    7. OS is control programs(Controls executing of programs)
    8. Prevents errors and improper use of the computer
    9. No universally accepted definition
    10. The one program running at all times on the computer is the **kernel**. Everything else is either a system program or an application program.

- Bootstrap program is loaded at power-up or reboot.
    1. Typically stored in ROM or EEPROM generally known as firmware
    2. Initializes all aspects of system
    3. Loads operating system kernel and starts execution

- Computer System Operation
    1. I/O devices and the CPU can execute concurrently
    2. Each device controller is in charge of a particular device type
    3. Each device controller has a local buffer
    4. CPU moves data from/to main memory to/from local buffers
    5. I/O is from the device to local buffer of controller
    6. Device controller informs CPU that it has finished its operation by causing interrupt.

- Common Functions of Interrupts
    1. Interrupt transfer control to the interrupt service routine generally, through **interrupt vector**, which contains the addresses of all the service routines
    2. Interrupt architecture must save the address of the interrupted instruction
    3. Incoming interrupts are disabled while another interrupt is being processed to prevent a lost interrupt
    4. A trap is a software-generated interrupt caused either by an error or a user request
    5. An operating system is **interrupt driven**
- Interrupt Handling
    1. The operating system preserves the state of the CPU by storing registers and the program counter
    2. Determines which type of interrupt has occured
        1. Polling
        2. Vectored interrupt system
    3. Separate segments of code determine what action should be taken for each type of interrupt

## I/O Structure
- After I/O starts, control returns to user program only upon I/O completion
    1. Wait instruction idles the CPU until the next interrupt
    2. Wait loop(contention for memory access)
    3. At most one I/O request is outstanding at a time, no simultaneous I/O processing

- After I/O starts, control returns to user program without waiting for I/O completion
    1. **System call** : Request to the operating system allow user to wait for I/O completion
    2. **Device-status table** : Contains entry for each I/O device indicating its type, address, and state
    3. Operating system indexes into I/O device table to determine device status and to modify table entry to include interrupt

- Direct Memory Access Structure
    1. Used for high-speed I/O devices able to transmit information at **close to memory speeds**
    2. Device controlelr transfers blocks of data from buffer storage directly to main memory without CPU intervention
    3. Only one interrupt is generated per block, rather than the one interrupt per byte

- Storage Structure
    1. Main memory - only large storage media that the CPU can access directly
        1. Random Access
        2. Typically volatile
    2. Secondary storage - extension of main memory that provides large **nonvolatile** storage capacity
    3. Magnetic disks - rigid metal or glass platters covered with magnetic recording metarial
        1. Disk surface is logically divided into **tracks**, which are subdivided into **sectors**
        2. The **disk controller** determines the logical interaction between the device and the computer

- Storage systems organized in hierarchy
    1. Speed
    2. Cost
    3. Volatility
- Caching - copying information into faster storage system, main memory can be viewed as a **cache** for secondary storage
- Storage device hierarchy : Registers -> Cache -> Main Memory -> Electronic disk -> Magnetic Disk -> Optical Disk -> Magnetic tapes

### Caching
- Important principle, performed at many leves in a computer(Hardware, operating system, software)
- Information is use copied from slower to faster storage temporaily
- Faster storage()

video2 at 5.31