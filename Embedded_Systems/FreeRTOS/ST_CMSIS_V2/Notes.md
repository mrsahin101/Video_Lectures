# **FreeRTOS CMSIS_V2 API**

## **Introduction**
- [Serial Wire Viewer](https://www.codeinsideout.com/blog/stm32/swv/#swv-windows)
- This Lecture series are based on CMSIS_V2
- To enable SW, do the following
    1. define Task_action as below
    ``` C
    void Task_action(char message)
    {
        ITM_SendChar(message);
        ITM_SendChar('\n');
    }
    ```
    2. Enable SW debug on CubeMX
    3. Do debug configuration as below


    ![RTOS](.//Images/CMSIS_OS_ITM_Debug.PNG)

    4. Open SWV ITM Data Console, Add Port 0

    ![RTOS](.//Images/CMSIS_OS_Enable_SWV.PNG)
    

- Also to save some project as template do the following

![RTOS](.//Images/CMSIS_OS_Export.PNG)

- With values higher Than SYSCALL macro is not blocked by OS.Even the Critical sections wont block those interrupt higher than SYSCALL macro interrupt priority. 

## **Operating System Main Components**
- Components
    1. **Tasks or Threads** : mini programs run in endless loop
    2. **Scheduler** : To manage tasks and switch between them
    3. **Queues** : To pass information among tasks or among tasks and interrupts
    4. **Semaphores** : ON/OFF type of queues.
    5. **Mutexes** : semaphores with tokens
    6. **Software Timers** : To manage tasks execution in particular moments

### What is a Task?
- Task is piece of C function does intended work
    1. It is a C **function**
    2. It should be run within **infinite** loop
    3. It has its own part of **stack** and priority
    4. It can be in 4 different states. **RUNNING**, **READY**, **BLOCKED**, **SUSPENDED**
    5. It is **created** and **deleted** by calling API Functions
    ``` C
    /* Task Body Example */
    void TaskName(void *arguments)
    {
        /*initialization part*/
        for(;;)
        {
            /*Endless Loop */
        }
    }
    ```

![RTOS](.//Images/CMSIS_OS_Task_States.PNG)
   
### What is Scheduler?
- Scheduler is algorithm determining which task to execute
    1. **Select** one of the task being **READY** to executed
    2. There are few mechanism controlling access to CPU for Task(**timeslice**, **preemption**, **idle**);
- In FreeRTOS, **round-robin** scheduling is implemented. Round-Robin can be used either with preemptive or cooperative multitasking

### What is an OS Heap?
- It is memory chunk assigned to FreeRTOS.


## **Basic Features of FreeRTOS**
- Market leading RTOS by Real Time Engineers LTD
- **Professionally** developed with **strict** quality management
- Commercial version : **OpenRTOS**, **SafeRTOS**
- Distributed under MIT open license.
- In STM32 Cube used as Real-time operating system, by wrapping layer CMSIS OS provided by ARM

### Main Features
- **Pre-emptive** or **Co-operative** Real-time kernel
- **Tiny** memory footprint(Less than 10kB ROM) and easly scalable
- Includes a tickless mode for low power applications
- Synchronization and inter-task communication using
    1. Message Queues
    2. Binary and Counting Semaphores
    3. Mutexes
    4. Group Events(Flags)
- Software timers for task scheduling
- Execution trace functionality
- CMSIS-RTOS API Port

- Core Resources
    1. System Timer(SysTick) - Generate system time(Time Slice)
    2. Two Stack Pointesr(**MSP**, **PSP**)
- Interrupt Vectors
    1. **SVC** - System call service(like SWI instruction)
    2. **PendSV** - Pended system call(Context switching)
    3. **SysTick** - System Timer
- Flash Memory
    1. **6-10 KB** memory
- Ram Memory
    1. **~0.5KB** + task stacks

### SVC - System Service Call
- **SVC** : System service call / supervisor call
- It is **instruction** and an **exception**. Once SVC instruction executed, **SVC IRQ** is triggered immediately(Unless there is higher priority IRQ active)
- SVC contains **8-bit immediate value** what could help to determine Which **OS** service is requested
- **Don't** use SVC inside NMI or Hard Fault handler

### PendSV - Pended System Call
- PendSV is priority **programmable** exception triggered by SW(Write to ICSR register **@0xE000ED04, **SCB->ICSR |= (1<<28)**)
- It is not precise(Contrary to SVC). After **setting** pending bit, CPU can execute number of instructions before **exception** starts.

### System Timer
- It is necessary to trigger context switch **regular time** slots
- In Cortex-M architecture **24-bit down counting SysTick** is used.(it can be changed)
- System timer is **triggered** **PendSV SW interrupt** to perform context-switch
- When using HAL Libraries, Timebase timer should be changed to something else than **SysTick**

### FreeRTOS File Structure
- Files
    1. **croutine.c/croutine.h** : Co-routines functions definitions, Efficent in 8-bit and 16-bit architecture. In 32-bit architecture usage of tasks is suggested
    2. **event_groups.c/event_groups.h** : Effective inter-task communication
    3. **list.c/list.h** : List implementation used by the scheduler
    4. **queue.c/queue.h/semphr.h** : Semaphores, mutexes functions definitions
    5. **stream_buffer.c/stream_buffer.h** : Optimised for single writer and single reader inter-task data stream communication(can be used in dual core architectures) 
    6. **tasks.c/tasks.h** : Task functions and utilities definitions
    7. **timers.c/timers.h** : Software timers functions definitions
    8. **FreeRTOS.h** : Configuration file which collect whole FreeRTOS sources.
    9. **FreeRTOSConfig.h** : Configuration of FreeRTOS system, system clock and IRQ parameters configurations
    10. **heap_x.c** : Memory management functions(allocate and free memory segment, three different approaches in **heap_1.c**, **heap_2.c**, **heap_3.c** and **heap_4.c** files)
    11. **port.c/portmacro.h** : Low level functions supporting SysTick timer, context switch, interrupt management on low hw level - strongly depends on the platform(core and sw toolset).Mostly written in assembly. In portmacho.h there are definitions of **portTickType** and **portBASE_TYPE**.

- **list.c/list.h**, **tasks.c/task.h**, **FreeRTOS.h**, **FreeRTOSConfig.h** and one of heap management file is included in every FreeRTOS distribution.

## **Native API**
- Prefixes at variable names
    1. **c** -> char
    2. **s** -> short
    3. **l** -> long
    4. **x** -> portBASE_TYPE defined in portmacro.h for each platform
    5. **u** -> unsigned
    6. **p** -> pointer
    7. **v** -> void
    8. **prv** -> private
    ![RTOS](.//Images/CMSIS_OS_Naming.PNG)
    
- Prefixes at macro definitions their location
    1. **port**     -> portMAX_DELAY            -> portable.h
    2. **task**     -> task_ENTER_CRITICAL      -> task.h
    3. **pd**       -> pdTRUE                   -> projdefs.h
    4. **config**   -> configUSE_PREEMPTION     -> FreeRTOSConfig.h
    5. **err**      -> errQUEUE_FULL            -> projdefs.h

- Common Macro Definitions
    1. **pdTRUE**   -> 1
    2. **pdFALSE**  -> 0
    3. **pdPASS**   -> 1
    4. **pdFAIL**   -> 0

- CMSIS OS API is simple additional software layer over FreeRTOS API
- Not **All** features available in FreeRTOS is available in CMSIS OS API
- It is possible to use additional FreeRTOS modules(like task notification) among CMSIS OS code
- Main OS handlers are just basic typedefs from FreeRTOS to CMSIS OS. Example :
``` C
typedef TaskHandle_t osThreadId_t
```

## CMSIS OS API
- CMSIS-OS API is generic RTOS interface for Cortex-m Processor based devices
- CMSIS-OS API is RTOS independent, this allows an **easy linking** to any third-party RTOS
- CMSIS OS defines minimum feature set including
    1. **Thread Management**
    2. **Kernel control**
    3. **Semaphore management**
    4. **Message queue and mail queue**
    5. **Memory management**
- STM32Cube comes with an implementation of the CMSIS-RTOS for FreeRTOS
- Detailed documentation :
    1. **CMSIS_OS v1.x** -> [CMSIS_OS V1](http://keil.com/pack/doc/CMSIS/RTOS/html/index.html)
    2. **CMSIS_OS v2.x** -> [CMSIS_OS V2](http://keil.com/pack/doc/CMSIS/RTOS2/html/index.html)

- Most functions **returns** <code>osStatus</code>(v1.x)/<code>osStatus_t</code>(v2.x) value, which allows error checking for functions
- Each OS component has its own **ID**
    1. **Tasks** : <code>osThreadId</code>(v1.x)/<code>osTreadId_t</code>(v2.x) -> mapped to **TaskHandle_t** within FreeRTOS API
    2. **Queues** : <code>osMessageQId</code>(v1.x)/<code>osMessageQId_t</code>(v2.x) -> mapped to **QueueHandle_t** within FreeRTOS API
    3. **Semaphores** : <code>osSemaphoreId</code>(v1.x)/<code>osSemaphoreId_t</code>(v2.x) -> mapped to** SemaphoreHandle_t** within FreeRTOS API
    4. **Mutexes** : <code>osMutexId</code>(v1.x)/<code>osMutexId_t</code>(v2.x) -> mapped to **SemaphoreHandle_t** within FreeRTOS API
    5. **SW timers** : <code>osTimerId</code>(v1.x)/<code>osTimerId_t</code>(v2.x) -> mapped to **TimerHandle_t** within FreeRTOS API

- Delays and timeouts are given in **ms**
    1. **0** -> No delay
    2. **>0** -> Delay in ms
    3. **0xFFFFFFFF** -> wait forever(defined in osWaitForever within cmsis_os.h file)

![RTOS](.//Images/CMSIS_OS_Status.PNG)
![RTOS](.//Images/CMSIS_OS_Tasks_States.PNG)

- Thread parameters are grouped within lists at **osThreadAttr_t** object within cmsis_os2.h file
```C
const char *name;           // Name of the thread, Configurable via CubeMX
uint32_t attr_bits;         // Attribute bits
void *cb_mem;               // Pointer to thread control block memory area
uint32_t cb_size;           // Thread control block(TCB) size
void *stack_mem;            // Pointer to thread stack memory area Configurable via CubeMX and with macro configMINIMAL_STACK_SIZE
osPriority_t priority;      // Initial thread priority(Default: osPriorityNormal). Configurable with CubeMX
TZ_ModuleId_t tz_module;    // TrustZone module identifier
uint32_t reserved;          // For future use, must be set to 0
```
![RTOS](.//Images/CMSIS_OS_Priority_Table.PNG)

## CMSIS_OS API V2.x vs V1.x
- OS objects creation without macros(dynamic creation and resource allocation)
    1. added osXxxxNew functions which replace osXxxxCreate
    2. added osXxxxAttr_t structures
- **osStatus** codes simplified and renamed to **osStatus_t**
- **osEvent** return structure deprecated
- Event flags parameter and return type changed from int32_t to uint32_t
- Full list of changes available in this link : [Migration Functions](http://keil.com/pack/doc/CMSIS/RTOS2/html/os2MigrationFunctions.html)
- Alot of new **Kernel** functions added!
    1. **osKernelInfo_t** and **osKernelGetInfo**
    2. **osKernelState_t** and **osKernelGetState** (replaces osKernelRunning)
    3. **osKernelLock**, **osKernelUnlock**
    4. **osKernelSuspend**, **osKernelResume**
    5. **osKernelGetTickCount**, **osKernelGetTickFreq**
    6. **osKernelRestoreLock**
- Some functions are renamed
    1. **osKernelSysTick** to **osKernelGetSysTimerCount**
- Replaced **osKernelSysTickFrequency** with **osKernelGetSysTimerFreq**
- Deprecated : **osKernelSysTickMicroSec**

- **Thread** Functions changes :
    1. Extended number of thread priorities
    2. Renamed **osPriority** to **osPriority_t**
    3. Replaced **osThreadCreate** with **osThreadNew**
    4. Added **osThreadGetName**
    5. Added **osThreadState_t** and **osThreadGetState**
    6. Added **osThreadGetStackSize** and **osThreadGetStackSpace**
    7. Added **osThreadSuspend** and **osThreadResume**
    8. Added **osThreadJoin**, **osThreadDetach**, **osThreadExit**
    9. Added **osThreadGetCount**, **osThreadEnumerate**
    10. Added **Thread Flags(moved from signals)**

- **Signals** :
    1. Renamed **osSignals** to **osThreadFlags**(moved to Thread Flags)
    2. Changed return value of Set/Clear/Wait Functions
    3. Clear function limited to current running thread
    4. Extended Wait function(Options)
    5. Added **osThreadFlagsGet**
- **Event Flags** : Adde new independent object for handling Event Flags
- **Delay and Wait Functions** : added **osDelayUntil**, deprecated **osWait**
- **Sw Timer** : replaced **osTimerCreate** with **osTimerNew**. Added **osTimerGetName**, **osTimerIsRunning**

- **Mutexes**
    1. Extended attributes(Recursive, Priority Inherit, Robust)
    2. Replace **osMutexCreate** with **osMutexNew**
    3. Renamed **osMutexWait** to **osMutexAcquire**
    4. Added **osMutexGetName** to **osMutexGetOwner**

- **Semaphore** 
    1. Extended maximum and initial token count
    2. Replace **osSemaphoreCreate** with **osSemaphoreNew**
    3. Renamed **osSemaphoreWait** to **osSemaphoreAcquire**(changed return value)
    4. Added **osSemaphoreGetName**, **osSemaphoreGetCount**

- **Memory Pool** 
    1. Using **osMemoryPool** prefix instead of **osPool**
    2. Replace **osPoolCreate** with **osMemoryPoolNew**
    3. Extended **osMemoryPoolAlloc(timeout)**
    4. Added **osMemoryPoolGetName**
    5. Added **osMemoryPoolGetCapacity**, **osMemoryPoolGetBlockSize**
    6. Added **osMemoryPoolGetCount**, **osMemoryPoolGetSpace**
    7. Added **osMemoryPoolDelete**
    8. Deprecated **osPoolCAlloc**
- **Message Queue** 
    1. Extended fixed size message instead of single 32-bit value
    2. using **osMessageQueue** prefix instead of **osMessage**
    3. Replace **osMessageCreate** with **osMessageQueueNew**
    4. Updated **osMessageQueuePut**, **osMessageQueueGet**
    5. Added **osMessageQueueGetName**
    6. Added **osMessageQueueGetCapacity**, **osMessageQueueGetMsgSize**
    7. Added **osMessageQueueGetCount**, **osMessageQueueGetSpace**
    8. Added **osMessageQueueReset**, **osMessageQueueDelete**
    9. **Mail Queue** deprecated, superseded by extended Message Queue functionality.

## Configuration Basics
- 2 configuration file is there. **FreeRTOS.h** and **FreeRTOSConfig.**. We can configure RTOS as we want it

## Memory Allocation Schemes
- In **heap_3.c** heap management file, we create our linker file and our memory allocation scheme.

- **heap_2.c** : Uses **first-fit** algorithm to allocate memory. Simplest allocation method(deterministic), but **does not** follow **freeing** of allocated memory
- **heap_2.c** : **Not recommended** for new projects. Kept for backward compatibility. Implement **best-fit** algorithm for allocation. Allows memory free() but **doesn't combine** adjacent free blocks.(It has risk of fragmentation)
- **heap_3.c** : Implements simple wrapper for standart C library **malloc** and **free()**. Wrapper makes these functions thread safe, but makes code increase and **not deterministic**. Uses linker heap region. <code>configTOTAL_HEAP_SIZE</code> macro has no effect when this model is used.
- **heap_4.c** : It is most popular one. Uses **First-Fit** algorithm to allocate memory. It is able to **combine** adjacent free memory blocks into **single block**. This is used in STM32Cube examples. The memory array used by heap_4 declared in **heap_4.c** and start address is configured by linker **automatically. To use your own decleration <code>configAPPLICATION_ALLOCATED_HEAP</code> must be set 1 in FreeRTOSConfig.h and array must be declared within user code with selected start address and size specified by macro <code>configTOTAL_HEAP_SIZE</code>. Heap_4.c is organized as linked list. 
- **heap_5.c** : Fit algorithm able to combine adjacent free blocks into single block using same algorithm with heap_4. but supporting different memory regions(SRAM1, SRAM2 etc) being not in linear memory space. It is only one must be explicitly initialized before any OS object can be created. To initialize this scheme <code>vPortDefineHeapRegions()</code> function should be called. Specifies start address and size of each separate memory area.

![RTOS](.//Images/CMSIS_OS_Heap_5.PNG)
![RTOS](.//Images/CMSIS_OS_Memory_Functions.PNG)

## FreeRTOS Memory Management Hints
- FreeRTOS heap is different than system heap defined at compiler level
- Implements <code>vPortMalloc()</code> instead of **malloc()**, and <code>PvPortFree()</code> instead of **free()**
- Total amount of heap is defined by macro <code>configTOTAL_HEAP_SIZE</code>
- <code>xPortGetFreeHeapSize()</code> API function returns total amount of heap space remains unallocated.

### Task Heap usage
- Each created task requires TCB(Task Control Block) and a stack that are allocated in heap
- TCB size in bytes depends on macros below
    1. Minimum configuration is TCB size 24 words -> 96 bytes
    2. if <code>configUSE_TASK_NOTIFICATIONS</code> enabled adds 8 bytes 
    3. if <code>configUSE_TRACE_FACILITY</code> enabled add 8 bytes
    4. if <code>configUSE_MUTEXES</code> enabled adds 8 bytes
- When task created stack size is passed as argument, words of 32-bits
- Task number of bytes  = TCB_Size + (4 * task_stack_size);
- <code>configMINIMAL_STACK_SIZE</code> defines minimum stack size that can be used in words. Idle task takes this size automatically.
- Necessary task stack size can be **fined-tuned** using <code>uxTaskGetStackHighWaterMark()</code>

### Semaphores, Mutexes and Queues Heap usage
- Each semaphore declared by user application requires 88 bytes to be allocated in heap
- Each mutex declared by user application requires to be allocated in the heap
- For each message queue requires following : <code>Number_of_bytes = 76 + ((element_size * number_of_elements) + 16);</code>

### Software Timers Heap usage
- When Software timers are enabled, scheduler creates **automatically** timer service task(DEAMON).The Timer task parameters set by macros : <code>configTIMER_TASK_PRIORITY</code> and <code>configTIMER_TASK_STACK_DEPTH</code>. The scheduler also creates message queue used to send commands to RTOS DEAMON(timer service task). This queue length is configurable with macro : <code>configTIMER_QUEUE_LENGTH</code>
- Timer Deamon Task (in bytes) : TCB_Size + (4 x configTIMER_TASK_STACK_DEPTH)
- Timer message queue in bytes : 76 + ((12 * configTIMER_QUEUE_LENGTH) + 16)
- Each timer Created by **osTimerCreate** need 48 bytes.

### Reducing RAM Footprint
- Optimize Stack allocation for each task : use <code>uxTaskGetStackHighwaterMark()</code>
- Recover and minimize the stack used by main and rationalize the number of task
- Use minimal number of priorites.
- If not using some component(like timers, mutexes..) **disable** their defines

## Scheduler
![RTOS](.//Images/CMSIS_OS_Cooperative.PNG)
![RTOS](.//Images/CMSIS_OS_Cooperative_with_IRQ.PNG)

![RTOS](.//Images/CMSIS_OS_Preemptive.PNG)

- Scheduler is algorithm **determining** which task to **execute**. In FreeRTOS **round-robin** scheduling algorithm is implemented. 

### CMSIS Kernel API
- Functions :
``` C
/* Initialize heap regions if heap5 memory management scheme is selected
 * Sets kernel state to osKernelReady. Not working in IRQ mode
 */
osStatus_t osKernelInitliaze(); 
/* Gets KERNEL_VERSION and KERNEL_ID values and stores them in memory,
 * can work from user code and IRQ
 */
osStatus_t osKernelGetInfo();
/* Reads and returns kernel current state,
 * can work from user code and IRQ
 */
osKernelState_t osKernelGetState();

/* Set kernel state to osKernelRunning, Executing vTaskStartScheduler(),
 * not working in IRQ mode
 */
osStatus_t osKernelStart();

/* If scheduler in run state, it will be suspended, not working in IRQ mode */
int32_t osKernelLock();

/* If scheduler in suspended state, it wil lbe unlocked , not working in IRQ mode */
uint32_t osKernelUnlock();

/* In case scheduler is suspended or run mode it will confirm current state. */
uint32_t osKernelRestoreLock();
/* Returns value of configTICK_RATE_HZ can be called from user code and IRQ*/
uint32_t osKernelGetTickFreq();
/* Returns tick count can be called from user code and IRQ*/
uint32_t osKernelGetSysTimerCount();
/* returns value of configCPI_CLOCK_HZ, can be called from user code and IRQ */
uint32_t osKernelSysTick();
```
![RTOS](.//Images/CMSIS_OS_Kernel_Functions.PNG)


## Interrupts and Connection to Hardware

### PendSV interrupt
- Used for task switching before tick rate
- Lowest NVIC interrupt priority
- Not triggered by any peripheral

### SVC interrupt
- Interrupt risen by SVC instruction
- **SVC 0** call used only once, to start scheduler

### SysTick Timer
- Lowest NVIC interrupt priority
- Used for task switching on <code>configTICK_RATE_HZ</code> regular timebase
- Set PendSV if context switch is necessary


- **PendSV** and **SysTick** interrupts has lowest NVIC priority to not block Hardware level interrupts.

![RTOS](.//Images/CMSIS_OS_Interrupts.PNG)

- When we call **FromISR** functions from interrupt, **PendSV** is triggered if we set **xHigherPriorityTaskWoken** parameter. In cMSIS API, it is handled automatically by library.

## Booting Process

### Hardware Dependent
- Configure the CPU clocks
- Initialize static and global variables that contain only value zero(bss)
- Initialize variables that contain a value other than zero
- Perform any other hardware set-up required

## FreeRTOS related
- Create application queues, semaphores, mutexes(~ 500 CPU cycles/per object)
- Create application tasks(~1100 CPU cycles/task)
- Start RTOS scheduler(~1200 CPU cycles)

- Idle Task code is generated automatically when scheduler is started. Performing following in endless loop
    1. Check for deleted tasks to clean the memory
    2. taskYIELD() if preemption is not used
    3. Get yield if anotehr task waiting and <code>configIDLE_SHOULD_YIELD 1</code> 
    4. Perform low power entrance if <code>configUSE_TICKLESS_IDLE != 0</code>
    5. Executes <code>vApplicationIdleHook()</code>if <code>configUSE_IDLE_HOOK 1</code> defined.

- Criticl section mechanism allows to block all interrupts during sensitive operation. Hardware ISR still operational.
    1. **portENTER_CRITICAL()** -> All interrupts are blocked below <code>configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY</code>
    2. **portEXIT_CRITICAL()** -> Block is removed.

## Context Switching

![RTOS](.//Images/CMSIS_OS_Context_Switching.PNG)

- Context switch depends on port, compiler, configuration.
- STM32 devices needs 12 CPU cycles on each interrupt entrance and exit.
- With FPU registers context switch could be longer.

### Stack Pointers
- **Main Stack Pointer(MSP)**
    1. Used in interrupts
    2. Allocated by linker during compiling
- **Process Stack Pointer(PSP)**
    1. Each task have own stack pointer
    2. During context switch the stack pointer is initialized for correct task

- In FreeRTOS **MSP** used **Interrupts** and **Kernel**, **PSP** used for tasks **stack**.