# FREERTOS Simplified : A Beginner's Guide to Develop and Debug FreeRTOS Application

## Why RTOS ? What is this?
- RTOS : OS specialized for Real-Time Operations. 
- We are mostly using Fixed Priority Preemptive scheduling.
- To use time slicing macro below should be defined
``` C
#define configUSE_TIME_SLICING 1
```

## RTOS Firmware Design
- Task Grouping
- Task Prioritization
- Timing Analysis
- Intertask Communication
- Task Synchronization

- **Priority Inversion** : Lower priority task preempting higher priority task.
- **Priority Inheritance** : When lower priority task takes the mutex, It gets to higher priority task blocked on resources(mutex)
- **Task starvation** : High priority task starving(not letting to run) low priority task
- **Deadlock** : Both task signals from each other and both stays in blocked state.
- **RaceCondition** : When 2 or more task try to access shared data and change it at same time
