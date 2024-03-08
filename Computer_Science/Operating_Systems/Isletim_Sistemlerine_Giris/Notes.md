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

## Caching
- Important principle, performed at many leves in a computer(Hardware, operating system, software)
- Information is use copied from slower to faster storage temporaily
- Faster storage(cache) checked first to determine if information is there
    1. If it is, information used directly from the cache
    2. If not, data copied to cache and used there
- Cache smaller than storage being cached
    1. Cache management important design problem
    2. Cache size and replacement policy

## Computer-System Architecture
- Most systems use a single general-purpose processor
    1. Most systems have special-purpose processors as well
- **Multiprocessors** systems growing in use and importance
    1. Also known as paralel system, **tightly-coupled systems**
    2. Advantages include
        1. Increased throughput
        2. Economy of scale
        3. Increased reliability -graceful degradation or fault tolerance
    3. Two types
        1. Asymmetric Multiprocessing
        2. Symmetric Multiprocessing

![Von Neuman Architecture](./Images/VonNeuman.PNG)

![Von Neuman Architecture](./Images/Symmetric.PNG)

## Clustered Systems
- Like multiprocessor systems, but multiple systems working together
    1. Usually sharing storage via **storage-area network(SAN)**
    2. Provides a **high-availabilty** service which survives failures
        1. **Asymmetric clustering** has one machine in hot-standby mode
        2. **Symmetric clustering** has multiple nodes running applications, monitoring each other
    3. Some clusters are for **high-performance computing(HPC)**
        1. Applications must be written to use **parallelization**

## Operating System Structure
- **Multi programming** needed for efficency
    1. Single user cannot keep CPU and I/O devices busy at all times
    2. Multiprogramming organizes jobs(code and  data) so CPU always has one to execute
    3. A subset of total jobs in system is kept in memory
    4. One job selected and run via **job scheduling**

- **Timesharing(Multi-tasking)** is logical extension in which CPU switches jobs so frequently that user can interact with each job while it is running, creating **interactive** computing
    1. **Response time** should be <1 second
    2. Each user has at least one program executing in memory -> **process**
    3. If several jobs ready to run at the same time -> **CPU scheduling**
    4. If processes don't fit in memory, **swapping** moves them in and out to run
    5. **Virtual memory** allows execution of processes not completely in memory

## Operating-System Operations
- Interrupt driven by hardware
- Software error or request creates **exceptions** or **trap**
    1. Divison by zero, request for operating system service
- Other process problems include infinite loop, processes modifying each other or the operating system
- **Dual-mode** operation allows OS to protect itself and other system components
    1. **User mode** and **kernel mode**
    2. **Mode bit** provided by hardware
        1. Provides ability to distinguish when system is running user code or kernel code
        2. Some instructions designated as **privileged**, only executable in kernel mode
        3. System call changes mode to kernel, return from call resets it to user

- Timer to prevent innfinite loop / process hogging resources
    1. Set interrupt after specific period
    2. Operating system decrements counter
    3. When counter zero generate an interrupt
    4. Set up before scheduling process to regain control or terminate program that exceeds allotted time

![Von Neuman Architecture](./Images/Transition.PNG)

## Process Management
- A process is a program in execution. It is a unit of work within the system. Program is a passive entity, process is an active entity
- Process needs resources to accomplish its task
    1. CPU, memory, I/O, files
    2. Initialization data
- Process termination requires reclaim of any reusable resources
- Single-threaded process has one program counter specifying location of next instruction to execute
    1. Process executes intructions sequentially, one at a time, until completion
- Multi-threaded process has one program counter per thread.
- Typically system has many processes, some user, some operating system running concurrently on one or more CPUs
    1. Concurrency by multiplexing the CPUs among the processes / threads

### Activities
- The operating system is responsible for the following activities in connection with process management
    1. Creating and deleting both user and system processes
    2. Suspending and resuming processes
    3. Providing mechanisms for process synchronization
    4. Providing mechanisms for process communication
    5. Prodiving mechanisms for deadlock handling.

## Memory Management
- All data in memory before and after processing
- All instructions in memory in order to execute
- Memory management determines what is in memory when
    1. Optimizing CPU utilization and computer response to users
- Memory management activities
    1. Keeping track of which parts of memory are currently being used and by whom
    2. Deciding which processes(or parts thereof)and data to move into and out of memory
    3. Allocating and deallocating memory space as needed      

