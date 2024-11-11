<h1 align=center>💻 Philosophers</h1>
<p align="center">
  <img src="img/philosophers.png?raw=true" alt="Philosophers Project Image"/>
</p>

## About
>In this project, you will learn the basics of threading a process.
>You will see how to create threads and you will discover mutexes

[Subject Philosophers Project 42](philosophers.pdf)

In this project, philosophers sit around a table, each attempting to eat, sleep and think without starving. The challenge is to prevent any philosopher from dying by using careful thread or process management.

## Features
- **Description**: Philosophers aim to avoid starvation by eating periodically, but they must also avoid holding onto resources indefinitely (to prevent deadlocks).
- **Feature**: Each philosopher runs as a thread or process and must eat every specified interval of time (in milliseconds) to avoid starvation.
- **How to Use**: Run the program with parameters specifying the number of philosophers, time limits for various actions (e.g., time to die, eat, and sleep), and an optional maximum number of cycles.

## Setup
### Mandatory Part
**Clone the Repository**:

```bash
git clone https://github.com/J0hann3/Philosophers.git
cd Philosophers/philo/
make
```
### Bonus Part
**Clone the Repository**:
```bash
git clone https://github.com/J0hann3/Philosophers.git
cd Philosophers/philo_bonus/
make
```

## Usage
- Run the program with the following parameters:
	- number of philosophers: The number of philosophers (and forks) at the table.
	- time to die(in milliseconds): Maximum time a philosopher can go without eating before they die.
	- time to eat(in milliseconds): Time it takes for a philosopher to eat.
	- time to sleep(in milliseconds): Time a philosopher spends sleeping after eating.
	- number of times each philosophers must eat(optional): If specified, the simulation stops when each philosopher has eaten at least this many times.

```bash
./philo 4 410 200 200
```
- The program will print a log of each action (e.g., eating, thinking) and will stop if a philosopher dies from starvation.

## New Notion
### Thread

- Different types of threads:
	- Kernel-level threads: Managed by the OS, with system calls for management (slower due to context switching).
	- User-level threads: Managed by the user and libraries without OS involvement (faster).
	- Hybrid threads: Combine features of both kernel- and user-level threads.

- Thread properties:
	- Threads share memory (instruction, global, and heap sections) within a process but have unique registers, stacks, and counters.
	- Synchronization is essential to avoid race conditions and unexpected behaviors.

- Thread States:
	- Running
	- Ready
	- Blocked

- Compilation:
	- Use thread sanitizer to check for race conditions:
		```bash
		gcc -fsanitize=thread -g multithread.c -lpthread
		```
	- Use Valgrind to detect thread-related issues:
		```bash
		valgrind --tool=helgrind ./a.out  # Checks for race conditions
		valgrind --tool=drd ./a.out       # Detects data races
		```
	- Limit the maximum number of threads with:
		```bash
		ulimit -T
		```
- Thread Limit Warning: Avoid deadlocks by ensuring that threads release mutexes before termination. Prevent cyclic dependencies between threads waiting on each other.

### Mutexes

- Purpose: Mutexes (Mutual Exclusions) are synchronization tools used to prevent multiple threads from simultaneously accessing shared resources. They help avoid race conditions, ensuring only one thread can access a critical section of code at a time.

- Basic Usage:

	- Initialize the mutex before using it:
		```C
		pthread_mutex_t mutex;
		pthread_mutex_init(&mutex, NULL);
		```
	- Lock the mutex before the critical section, which restricts access to other threads:
		```C
		pthread_mutex_lock(&mutex);
		```
	- Execute code within the critical section.
	- Unlock the mutex to allow other threads access:
		```C
		pthread_mutex_unlock(&mutex);
		```
	- Destroy the mutex after all threads are done using it:
		```C
		pthread_mutex_destroy(&mutex);
		```

### Process

- Process properties:
	- Processes communicate using IPC (Inter-Process Communication), which increases the need for system calls compared to threads.
	- Each process has its own stack, heap, and memory map, ensuring isolation.

- Process States:
	- New
	- Ready
	- Running
	- Waiting
	- Terminated
	- Suspended

### Semaphore

- Purpose: Semaphores coordinate access to shared resources, ensuring they are not overused.

- Key Functions:
	- sem_open: Opens or creates a semaphore.
	- sem_close: Closes a semaphore in the current process.
	- sem_post: Increments the semaphore value, signaling resource availability.
	- sem_wait: Decrements the semaphore value, blocking if it is zero.
	- sem_unlink: Removes the semaphore from the system.

- Behavior:
	- Semaphores cannot fall below 0.
	- A semaphore initialized to 1 behaves like a mutex, providing mutual exclusion.

- Common Operations:
	- Initialization: Set the initial value.
	- Post (Increment): Increase the semaphore value to release a resource.
	- Wait (Decrement): Test and potentially block until a resource is available.
	- Destroy: Remove the semaphore after it is no longer needed.
