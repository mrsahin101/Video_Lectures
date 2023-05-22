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

## osDelay() and osDelayUntil() functions
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

## QUEUES
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
