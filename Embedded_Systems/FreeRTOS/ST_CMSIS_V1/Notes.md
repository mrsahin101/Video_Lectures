# CMSIS V1

## Introduction
- **Operating System** : Simultaneous runing tasks, implementing different modules, hardware resources modules, Interrupt and scheduling task, are features that OS should be implement. Single core means simultaneously single task running.

- FreeRTOS gives basic structure. If we want to run some drivers, we should implement it.

- **Task** : It's C function. Usualy initialization part and never ending loop. It has own stack and priority. Can be in 4 different states, **READY**, **RUNNING**, **BLOCKED**, **SUSPENDED**. When task first created, it is in **READY** state. When task put in **SUSPENDED** state, scheduler doesn't waste time with evaluation its priority.

![RTOS](.//Images/CMSIS_OS_Task.PNG)

- FreeRTOS doesn't speed up application, but simplifies and make code structure better. But it could also help with synchronizing, resource management alot. 

- **Scheduler** : It is algorithm determining which task to execute. FreeRTOS implements **round-robin** scheduling algorithm. **Round-Robin** could be implemented as **pre-emptive** or **co-operative** multi-tasking.

- **Round-Robin** algorithm shares timeslice between task same priority.

- **pre-emptive** is when higher priority task become available, switching to it happens immediately.

- **co-operative**  is when higher prioirty task become available, switch to it happens until running task goes into blocked state.

- **pre-emptive** is more responsive but it's less efficent. Because context switch overhead is more. **co-operative** could be more stable.

![RTOS](.//Images/CMSIS_OS_Heap.PNG)

- FreeRTOS has its own heap management. FreeRTOS allocated tasks control blocks, tasks stacks, and other kernel object on heap. Heap is initialized when FreeRTOS initialized. 
- We can look list or map file to estimate task stack usage. Or We can give huge stack first for task and get high water mark and then test it. After testing it then we can make better decision about how much we give to stack. CPU has nothing about stack because all its heap to it.
- But if we are use FreeRTOS-MPU we can define memory protection for each chunk of RAM used by **different** tasks. When it runs out of stack, Core will give us MPU Exception

- TCB is where context is switched where register context saved. This is Only available when FPU not used. When FPU used, it must be specified in FreeRTOS Configuration. Then when context switched fpu registers will be saved in TCB as well.

## Basic Features
- FreeRTOS is market leading. Professionally developed with strict quality management. Commercially versions : OpenRTOS, SafeRTOS
- It is completely free.
- FreeRTOS-Plus is used for different drivers. 

- **Main Features** : 
    1. Pre-emptive or co-operative real-time kernel (Decided in compile-time)
    2. Tiny memory footprint and easy scalable
    3. Includes a tickless mode for low power applications
    4. Synchronization and inter-task communicating(message queues, binary and counting semaphores,mutexes, group events(flags))
    5. Software timers for tasks scheduling
    6. Executing trace functionality
    7. CMSIS-RTOS API port

## Resources Used
- FreeRTOS expect this resources.
- Core Resources :
    1. System Timer(Systick), generate system time(time slice)
    2. Two stack Pointers. **MSP**, **PSP**
- Interrupt vectors
    1. **SVC**, system service call
    2. **PendSV**, pended system call(switching context)
    3. **SysTick**, System Timer
- Flash memory
    1. **6-10kB**
- Ram Memory
    1. **~0.5kB** + task stacks

- System timer used as periodic time base. Shortest could be defined **1ms**
- **PendSV** takes care of context-switch. **SVC** executed immediately, but **PendSV** could be wait pending state.
- ST HAL libs need timebase. When RTOS is not used, **SysTick** used for halb libraries. When RTOS is used, **SysTick** used for RTOS and we need to assign different timer for HAL libraries. For example timer 16. Avoid using **SysTick** for RTOS and HAL.

## Files Structure
- Mandatory Files 
    1. **tasks.c**/**task.h** : Task Functions and utilities definition. **Directory** : \Source, \Source\include
    2. **list.c**/**list.h** : List implementation used by the scheduler. **Directory** : \Source, \Source\include
    3. **FreeRTOS.h** : configuration file which collect whole FreeRTOS sources. **Directory** : \Source\include
    4. **FreeRTOSConfig.h** : Configuration of FreeRTOS System, system clock and irq parameters configuration. **Directory** : \Core\include
    5. **heap_x.c** : Memory management functions(allocate and free memory segment, three different approaches in heap_1.c, heap_2.c, heap_3.c, heap_4.c, heap_5.c files)
    6. **port.c**/**portmacro.h** : Low level functions supporting Systick timer, context switch, interrupt management on low hw level - strongly depends on the platform(core and sw toolset). Mostly written in assembly.**Directory** : \Source\portable\xxx\yyy

- Optional(Depends on what functionality is used.)
    1. **queue.c**/**queue.h**/**semphr.h** : Semaphore, mutexes functions definitions. **Directory** : \Source, \Source\include
    2. **timers.c**/**timers.h** : Software timers functions definitions. **Directory** : \Source, \Source\include
    3. **event_groups.c**/**event_groups.h** : Includes event groups functionality. **Directory** : \Source \Source\include
    4. **croutine.c**/**croutine.h** : Co-routine functions definitions. Efficent in 8-bit, 16-bit architecture. In 32-bit not recommended. **Directory** : \Source \Source\include

## Available APIs
- Native API is originally created by FreeRTOS. It is still underneath CMSIS OS

- Naming Convention : 
    1. Prefixes : **c** -> char, **s** -> short, **l** -> long, **x** -> data structures, **u** -> unsigned, **p** -> pointer, **v** -> void, **prv** -> private.
    ![RTOS](.//Images/CMSIS_OS_TaskNaming.PNG)

- For macro naming convention : first word shows which file this macro is. Example : portMAX_DELAY -> portable.h, task_ENTER_CRITICAL -> task.h

- Common Macro definitions
    1. **pdTRUE** 1
    2. **pdFALSE** 0
    3. **pdPASS** 1
    4. **pdFAIL** 0
    
- CMSIS is standart interface to control any microcontroller based on ARM Cortex-M. **CMSIS_OS** is standart api for RTOS'es developed by ARM for Cortex-M devices.
- Defines minimum feature set including
    1. Thread Management
    2. Kernel control
    3. Semaphore management
    4. Message queue and mail queue
    5. Memory management.

        ![RTOS](.//Images/CMSIS_OS_Compare.PNG)

- Most of the functions returns **osStatus** value, which allows to check whether the function is completed or there was some issue.

- Don't need to **FromISR** functions in FreeRTOS API. It hides all details from user. Also each object created has own ID.
- Delays and timeouts are given in ms. **0** -> No delay, **>0** -> Delay in ms, **0xFFFFFFFF** -> wait forever.

- **osStatus** values :
    ![RTOS](.//Images/CMSIS_OS_osStatus.PNG)
    ![RTOS](.//Images/CMSIS_OS_errorStatus.PNG)

## CubeMX
- FreeRTOS uses **SysTick** for clock source. So we have to assign different Timer as TimeBase Source for HAL.

- The features we dont use, it is recommended to keep them disabled.(To keep code size small.)

- Context switching interrupts(**SysTick**, **PendSV**) is done in lowest possible value, because it shouldnt block any hardware interrupts. Because Operating System is Middleware and it should not interact with negative way. 
- Also in config section, we define <code>LIBRARY_LOWEST_INTERRUPT_PRIORITY</code> and <code>LIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY</code>. Max syscall is used for context switch interrupts.

## Configuration
- Configuration settings are set in **FreeRTOSConfig.h** file.
![RTOS](.//Images/CMSIS_OS_Config_Option.PNG)

- In Cortex-M4 devices, lowest interrupt priority is 0xF -> 15.(Depends on how many bit used. For Cortex-M4 4 bit used.)

- Higher priority Hardware interrupt (Higher than MAX_SYS_CALL value) will not block by operating system.

- configMINIMAL_STACK_SIZE is given by **words**, while configTOTAL_HEAP_SIZE is given by **bytes**.

## Memory Management - HEAP
- In Operating System, we need **thread-safe** operations. 
- We can define total size with <code>configTOTAL_HEAP_SIZE</code>.
- We can check for highest point reached on stack with watermark API Function.
- When Timers used <code>configUSE_TIMER</code> macro should be defined
- Deamon task should have appropriate stack size and priority.
- Also Timer Queue length should be defined in FreeRTOSConfig.h <code>configTIME_QUEUE_LENGTH</code>
- <code>vApplicationStackOverflowHook()</code> is important function and must use it
- <code>configMAX_PRIORITIES</code> macro should be kept lowest possible, because the higher it is the more RAM it needs.
- Pools are faster to implement in run-time but they are not recommended.

## Scheduler

### Co-operative multitasking
- Requires co-operation of all tasks.
- Context gets switched only when **RUNNING** task
    1. goes to **BLOCKED** state(osDelay())
    2. goes to **READY** state(osThreadYield())
    3. is put into **SUSPEND** mode by the system
- Tasks are not preempted with higher priority tasks.
- No time slice preemption as-well.
- To enable it define macro below in FreeRTOSConfig.h
``` C
#define configUSE_PREEMPTİON 0
```

### Pre-emptive Multi-tasking
- Tasks with the same priority share CPU time
- Context gets switched when :
    1. **Time-slice** has passed
    2. Task with **higher-priority** has come
    3. Task goes to **BLOCKED** state(osDelay())
    4. Task goes to **READY** state(osThreadYield())
- To enable it define macro below in FreeRTOSConfig.h
``` C
#define configUSE_PREEMPTION 1
```

- Cooperative with preemption by **IRQ** could be used. When Interrupt happens it could request context switch and lets **context** switch happens

- Scheduler is **algorithm** determining which task to execute. Typically triggered by **PendSV**. It scans all tasks in **READY** state. If all tasks are equal priority it uses **round-robin** algorithm

### Interrupts
- **PendSV** interrupt
    1. Used for task switching before tick rate
    2. Lowest NVIC Priority
    3. Not triggered by any peripheral

- **SVC** interrupt
    1. Interrupt risen by **SVC** instruction
    2. SVC 0 call **used only once**, to start the scheduler.

- **SysTick** Timer
    1. Lowest **NVIC** interrupt priority
    2. Used for task switching on <code>configTICK_RATE_HZ</code> regular timebase
    3. Set **PendSV** if context switch is necessary

![RTOS](.//Images/CMSIS_OS_Interrupts.PNG)
![RTOS](.//Images/CMSIS_OS_Interrupts2.PNG)
    
- RTOS interrupts priority has to run below <code>configMAX_SYSCALL_INTERRUPT_PRIORITY</code>

- When using **CMSIS API**, Handles IRQ procedures for us.(for context switch.)

![RTOS](.//Images/CMSIS_OS_Interrupts_API.PNG)

- To speed up booting up process, some initializating could be deferred to RTOS tasks.

- Idle task hook could be used to **wake-up** microcontroller from low power mode.

- All FreeRTOS items are implemented in lists.
![RTOS](.//Images/CMSIS_OS_List.PNG)

- To stop scheduler -> **vTaskEndScheduler()** is used. CMSIS os not implemented.

- **osKernelRunning()** function is used for checking status. if returned 0, RTOS not started, if returned 1, RTOS is already started. To allow this, define macro below in FreeRTOSConfig.h
``` C
#define INCLUDE_xTaskGetSchedulerState 1
```
- **osKernelSysTick()** returns value of **SysTick** value

## Tasks
- It can be in 4 different States(**RUNNING**, **BLOCKED**, **SUSPENDED**, **READY**)
- It never returns.
- It gets argument type of : **void const * argument**. It means any type of data we can pass into it.
- Created by **osThreadCreate()** and deleted by **osThreadDelete()**
- A task consist of three parts
    1. **Program code** : This is pointer of Task. This is where scheduler jump when this task is scheduled.
    2. **Stack** : Where it holds variables
    3. **TCB**(Task control block) : Contains status information of task, including stack pointer, task priority, current task status

- The process of saving the context of a task that is being **suspended** and restoring context of task being **resumed** is called <code>context switching</code>
- Code body example :
``` C
void FirstTask(void const * argument)
{
    /*task initialization */

    for(;;)
    {
        /* Task code*/
    }
    /*we should never be here */
}
```
![RTOS](.//Images/CMSIS_OS_Task_State_Machine.PNG)
- There can be only <code>one</code> task in **RUNNING** state.(for single core processor.  )
- Sometimes increasing task priorities can be good trick to temporarly changing execution flow.

![RTOS](.//Images/CMSIS_OS_Priority.PNG)

### Context Switching
- **SysTick** interrupt causes execution of **xPortSysTickHandler()** in port.c file. This handler first disables interrupts, then activates bit to run  **xPortPendSVHandler** function. This function calls **vTaskSwitchContext**, This function selects highest priority task in **READY** state.

- Context switching time depends on **Compiler**, **port** and **configuration**. To measure context-switch time, We can use GPIO pins to output and check wave.

- To generate 1 sys clock long puls on some GPIO, **SEV** assembly instruction could be used. This will switch **EVENTOUT** pin

- Stack Pointers : Both are them banked. Both of them used as register **R13**
    1. **Main Stack Pointer** used when interrupt
    2. **Process Stack Pointer** used in standart application code.

- To define task for example : <code>osThreadDef(Task1, "FirstTask", osPriorityNormal, 0 ,128);</code>
- Task1Handle = <code>osThreadCreate(osThread(Task1), NULL);</code>
- CMSIS api takes stack size in bytes.

- Task firstly **defined** then, created.

``` C
/* Task Handle Definition */
osThreadId Task1Handle;
/* Create task */
osThreadId osThreadCreate(const osThreadDef *thread_def, void *argument);
/* Delete a task */
osStatus osThreadTerminate(osThreadId thread_id); // osStatus osThreadTerminate(NULL);
/* Get task ID */
osThreadId osThreadGetId(void);

/* Yield Task */
osStatus osThreadYield(void);
/* Check if task is suspended */
osStatus osThreadIsSuspended(osThreadId thread_id);
/* Resume task */
osStatus osThreadResume(osThreadId thread_id);
/* Check State of Task */
osThreadState osThreadGetState(osThreadId thread_id);
/* Suspend task */
osStatus osThreadSuspend(osThreadId thread_id);
/* Resume all tasks */
osStatus osThreadResumeAll(void);
/* Suspend all tasks */ 
osStatus osThreadSuspendAll(void);
```

## Inter-Task Communication

### Queues 
- **Queues** : Allows to pass more information between tasks. Suspend task if it tries **put** to full queue or **get** from empty one
- Queues are pipes to transfer data between tasks.
- Default behaviour is **FIFO**(First In - First Out), but it could be used as **LIFO**(Last in - First Out)
- Native API Function <code>xQueueSendToFron()</code> not available on CMSIS RTOS
- All data sent to queue must be same type, declared during queue **creating** phase. It can be simple **variable** or **structure**
- In CMSIS RTOS API there are 2 types of queue
    1. **Message** : where once can send only **integer type** or a **pointer**
    2. **Mail** : where one can send memory blocks

- Length of queue is declared during creation phase, and is defined **number of items** which will be send via queue.
- Operations within queues are performed in **critical sections** 
- Tasks can **block** on queue sending or receiving data **with** or **without** timeout.

![RTOS](.//Images/CMSIS_OS_Structure.PNG)

- Queue API's
``` C
/* Create Queue */
osMessageId osMessageCreate(const osMessageQDef_t *queue_def, osThreadId thread_id);
/* Put data into Queue */
osStatus osMessagePut(osMessageId queue_id, uint32_t info, uint32_t millisec);
/* Receive data from Queue */
osEvent osMessageGet(osMessageId queue_id, uint32_t millisec);
/* Delete the Queue */
osStatus osMessageDelete(osMessageId queue_id);
/* Read an item from a Queue without removing the item from it */
osEvent osMessagePeek(osMessageQId queue_id, uint32_t millisec);
/* Get the number of messages stored in a queue */
uint32_t osMessageWaitingPeek(osMessageQId queue_id);
/* Get the available space in message queue */
uint32_t osMessageAvailableSpace(osMessageQId queue_id);
```

- If **more** than one tasks waiting for message from the queue, the **higher** priority task waiting data will get it. If the task are waiting has **same** priority, then the task **waited** longer will get it.

- **osEvent** structure
``` C
typedef struct
{
    osStatus status;                // status code, event or error information
    union
    {
        uint32_t v;                 // message as 32-bit value
        void *p;                    // message or mail as void pointer
        int32_t signals;            // signal flags
    }value;
    union
    {
        osMailQId mail_id;          // mail id obtained by \ref osMailCreate
        osMessageQId message_id;    // message id obtained by \ref osMessageCreate
    }def;
}osEvent;
```

- After calling **osMessagePut()** 
    1. If there is no free space in queue, task will be **BLOCKED** for settable time then it will continue(without sending data if queue still full)
    2. If there is free space in queue, task will continue just after sending data.
- After calling **osMessageGet()** 
    1. If any data are not in queue, task is **BLOCKED** for settable time, then it will continue(without data reception if queue is empty)
    2. If the data in queue task will continue just after data reception


### Mail Queue
``` C
/* Create a Mail Queue */
osMailQId osMailCreate(const osMailQDef_t *queue_def, osThreadId thread_id);
/* Put a mail to a Queue */
osStatus osMailPut(osMailQId queue_id, void * mail);
/* Receive mail from a Queue */
osEvent osMessageGet(osMailQId queue_id, uint32_t millisec);
/* Free a memory block from a mail */
osStatus osMailFree(osMailQId queue_id, void * mail);
```
- Queues are takes pointer to data but has to maintain orginial content at its place, but mails are taking data into itself but this takes alot of RAM. There is tradeoff without both of them.

``` C
/* Allocate a memory block from a mail */
void * osMailAlloc(osMailQId queue_id, uint32_t millisec);
/* Allocate mail block from a mail and set memory block to zero */
void * osMailCalloc(osMailQId queue_id, uint32_t millisec);
```
![RTOS](.//Images/CMSIS_OS_Mail_API.PNG)


## Semaphores
- Semaphores are used to **synchronize** tasks with other events in system(especially IRQs)
- Waiting for semaphore is equal to wait() procedure, task is **BLOCKED** state, not taking CPU time
- Semaphore should be created **before** usage
- In FreeRTOS implementation semaphores are based on **queue** mechanism
- In fact those **queues** are with length **1** and data size 0
- There are following types of semaphores in FreeRTOS
    1. **Binary** semaphore : Simple **ON**/**OFF** mechanism
    2. **Counting** semaphore : count multiple **give** and multiple **take**
    3. **Mutex** semaphore : Mutual Exclusion type semaphores
    4. **Recursive** semaphore : In CMSIS OS used only for Mutexes

- **Turn ON** semaphore : **give** a semaphore can be done from other task or interrupt subroutine -> <code>osSemaphoreRelease()</code>
- **Turn OFF** semaphore : **take** a semaphore can be done from the task -> <code>osSemaphoreWait()</code>

- Semaphore Functions :
``` C
/* Semaphore Creation */
osSemaphoreId osSemaphoreCreate(const osSemaphoreDef_t *semaphore_def, int32_t count);

/* Wait for Semaphore Release */
int32_t osSemaphoreWait(osSemaphoreId semaphore_id, uint32_t millisec); // millisec = 0xFFFFFFFF -> forever wait

/* Semaphore Release */
osStatus osSemaphoreRelease(osSemaphoreId semaphore_id);
```
### Counting Semaphores
- They can be seen as **queues** length of **greater** than one. Users of semaphore(Tasks, Interrupt) are not interested in data stored in the queue, they are interested queue item count.
- Typically used for 2 purposes.
    1. **Counting events** : The count value of queue is number of events occured - event has been processed. It desired count value to be **zero** when semaphore created.
    2. **Resource management** : The count value indicates resource **available**. To obtain control of resource, task must first obtain a semaphore.It is desired count value to be **maximum** value when semaphore created.
- API functions are same as Binary semaphores.

## Signals