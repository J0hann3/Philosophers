# Philosophers

THREAD

Different types of threads:

- Kernel-level threads -> handle by the OS, managed by kernel + need call system -> slower
- User-level threads -> managed by the users, kernel does not have the info + use librairy, not system calls ->faster
- Hybrid threads

Thread properties:
- Threads shares instruction, global, and heap regions. However, it has its register and stack(pile) and counter.
- share only with theeir peer thread within a process
- Threads need to be synchronized in order to avoid unexpected scenarios

States of thread:
- Running
- Ready
- Blocked

Compilation:
-> gcc multithread.c -lpthread

PTHREAD_THREADS_MAX -> number of thread max
ATTENTION: DEAD LOCK -> kill a thread before unlock a mutex

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

fork() -> create process -> separate system calls


context switch ??
data segment : which variables are contain in it ??
concurrency or parallelism CPU
mutex ??