## Storage Management
- OS provides uniform, logical view of information storage
    1. Abstracts physical properties to logical storage unit - file
    2. Each medium is controlled by device(disk drive, tape drive)
- File-system management
    1. Files usually organized into directories
    2. Access control on most systems to determine who can access what
    3. OS activities include 
        1. Creating and deleting files and directories
        2. Primitives to manipulate files and dirs
        3. Mapping files onto secondary storage
        4. Backup files onto stable(non-volatile) storage media

## Mass-Storage MAnagement
- Usually disks used to store data that does not fit in main memory or data that must be kept for a "long" period of time
- Proper management is of central importance
- Entire speed of computer operation hinges on disk subsystem and its algorithms
- OS activities
    1. Free-space management
    2. Sotrage allocation
    3. Disk scheduling

- Some storage need not to be fast
    1. Tertiary storage includes optical storage, magnetic tape
    2. Still must be managed - by OS or application
    3. Varies between WORM(write-once, read-many-times) and RW(read-write)

## I/O Subsystem
- One purpose of OS is to hide peculiarities of hardware devices from the user
- I/O subsystem responsible for
    1. Memory management of I/O including buffering(storing data temporarily while it is being transferred), caching(storing parts of data in faster storage for performance), spooling(the overlapping of output of one job with input of other jobs)
    2. General device-driver interface
    3. Drivers for specific hardware devices

## Protection and Security
- **Protection** : Any mechanism for controlling access of processes or users to resources defined by the OS
- **Security** : Defense of the system against internal and external attacks
    1. Huge range, including denial-of-service, worms, viruses, identity, theft, theft of service
- Systems generally first distinguish among users, to determine who can do what
    1. User identities(user IDS, security IDs)include name and associated number, one per user
    2. User ID then associated with all files, processes of that user to determine access control
    3. Group identifier(**group ID**) allows set of users to be defined and controls manage, then also associated with each process, file
    4. **Privilege escalation** allows user to change to effective ID with more rights

## Special-Purpose Systems
- Real-time embedded systems most prevalent form of computers
    1. Vary considerable, special purpose, limited purpose OS, **Real-time OS**
- Multimedia systems
    1. Streams of data must be delivered according to time restrictions
- Handheld systems
    1. PDAs, smart phones, limited CPU, memory, power
    2. Reduced feature set OS, limited I/O

# Operating-System Structures

## Operating System Services
- Operating systems provide an enviroment for execution of programs and services to programs and users
- One set of operating-system services provides functions that are helpful to the user
    1. **User Interface(UI)** : Varies between Command-Line(CLI), Graphics User Interface(GUI), Batch
    2. **Program execution** : The system must be able to load a program into memory and to run that program, end execution, either normally or abnormally
    3. **I/O operations** : A running program may require I/O, which may involve a file or an I/O device
    4. **File-System manipulation** : The file system is of particular interest. Programs need to read and write files and directories, create and delete them, search them, list file information, permission management
    5. **Communications** : Process may exchange information, on the same computer or between computers over a network
    6. **Error Detection** : OS needs to be constantly aware of possible erros
    7. **Resource Allocation** : When multiple users or multiple jobs running concurrently, resources must be allocated to each of them
    8. **Accounting** : To keep track of which users use how much and what kinds of computer resources
    9. **Protection and security** : The owners of information stored in a multiuser or networked computer system may want to control use of that information, concurrent processes should not interfere with each other

![Von Neuman Architecture](./Images/OS_overview.PNG)

- To access hardware, User applications should do via Operating system. There is no other way possible generally.

- CLI or **command interpreter** allows direct command entry
    1. Sometimes implemented in kernel, sometimes by systems program
    2. Sometimes multiple floavors implemented - **shells**
    3. Primarily fetches a command from user and executes it
    4. Sometimes commands built-in, sometimes just names of programs

- User friendly **desktop** metaphor interface
    1. Usually mouse, keyboard and monitor
    2. **Icons** represent files, programs, actions, etc
    3. Various mouse buttons over objects in the interface cause various actions
    4. Invented at Xerox PARC
- Many systems now include both CLI and GUI interfaces
- Touchscreen devices require new interfaces.

## System Calls
- Programming interface to the services provided by the OS
- Typically written in a high-level language(C or C++)
- Mostly accessed by programs via a high-level **Application Programming Interface(API)** rather than direct system call use
- Three most common APIs are Win32 API, POSIX API for POSIX Based Systems(UNIX, Linux, Mac OS X) and Java API for JVM

