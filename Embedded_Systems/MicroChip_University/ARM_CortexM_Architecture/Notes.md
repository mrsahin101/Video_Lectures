# ARM Cortex-M Architecture Overview

## Introduction
- ISA : Instruction Set Architecture
- Arm has 3 architecture profile in Cortex Family. Cortex-A -> Application, Cortex-R -> Real-time, Cortex-M -> Microcontrollers

### M Profile
- There are several version of the M architecture. ARMv6-M, ARMv7E-M, ARMv8-M
    1. Cortex-M0+ -> ARMv6-M, 
    2. Cortex-M23 -> ARMv8-M, 
    3. Cortex-M3 & Cortex-M4F -> ARMv7E-M, 
    4. Cortex-M7 -> ARMv7E-M
- Instruction Set Architecture is 
    1. Collection of instructions
    2. Contract between hardware and software on behavior
    3. It is not definition of implementation
    4. Not a guarantee of performance

## Computer Architecture
- Von Neumann Architecture : Single(Common) bus for instruction and data
- Hardvard Architecture : Separate busses for instruction
- Arm processors
    1. Cortex-M0+ -> Von Neumann
    2. Cortex-M23 -> Von Neumann
    3. Cortex-M3 & Cortex-M4F -> Harvard
    4. Cortex-M7 -> Harvard

- Multiple busses allow for better utilization of memory bandwidth
- Multiple caches enable high percentage of cache hits in both data and code
- ARMv6-M
    1. 56 instructions
    2. Most Thumb1 instruction(Thumb1 -> 16bit instructions)
    3. Some Thumb2 instructions
    4. Multiplication is 32bit x 32bit into 32bit result
- ARMv8-M baseline
    1. 63 instructions
    2. Adds Divide instructions
    3. Optional TrustZone

- ARMv7E-M 
    1. 98+ instructions
    2. All Thumb1 and Thumb2 instruction
    3. Multiplication of 32bit x 32bit into 64bit result
    4. Divide instructions
    5. DSP and Saturation instructions
    6. Optional floating point instructions
        1. Single Precision(M4F)
        2. Double Precision(M7)

- DMIPS : DryStone MIPS benchmark

