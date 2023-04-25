# NOTES

- **Operating System** is middle-man(Operating System is software itself.) between **hardware** and **Application** software.

- Operating System provides **API**(Application Programming Interface), reduce hardware complexity and gives simple interface to application layer.

- Operating System has direct access to hardware.

- Manage the hardware according to predefined rules.

- Offers Multi-tasking, Resources, Data Management. 

- Operating System can be **GPOS(General-Purpose Operating System)** or **RTOS(Real-Time Operating System)**

## RTOS -> REAL TIME OPERATING SYSTEM
- Designed specially to Run Application with **very precise timing** and **High degree of Reliability**. 

- Real-Time means : Works with time constraint. It should have deadline. 

- For Real-time System, **A late answer is wrong answer**. Real-time performance does not mean faster operation.

- Real-Time Systems :
    1. **Hard Real-time Systems**   -> This systems must meet deadline %100. Safety-Critical Applications. Missing Deadline result in **fatal** consequences.
    2. **Soft Real-time Systems**   -> This systems could miss deadline. Entertaiment Systems.Missing Deadline **Doesn't** result fatal consequences.

## RTOS Characteristics.
- Single Tasking    -> Single CPU, NO-RTOS, Single **while(1)** loop. Classic way, Difficult when large programs.Poor Real-time Behaviour
- Multi-Tasking     -> Single CPU, Multi-Task.Multiple **while(1)** loops

- Scheduler(Kernel) is managing the multi-tasking. 

- Super-Loop only could be stoped by interrupts.

## Scheduling
- Scheduler must know 
    1. Number of tasks
    2. Resource Requirments
    3. Execution time
    4. Deadlines
    5. Priority

- Hardware Interrupts are always highest priority.

- In other words, Operating Systems provides API for Application layer. It hides hardware complexity from Application layer.