![Von Neuman Architecture](./Images/API.PNG)
- Often, more information is required than simply identity of desired system call
    1. Exact type and amount of information vary according to OS and call
- Three general methods used to pass parameters to the OS
    1. Simplest : Pass the parameters in Registers
    2. Parameters stored in block, or table in memory and address of block passed as a parameter in a register
    3. Parameter placed or pushed, onto the stack by the program and popped off the stack by the operating system
    4. Block and stack methods do not limit the number or length of parameters being passed

## Types of System Calls
- Process Control
    1. Create process, terminate process
    2. end, abort
    3. load, execute
    4. Get process attributes, set process attributes
    5. Wait for time
    6. Wait Event, signal event
    7. Allocate and free memory
    8. Dump memory if error
    9. **Debugger** for determining **bugs**, **single step** execution
    10. **Locks** for managing access to shared data between processes
- File management
    1. Create file, delete file
    2. Open, close file
    3. Read, write, reposition
    4. Get and set file attributes
- Device management
    1. Request device, release device
    2. Read, write, reposition
    3. Get device attributes, set device attributes
    4. Logically attach or detach devices
- Information maintenance
    1. Get time or date, set time or date
    2. get system data, set system data
    3. Get and set process, file or device attributes
- Communications
    1. Create, delete communication connection
    2. Send, receive messages if **message passing model** to **hostname** or **process name**
    3. **Shared-memory model** create and gain access to memory regions
    4. Transfer status information
    5. Attach and detach remote devices
- Protection
    1. Control access to resources
    2. Get and set permissions
    3. Allow and deny user access

## System Programs
- System programs provide a convenient environment for program development and execution. 
    1. File manipulation
    2. Status information sometimes stored in a File modification
    3. Programming language support
    4. Program loading and execution
    5. Communications
    6. Background services
    7. Application programs
- Most users view of the operating system is defined by system programs, not the actual system calls.
- Provide a convenient enviroment for program development and execution
- **File management** : Create, delete, copy, rename, print, dump, and generally manipulate files and directories
- **Status information** : Some ask the system for info-date, time, amount of available memory, disk space, number of users
- **File modifications** : Text editors to create and modify files
- **Programming-language support** : Compilers, assemblers, debuggers, interpreters
- **Program loading and execution** : Absolute loaders, relocatable loaders, linkage editors and overlay loaders
- **Communications** : Provide the mechanism for creating virtual connections among processes, users, and computer systems

![Kernel](./Images/Kernel.PNG)

# Processes

## Process Concept
- An operating system executes a variety of programs
    1. Batch system - **jobs**
    2. Time-shared systems - **user programs** or **tasks**
- Textbook uses the term **job** and **process** almost interchangeably
- **Process** a program in execution process execution must progress in sequential fashion
- Multiple parts
    1. The program code, also called **text section**
    2. Current activity including **program counter**, processor register
    3. **Stack** containing temporary data
    4. **Data section** containing global variabes
    5. **Heap** containing memory dynamically allocated during run time
- Program is **passive** entity stored on disk process(**executable file**) is **active**
    1. Program becomes process when executable file loaded into memory
- Execution of program started via GUI mouse clicks, command line entry of its name
- One program can be several processes
    1. Consider multiple user executing the same program

## Process States
- As a process executes, it changes **state**
    1. **new** : The process is being created
    2. **running** : Instructions are being executed
    3. **waiting** : The process is waiting for some event to occur
    4. **ready** : The process is waiting to be assigned to a processor
    5. **terminated** : The process has finished execution

## Process Control Block(PCB)
- Information associated with each process(also called **task control block**)
- Process state, running, waiting, etc
- Program counter - location of instruction to next execute
- CPU registers - contents of all process-centric register
- CPU scheduling information - priorities, scheduling queue pointers
- Memory-management information memory allocated to the process
- Accounting information - CPU used, clock time elapsed since start, time limits
- I/O status information - I/O devices allocated to process, list of open files.

![Kernel](./Images/CONTEXT_SWITCH.PNG)

## Threads
- So far, process has a single thread of execution
- Consider having multiple program counters per process
    1. Multiple locations can execute at once
- Must then have storage for thread details multiple program counters in PCB

