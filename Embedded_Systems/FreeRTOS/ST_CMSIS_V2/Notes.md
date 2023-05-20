# **FreeRTOS CMSIS_V2 API**

## Introduction
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
    