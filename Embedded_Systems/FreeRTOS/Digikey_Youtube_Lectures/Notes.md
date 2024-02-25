# NOTES

- General Purpose OS(GPOS) -> Scheduler is **non-deterministic**.
- Real-Time OS(RTOS) -> Scheduler is **deterministic**

- Some RTOS provide device drives, and some RTOS provide just scheduler. For those which provides only scheduler, you need to write your own device drivers.

- **Super-Loop** : SETUP -> 
                            Loop:
                                Task1
                                Task2
                                Task3

- Super-Loop : Easy to implement, Has very little Overhead, great when only handfull of tasks.  Easier to debug.
- When you need to meet deadlines below **ms**, interrupts are best way to go.

- **RTOS** : SETUP  ->
            TASK1, TASK2, TASK3;

- **Task** : set of program instructions loaded in memory.
- **Thread** : unit of CPU utilization with its own program counter and stack.
- **Process** : instance of a computer program.

- A process usualy have 1 or more threads and those threads has some tasks to accomplish desired control. Threads within process, share resources like heap memory, can pass resources to each other. RTOS usually handles 1 process, while GPOS can handle many process together.
- In FREE-RTOS task is used something closer to thread. Interrupts still works, depending on prioritization.

- 