## Process Scheduling
- Maximize CPU use, quickly switch processes onto CPU for time sharing
- **Process scheduler** selects among available processes for next execution on CPU
- Maintains scheduling **queues** of processes
    1. **Job queue** - set of all processes in the system
    2. **Ready queue** : Set of all processes residing in main memory, ready and waiting to execute
    3. **Device queues** : Set of processes waiting for an I/O device 
    4. Processes migrate among the various queues

## Schedulers
- **Short-term scheduler** or (**CPU Scheduler**) - selects which process should be executed next and allocates CPU
    1. Sometimes the only scheduler is a system
    2. Short-term scheduler is invoked frequently(millisecond)
- **Long-term scheduler** or (job scheduler) selects which process should be brought into the ready queue
    1. Long-term scheduler invoked infrequently(seconds, minutes)
    2. The long-term scheduler controls the **degree of multiprogramming**
- Processes can be described as either
    1. **I/O-bound process** : Spends more time doing I/O than computations, many short CPU bursts
    2. **CPU-bound process** : Spends more time doing computations, few very long CPU bursts
- Long-term scheduler strives for good **process mix**

## Context Switch
- When CPU switches to another process, the system must **save the state** of the old process and load the **saved state** for the new process via a **context switch**
- **Context** of process represented in the PCB
- Context-switch time is overhead, the system does no useful work while switching
    1. The more complex the OS and the PCB, the longer the context switch
- Time dependent on hardware support
    1. Some hardware provides multiple sets of registers per CPU

## Process Creation
- **Parent** process create **children** processes, which, in turn create other processes, forming a **tree** of processes
- Generally, process identified and manage via a **process identifier(pid)**
- Resource sharing options
    1. Parent and children share all resources
    2. Children share subset of parents resources
    3. Parent and child share no resources
- Execution options
    1. Parent and children execute concurrently
    2. Parent waits until children terminate
- Address space
    1. Child duplicate of parent
    2. Child has a program loaded into it
- Unix examples 
    1. fork() system call creates new process
    2. exec() system call used after a fork() to replace the process memory space with a new program

## Process Termination
- Process executes last statement and then asks the operating system to delete it using the **exit()** system call.
    1. Returns status data from child to parent(via wait())
    2. Process resources are deallocated by operating system
- Parent may terminate the execution of children processes using the **abort()** system call. Some reasons for doing so
    1. Child has exceeded allocated resources
    2. Task assigned to child is no longer required
    3. The parent is existing and the operating system does not allow a child to continue if its parent terminates
- Some operating systems do not allow child to exists if its parent has terminated. If a process terminates, then all its children must also be terminated.
    1. Cascading termination. All children, grandchildren are terminated
    2. The termination is initiated by the operating system
- The parent process may wait for termination of a child process by using the **wait()** system call. The call returns status information and the pid of the terminated process.
- If no parent waiting(didnt invoke wait()) process is a **zombie**
- If parent terminated without invoking **wait()**, process is an **orphan**

# Threads

## Multicore Programming 
- **Multicore** or **Multiprocessor** systems putting pressure on programmers, challenges include
    1. **Dividing activities**
    2. **Balance**
    3. **Data splitting**
    4. **Data dependency**
    5. **Testing and debugging**
- **Parallelism** implies a system can perform more than one task simultaneously
- **Concurrency** supports more than one task making progress
- Types of parallelism
    1. **Data parallelism** : Distrubtes subsets of the same data across multiple cores, some operation on each
    2. **Task parallelism** : Distributing threads across cores, each thread performing unique opeartion
- As # of threads grows, so does architectural support for threading
    1. CPUs have cores as well as **hardware threads**

![Concurrent](./Images/CONCURRENT.PNG)
![Threads](./Images/Threads.PNG)

## User Threads and Kernel Threads
- **User Threads** - management done by user-level threads library
- Three primary threads libraries
    1. POSIX Pthreads
    2. Windows Threads
    3. Java Threads

- **Kernel Threads** - Supporte by the kernel
- Examples - virtually all general purpose operating systems, including
    1. Windows
    2. Solaris
    3. Linux
    4. Tru64 UNIX
    5. Mac OS X

## Multi-Threading Models
- **Many-to-One** : Many user-level threads mapped to single kernel thread. One thread blocking causes all to block.
- **One-to-One** : Each user-level thread maps to kernel thread. Creating user-level thread creates kernel thread. More concurrency than many-to-one
- **Many-to-Many** : Allow many user level threads to be mapped to many kernel threads. Allows the operating system to create a sufficent number of kernel threads.