## Functional Similiarities Between Cortex-M Families
![Register Model](.//Images/RegisterModel.PNG)
- R0-R7 Accessible to all instructions
- R8-12 Accessible to a few 16-bit instructions, Accessible to all 32-bit instructions
- R13 -> Stack Pointer, ARMv7E-M cores have two banked versions
- R14 -> Link Register(Return address for calls)
- R15 -> Program Counter
- PSR -> xPSR(Program Status Register), Not directly accessible, Save to the stack during context switch

- Any code compiled for ARMv6-M runs unchanged on ARMv7E-M and ARMv8-M baseline.
- Allows for libraries to move between cores without re-compiling.
- Applications running in TrustZone enabled processors could benefit.

## NVIC
- NVIC included in Architecture and processor definitions for Cortex-M
- Allows for greater cooperation and efficency between processor and peripherals
- Mechanism for expanding beyond the single IRQ signal into the core
- Exceptions
    1. Software Interrupts
    2. Pre-fetch abort
    3. Undefined instructions
    4. Data aborts
    5. Reset

- Interrupts(IRQ), Non-Maskable Interrupt(NMI), Memory Management Protection Violation, Debug Event, Service Calls
![Register Model](.//Images/Exceptions.PNG)

- Exception Process
    1. Processor detects exception
    2. Saves processor state to stack
    3. Extended Frame includes VFP(Vector Floating Point) state(24 words)
    4. Loads PC(R15) with handler address from vector corresponding the exception
    5. Completion of Handler
        1. Context restored from stack
        2. Program Counter continues execution

- Reset, NMII and Hardfault interrupts priority is not programmable. And always they overwrite other interrupts
- **Tail Chaining** : Abilty to move from a high priority interrupt into a lower priority interupt without exiting Handler mode. Saves two context switching.
- **Interrupt Nesting** : Ability for a higher priority interrupt to preempt a lower priority interrupt currently executing
- **Late Arrival** : If a higher priority interrupt occurs during the context save of a lower priority interrupt, the processor services the late arriving interrupt first.
- Relocatable Vector Table. Defaults to 0x00000000 in Flash. Can be moved via VTOR to SRAM
- Different number of External interrupts to processor
    1. ARMv6-M -> Cortex-M0+ -> 32
    2. ARMv8-M Baseline -> Cortex-M23 -> 240
    3. ARMv7E-M -> Cortex-M4F -> 240
    4. ARMv7E-M -> Cortex-M7 -> 240

- Jitter-free latency of highest priority interrupt
    1. Cortex-M0+ -> 15
    2. Cortex-M23 -> 15 or 27
    3. Cortex-M4F -> 12
    4. Cortex-M7 -> 12

- While instruction is executed, interrupt occured, interrupt serviced, then instruction restart to executed.

## Systick Core Timer
- It is built-in all Cortex-M processors. 
- 24-bit system timer, Clear-on write, Decrementing, Wrap-On-Zero. Clocked by processor clock.

## DIFFERENCES BETWEEN CORTEX-M FAMILIES

### Bus Interfaces
- Cortex-M0+, Cortex-M23, Cortex-M4F : 
    1. **AHB-Lite** : Synchronous bus, High-Performance, Burst-Able, 2 cycle Bus transaction
    2. **APB** : Simple Bus, Atleast 2 cycle transaction time, Decouples from processour bus in speed and power, Synchronous bus
- Cortex-M7 :
    1. **AXI** : Transaction based, Network like model
    2. **AHB-Lite** : Synchronous bus, High performance and brust able, 2 cycle bus transaction
    3. **APB** : Simple Bus, Atleast 2 cycle transaction time, Decouples from processour bus in speed and power, Synchronous bus

### Pipelines
- Latency : Time takes between fetch and execution
- Throughtput : How often an instruction exits the pipeline and executes.

- Cortex-M0+ and Cortex-M23 Pipeline :
    1. Two stage pipeline.
    2. Only Thumb2 instructions
    3. Can fetch up to two instruction per fetch
    4. Decode is split between the fetch and execute stages
- Cortex-M4F Pipeline
    1. Three stage pipeline
    2. Only Thumb2 instructions
    3. Can fetch up to two instructions per fetch
    4. Adds branch prediction

- Cortex-M7 Pipeline
    1. Six stage pipeline
    2. Dual issue
    3. Superscalar
    4. Branch Target Address Cache
    5. Branch Predictor
    6. In order execution

### Processor Modes
- Cortex-M0+
    1. Thread Mode, Handler -> Thread mode normal code, Handler is ISR
    2. Thumb State -> 16-bit instructions mostly
- Privileged Mode : Can access any state or instruction
- Un-Privileged Mode : Takes away certain access to states or instructions, It safers.

- Cortex-M23
    1. Secure World : Has its own Privileged and Unprivileged Thread modes and Handler Mode.
    2. UN-Secure World : Has its own Privileged and Unprivileged Thread modes and Handler Mode.

- Cortex-M4, Cortex-M7
    1. Un-privileged Thread Mode
    2. Privileged Thread Mode
    3. Handler Mode

### Fast I/O access

### DSP Instructions
- They are available for Cortex-M4 and Cortex-M7
- SIMD operation -> Single Instruction Multiple Data
- Saturation algorithms

### Floating Point Units
- They are implemented as co-processors.(Not available for Cortex-M0+ and Cortex-M23)
- They have their own set of registes that may need to be saved on context switch.

### Optional Processor Features


## Memory Hierarchy

### Caches
- Caches is basically chunk of SRAM memory
- **Cache Miss** : When processor look for some data and its not cached. This called Cache miss
- **Cache Hit** : When processor look for some data and its cached. This called Cache Hit
- **Cache Line** : Cache line is 16 byte.
- **Cache Way** : Cache way is 96 bytes
- **Cache Set** : Its collection of cache ways.
- Cortex-M0+, Cortex-M23, Cortex-M4 has no cache support. Cortex-M7 supports caches.
- **Cache Coherency** : When cache and memory data doesnt match. 

### TCM
- Tightly Coupled Memory : Tightly Coupled refers to the interface.
- TCM memory directly connected to core
- SRAMs are connected to core via High-Speed Bus Matrix
- Cortex-M0+, Cortex-M23, Cortex-M4 doesnt have TCM support. Cortex-M7 supports TCM.
- TCM runs at processor speed
- TCM is always fasest compare to Cache

## TRUST-ZONE

### Introduction
- Trust-Zone added in ARMv8-M basic
- Introducing secure and non-secure worlds to architecture
- Trust-zone protects data, indirectly protects communications, enables physical security
- Trust-zone has Secure world and Non-Secure world.
- Worlds defined by memory address
- Trust-Zone protects data and firmware while increasing the software reliability of the system
- Trust-Zone allows for  software to instract securely with zero trust or assumptions between worlds