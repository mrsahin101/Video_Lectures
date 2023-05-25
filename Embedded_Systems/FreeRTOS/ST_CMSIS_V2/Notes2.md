## Task Intro

### What is Task?
- It is **C** function
- It can be used to **generate** any number of tasks(separate instances)
- It has its own part of stack(each instance) and priority
- It can be in one of 4 states(**RUNNING**, **BLOCKED**, **SUSPENDED**, **READY**)
- It is created and deleted by CMSIS API Function below
    1. **osThreadCreate()** and **osThreadDelete()** -> CMSIS_OS v1.x
    2. **osThreadNew()** and **osThreadTerminate()** -> CMSIS_OS v2.x

- Example body :
``` C
void TaskName(void *arguments)
{
    /* Initializing code 
     * ...
     * ...
     */

    /* Endless Loop */
    for(;;)
    {
        /* Task code
         * ...
         * ...
         */
    }
    /* Should never reach here */
}
```
- A task consist three parts
    1. **Program Code** (ROM): 
    2. **A stack** : All local variables are stored here
    3. **TCB** : Data structure assigned to taask when its created, Contains information of task.(stack pointer, task priority, current status.. etc)

- The process of saving the context of task that being suspended and restoring the context of task being resumed is called **context-switching**

![RTOS](.//Images/CMSIS_OS_TCB.PNG)

### Tasks States
- **READY** : Task is ready to be executed but is not currently executing because a different task with equal or higher priority is running
- **RUNNING** : Task is actualy running(only once can be in this state at the moment)
- **BLOCKED** : Task is waiting for either a temporal or an external external event
- **SUSPENDED** : Task not available for scheduling, but still being kept in memory

![RTOS](.//Images/CMSIS_OS_TaskStates.PNG)
![RTOS](.//Images/CMSIS_OS_ThreadStates.PNG)
![RTOS](.//Images/CMSIS_OS_osThreadAttr_t.PNG)
![RTOS](.//Images/CMSIS_OS_TaskLists.PNG)
- Since running task is only 1, that task id stored in <code>pxCurrentTCB</code> variable.
- Each task has assigned a priority between 0 and MAX_PRIORTY - 1
- The scheduelr activates the task that has higher priority. Lower number Lower priority in FreeRTOS
![RTOS](.//Images/CMSIS_OS_Priority_Table2.PNG)

- **CMSIS OS Task API**
``` C
/* Task Handle definition */
osThreadId_t Task1Handle;
/* Create task */
osThreadId_t osThreadNew(osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);
/* Delete task */
osStatus_t osThreadTerminate(osThreadId_t thread_id); // osThreadTerminate(NULL) for terminating currently running thread
/* Get currently running task ID */
osThreadId_t osThreadGetId(void);
/* Get task name */
const char *osThreadGetName(osThreadId_t thread_id);

/* Yield Task */
osStatus_t osThreadYield(void);
/* Resume Task */
osStatus_t osThraedResume(osThreadId_t thread_id);
/* Check state of task */
osThreadState_t osThreadGetState(osThreadId_t thread_id);
/* Suspend task */
osStatus_t osThreadSuspend(osThraedId_t thread_id);
/* Resume all tasks */
osStatus_t osThreadResumeAll(void);
/* Suspend all tasks */
osStatus_t osThreadSuspendAll(void);


/* Get stack size of a Task */
uint32_t osThreadGetStackSize(osThreadId_t thread_id);
/* Get available stack space of a thread based on stack watermark */
uint32_t osThreadGetStackSpace(osThreadId_t thread_id);
/* Change a priority of a task */
osStatus_t osThreadSetPriority(osThreadId_t thread_id, osPriority_t priority);
/* Get a current priority of a task */
osPriority_t osThreadGetPriority(osThreadId_t thread_id);
/* Delete of currently running task */
__NO_RETURN void osThreadExit(void);
/* Delete of a task */
osStatus_t osThreadTerminate(osThreadId_t thread_id);
```
![RTOS](.//Images/CMSIS_OS_Thread_API.PNG)

### osDelay() and osDelayUntil() functions
- **osDelay()** : waits for specified time
- **osDelayUntil()** : it waits from given referencee point to specified amount of time
- CMSIS API
``` C
/* Delay Functions */
osStatus_t osDelay(uint32_t millisec);
/* Delay function which measure time from which is delay measured */
osStatus_t osDelayUntil(uint32_t millisec);
```

- Don't use **HAL_Delay()** because it waste CPU time.

- **osThreadYield()** function moves task from **RUN** to **READY** state. If we have same priority task waiting, that waiting function will execute, otherwise if we dont have higher or same priority tasks waiting, same task which called **osThreadYield()** will execute again.

- Memory allocated by the task code is not automatically freed and should be freed before the task is deleted, TCB and its original stack are freed by **IDLE** task

## Inter-Task Communications
- **Queues** : Allows to pass more information between the tasks. Suspend task if tries to **put**  to full queue or **get** from empty one
- **Semaphores** : are used to communication between the tasks without specifying the ID of the thread who can accept it. It allows counting multiple events and can be accepted by many threads.
- **Event Flags** : are used to synchronize task with multiple events(OR-ed together). There could be 8 or 24 bit value used here. 
- **Direct Task Notifications** : are used to precise communication between the tasks. It is necessary to specify within signal thread id.
- **Mutexes** : are used to guard the shared resources. It must be taken and released always in that order by each task that uses the shared resource.

## **QUEUES**
- Queues are pipes to transfer data between tasks in FreeRTOS
- By default queue is behaving as FIFO(First In-First Out), can be redefined to perform as LIFO(Last In-First Out) structure by using **xQueueSendToFront()** FreeRTOS native API function(Not available in CMSIS OS)
- All data send by queue must be same type, declared during Queue creation phase. It can be simple variable or structure
- Within CMSIS OS there are two types of queues.
    1. **Message** : where one can send only integer type or a pointer
    2. **Mail** : where one can send memory blocks

- Length of the queue is declared during **creation phase** and is defined as number of items which will be send via queue.
- Operation within queues are performed in **critical sections**
- Tasks can block on queue sending or receiving data with timeout or infinitely
- If **multiple tasks** are blocked waiting for receiving/sending data from/to queue then only one task with **highest priority** will be unblocked what a data/space is available. If both tasks have equal priority the task has been waiting the **longest time** will be unblocked.
- To create a Queue :
``` C
/* Create a Queue */
const osMessageQueueAttr_t attr = { .name = "Queue1"};
osMessageQueueId_t osMessageQueueNew(uint32_t msg_cnt, uint32_t msg_size, const osMessageQueueAttr_t *attr);

/* Delete a Queue */
osStatus_t osMessageQueueDelete(osMessageQueueId_t queue_id);

/* Put Data into Queue */
osStatus_t osMessageQueuePut(osMessageQueueId_t queue_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout); // msg_prio not used

/* Receive Data from Queue */
osStatus_t osMessageQueueGet(osMessageQueueId_t queue_id, const void *msg_ptr, uint8_t *msg_prio, uint32_t timeout); // msg_prio set to NULL

/* Reset a message queue to initial empty state */
osStatus_t osMessageQueueReset(osMessageQueueId_t queue_id);

/* Get the number of messages stored in a queue */
uint32_t osMessageQueueGetCount(osMessageQueueId_t queue_id);

/* Get available space in a message queue */
uint32_t osMessageQueueGetSpace(osMessageQueueId_t queue_id);
``` 


![RTOS](.//Images/CMSIS_OS_osMessageQueueAttr_t.PNG)
![RTOS](.//Images/CMSIS_OS_Queue_Management.PNG)
![RTOS](.//Images/CMSIS_OS_Queue_API.PNG)


## **Semaphores**
- Semaphores are used to **synchronize** tasks with other events in the system(Especially IRQs)
- Waiting for semaphore is equal to wait() procedure, task is in blocked state not taking CPU time
- Semaphore should be created **before** usage
- In FreeRTOS implementation semaphores are based on **queue mechanism**
- In fact those are queues with length **1** and data size **0**
- There are following types of semaphores in FreeRTOS  :
    1. **Binary** semaphores : Simple **ON/OFF** mechanism
    2. **Counting** semaphores : Counts multiple **give** and multiple **take**
    3. **Mutex** : Mutual exclusion type semaphores
    4. **Recursive** : Usd only for Mutexes

- **Turn ON** semaphore = **give** a semaphore can be done from other task or from interrupt subroutine
- **Turn OFF** semaphore = **take** a semaphore can be done from the task. 

![RTOS](.//Images/CMSIS_OS_Semaphores.PNG)
![RTOS](.//Images/CMSIS_OS_Semaphore_API.PNG)
![RTOS](.//Images/CMSIS_OS_osSemaphoreAttr_t.PNG)

- Semaphore CMSIS V2 API
``` C
/* Semaphore creation */
const osSemaphoreAttr_t Sem_attr = {.name = "Sem_name"};
osSemaphoreId_t soSemaphoreNew(uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *Sem_attr);

/* Semaphore delete */
osStatus_t osSemaphoreDelete(osSemaphoreId_t semaphore_id);
 
 /* Wait for Semaphore release(acquire semaphore) */
 osStatus_t osSemaphoreAcquire(osSemaphoreId_t semaphore_id, uint32_t millisec); // 0-> no wait, >0-> delay in ms, 0xFFFFFFFF -> forever
 /* Semaphore release */
 osStatus_t osSemaphoreRelease(osSemaphoreId_t semaphore_id);
 ```

 ### Counting Semaphores
 - Counting semaphores can be seen as a queues of **length of greater than one**. Users of the semaphore(Tasks, IRQ) are **not interested int data** that is stored in the queue, just whether the queue is empty or not
 - Counting semaphores are typically used for two purposes.
    1. **Counting Events** : An event handler will **give** a semaphore each time an event occurs. Handler will **take** a semaphore each time it process event. The count value is the difference between the number of events that have occured and that have been processed.
    2. **Resource Management** : The count value indicates the number of resources available. To obtain control of a resource a task must first **obtain** semaphore, decrementing count value. When count value reaches zero, there are no **free** resources. When a task finishes with resource it **releases**(**give**) semaphore back incrementing the semaphore count. It is important to set count value to maximum count value when semaphore **created**

- Counting semaphore API is same as binary, but parameters are chages


## Event FLAGS
- They called Event Groups in FreeRTOS API. They are not available in CMSIS V1.
- It allows a task wait(in **BLOCKED** state) for combination of **one or more events** to **occur**
- It unblocks all the tasks that are waiting for the same event, combination of events, when the event occurs
- Event group functionality is **optional** and requires to add **event_groups.c** and **event_groups.h** files to the project
- It allows to **reduce** RAM usage by replacing various combination of semaphores
- It allows to use **broadcasting** mechanism within OS
- Event groups can be **set/clear** from other tasks or interrupt procedures

![RTOS](.//Images/CMSIS_OS_Event_Group.PNG)

- Most significant 8-bits are control bits, assigned for control.

![RTOS](.//Images/CMSIS_OS_Event_Group_API.PNG)
![RTOS](.//Images/CMSIS_OS_osEventFlagsAttr_t.PNG)

- Event Flags CMSIS OS API Functions
``` C
/* Creating Event Flags */
const osEventFlagsAttr_t Flags_attr = {.name = "name"};
osEventFlagsId_t osEventFlagsNew(const osEventFlagsAttr_t *attr);
/* Delete Event Flags */
osStatus_t osEventFlagsDelete(osEventFlagsId_t ef_id);
/* set bit mas within Event Flags */
uint32_t osEventFlagsSet(osEventFlagsId_t ef_id, uint32_t flags);
/* Event Flags bit mas clear */
uint32_t osEventFlagsClear(osEventFlagsId_t ef_id, uint32_t flags);
/* Wait for particular bit-mask within Event Flags */
uint32_t osEventFlagsWait(osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);
```

- To use event flags, we must enable Timers, because it uses timer service tasks to do operations. This Deamon task also known as **AGENT** task. Originally it was used to execute software timers **callback** functions, now it is used by other components too.
- Its priority is set within <code>configTIMER_TASK_PRIORITY</code>, Its stack size is set within <code>configTIMER_TASK_STACK_DEPTH</code>. It is necessary to define <code>configUSE_TIMERS</code> and <code>INCLUDE_xTimerPendFunctionCall</code> within FreeRTOSConfig.h file to generate this function.

## **Direct Task Notification** (**Thread FLAGS**)
- Each FreeRTOS task/thread has 31-bit notification value(MSB is not used). An task notification is **event sent directly** to a task that can **unblock** the receiving task
- Task notification can be used where previously it would have been necessary to create separate **queue**, **binary semaphore**, **counting semaphore** or **event group**. Unblocking RTOS task with direct notification is **%45 faster** and **uses less RAM** than unblocking a task with binary seamphore
- Task notification has RAM footprint and speed advantage over other features. But it has some limitations
- Task notification can only be used to notify **only one Task at a time**
- If Task notification is used in place of message queue then the receiving task is set to **BLOCKED** state. However sending task **cannot wait** in **BLOCKED** state for send to complete.

- Thread Flags are used to trigger execution states **between threads** and from **IRQ to thread**
- The maximum number of Thread Flags is defined in **cmsis_os.h** file. It is set to 24. 
- Signals(Task notifications) cannot be used :
    1. **To send an event or data to IRQ**
    2. **To communicate with more than one task(thread)**
    3. **To buffer multiple data items**
- CMSIS API Functions
``` C
/* Set specified flags of an active thread */
uint32_t osThreadFlagsSet(osThreadId_t thread_id, uint32_t signals);
/* Wait for one or more flags for running thread.*/
uint32_t osThreadFlagsWait(uint32_t signals, uint32_t options, uint32_t millisec); 
```

![RTOS](.//Images/CMSIS_OS_Thread_Flags_API.PNG)


## Resource Managements
- **Critical Sections** : When it is necessary to **block small piece of code** inside the task **against** **task switching** or **interrupts**. Starts with **taskENTER_CRITICAL()** and should end with macro **taskEXIT_CRITICAL()**
- Critical sections mechanism allows to block all the interrupts(Operating System interrupts) during sensetive/atomic operation execution(like operations on queues)

- **Suspending the Scheduler** : When waiting on interrupt and no task switching allowed. **vTaskSuspendAll()** block context switching with interrupts enabled. Unblock the tasks is done by **xTaskResumeAll()** function.

- It is not allowed to run **any** FreeRTOS API function when scheduler is suspended.

- **GateKeeper task** 
    1. Dedicated procedure managing selected resource(For example : peripheral)
    2. No risk of priority inversion and deadlock
    3. It has ownership of a resource and can access it directly
    4. Other tasks can access protected resource indirectly via gatekeeper task

- **Mutexes** 
    1. Kind of binary semaphore shared between tasks
    2. Require set <code>configUSE_MUTEXES</code> at **1** in FreeRTOSConfig.h

- Gatekeeper task is task being the only allowed to access certain resources, It owns the resource and only it can access it directly, other tasks can do it indirectly by using services provided by the gatekeepr task.
- **There is nothing physically preventing other tasks from accessing the resource**
- It spends most of the time in **BLOCKED** state for waiting for the request on the owned resources
- It is up to the designer to set the priority of the gatekeepr task and its name
- It is providing clean method to implement mutual exclusion without risk of priority inversion or deadlock


## **MUTEXES**
- Mutex is a **binary semaphore** that include a priority inheritance mechanism
    1. Binary semaphore is **better choice** for implementing synchronization(between tasks or between tasks and an interrupt)
    2. Mutex is the better choice for implementing simple mutual exclusion

- Used to guard access to limited resource. Works very similiar as semaphores

- When used for mutual exclusion the mutex acts like **a token** that is used to guard a resource
    1. When a task wishes to acces the resource it must first **obtain**(**take**) the token.
    2. When it has finished with the resource it must **give** the token back
    3. In case of <code>recursive mutex</code> it should be given as many times as it was successfully taken(like counting semaphores) to release it for another task.

- Mutexes use the **same** access API functions as semaphores
- The block time indicates the maximum number of ticks that a task should enter the **BLOCKED** state when attempting to **take** a mutex if the mutex is not available immediately
- Unlike binary semaphores mutexes employ <code>priority inheritance</code>. This means that if a **higher priority** task is blocked while attempting to obtain a mutex(token) that is currently held by a lower priority task, then the priority of the task holding token is **temporarily** raised to that of the blocked task.
- A task must not be deleted while it is controlling a Mutex. Othwersie, the mutex resource will be **locked out** to all other tasks
- Mutex management functions **cannot** be called from IRQ

### Priority Inversion
- This is the situation where a higher priority task is **waiting** for a lower priority task to give a control of the mutex and lower priority task is **not able to execute**
- **Priority inheritance** mechanism minimizes the negative effects of priority inversion but it is complicating system timing analysis and it is **not a good practice** to rely on it for correct system operation.

### Deadlock(Deadly Embrace)
- It occurs when two tasks cannot work because they are **both waiting** for a resource held by **each other**
- The best way to avoid deadlock is to consider them at **design time** and design the system to be sure that the deadlock cannot occur.

![RTOS](.//Images/CMSIS_OS_osMutexAttr_t.PNG)

- CMSIS API Functions
``` C
/* Mutex Creation */
const osMutexAttr_t attr = {.name = "name"};
osMutexId_t osMutexNew(const osMutexAttr_t *attr);
/* Wait for Mutex release(Mutex Acquire) */
osStatus_t osMutexAcquire(osMutexId_t mutex_id, uint32_t millisec);
/* Mutex release */
osStatus_t osMutexRelease(osMutexId_t mutex_id);
```

![RTOS](.//Images/CMSIS_OS_Mutex_API.PNG)
