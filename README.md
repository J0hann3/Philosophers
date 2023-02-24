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

Static element not safe to use with thread

Compilation:
-> gcc -fsanitize=thread -g multithread.c -lpthread
valgrind --tool=helgrind ./a.out ->error of thread Helgrind
valgrind --tool=drd ./a.out ->error of thread DRD
ulimit -T ->limit thread

PTHREAD_THREADS_MAX -> number of thread max
ATTENTION: DEAD LOCK -> kill a thread before unlock a mutex
					-> wait for a mutex to unlock that also wait for a other mutex -> infini
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

TEST

5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die


1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats		-> need to implement that
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)