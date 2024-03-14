# WHAT I LEARNED ? 
- Operating Systems are just piece of software component runs on computer. 
- Operating Systems abstracts hardware details from user and provides interface to user. User doesnt have to deal with low level implementation details. It has onion like structure
- Operating system is launched via bootloader from non volatile secondary storage unit.
- Computer programs are divided into processes. Each process lives its in own world. It has its own address space. 
- MMU(Memory Management unit) translated desired address from logical address to physical address for process. Basically kernel translate logical address for physical address.
- Memory organized in segments and pages. Kernel does this translation for processes.
- Process contains threads for sub units for desired jobs. 
- Threads share same address spaces within same process threads.
- Operating systems are provide services which could be runing in background. 