## Two-Level Model
- Similiar to many-to many except that allows a user thread to be **bound** to kernel thread

# Process Synchronization
- **Race Condition** : When one or more process runs at same time, Doesnt guarantee who will run first.

## Critical Section Problem
- Consider System of **n** processes{p0, p1, p2, pn-1}
- Each process has **critical section** segment of code
    1. Process may be changing common variables, updating table, writing file
    2. When one process in critical section, no other may be in critical section
- **Critical section problem** is to design protocol to solve this
- Each process must ask permission to enter critical section in **entry section**, may follow critical section with **exit section** then **remainder section**

## Solution to Critical-Section Problem
- **Mutual Exclusion** : If process Pi is executing in its critical section, then no other processes can be executing in their critical sections
- **Progress** : If no process is executing in its critical section there exist some processes that wish to enter their critical section, then the selection of the processes that will enter the critical section next cannot be postponed indefinetly
- **Bounded Waiting** : A bound must exist on the number of times that other processes are allowed to enter their critical sections after a process has made a request to enter its critical section and before that request is granted.
    1. Assume that each process executes at a nonzero speed
    2. No assumption concerning **relative speed** of the **n** processes

## Critical Section Handling
- Two approaches depending on if kernel is preemptive or non-preemptive
    1. **Preemptive** : Allow preemption of process when running in kernel mode
    2. **Non-Preemptive** : Runs until exits kernel mode, blocks, or voluntarily yields CPU

## Synchronization Hardware
- Many system provide hardware support for implementing critical section code
- All solutions below based on idea of **locking**
    1. Protecting critical regions via locks
- Uniprocessors - could disable interrupts
    1. Currently running code would execute without preemption
    2. Generally too inefficent on multiprocessor systems
        1. Operating systems using this not broadly scalable
- Modern machines provide special atomic hardware instructions
    1. Atomic = non-interruptable
    2. Either test memory word and set value
    3. Or swap contents of two memory words.

## Mutex Locks
- Previous solutions are complicated and generally inaccessible to application programmers
- OS designers build software tools to solve critical section problem
- Simplest is mutex lock
- Protect a critical section by first **acquire()** a lock then **release()** the lock
    1. Boolean variable indicating if lock is available or not
- Calls to **acquire()** and **release()** must be atomic
    1. Usually implemented via hardware atomic instructions
- But this solution requires busy **waiting**
    1. This lock therefore called a **spinlock**

## Semaphore
- Synchronization tool that provides more sophisticated ways process to synchronize their activities
- Can only be accessed via two indivisible(atomic) operations
    1. **wait()** and **signal()** : Originally called P() and V()

## Semaphore Usage
- **Counting Semaphore** : Integer value can range over an unrestricted domain
- **Binary Semaphore** : Integer value can range only between 0 and 1
    1. Same as a **mutex lock**
- Can solve various synchronization problems
- Can implement a counting semaphore as a binary semaphore

## Semaphore Implementation
- Must guarantee thaat no two processes can execute the **wait()** and **signal()** on the same semaphore at the same time.
- Thus, the implementation becomes the critical section problem where the **wait** and **signal** code are placed in the critical section
    1. Could now have **busy waiting** in critical section implementation
- Note that applications may spend lots of time in critical sections and therefore this is not a good solution

## Semaphore Implementation with no Busy Lock
- With each semaphore there is an associated waiting queue
- Each entry in a waiting queue has two data items
    1. Value(of type integer)
    2. Pointer to next record in the list
- Two operations
    1. **Block** : Place the process invoking the operating on the appropriate waiting queue
    2. **wakeup** : Remove one of processes in the waiting queue and place it in the ready queue.

## Deadlock and Starvation
- **Deadlock** : Two or more processes are waiting indefinetly for event that can be caused by only one of the waiting processes
- **Starvation - indefinite blocking** : A process may never be removed from the semaphore queue in which it is suspended
- **Priority Inversion** : Scheduling problem when lower priority process holds a lock needed by higher-priority process
    1. Solved via **priority-inheritance protocol**

## Monitors
- A high-level abstraction that provides a convenient and effective mechanism for process synchronization
- Abstract data type, internal variables only accessible by code within procedure
- Only one process may be active within the monitor at a time
- But not powerful enough to model some synchronization schemes

# CPU Scheduling
Didnt start video