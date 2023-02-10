# Philosophers

THREAD

Different types of threads:

- Kernel-level threads -> handle by the OS, managed by kernel + need call system -> slower
- User-level threads -> managed by the users, kernel does not have the info + use librairy, not system calls ->faster
- Hybrid threads

Thread properties:
- Threads shares instruction, global, and heap regions. However, it has its register and stack and counter.

States of thread:
- Running
- Ready
- Blocked

PROCESS

Process properties :
- Processes use the IPC(Inter-Process Communication) mechanism for communication that significantly increases the number of system calls.
- A process has its stack, heap memory with memory, and data map

States of Process:
- New
- Ready
- Running
- Waiting
- Terminated
- Suspended

Multitasking:
- Clone
- Child process
- Parent process (main process)

fork() -> create process


context switch ??