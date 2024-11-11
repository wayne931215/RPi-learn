# RPi-learn

## week 1

Q1:What is the memory space of a process ? How is the memory layout when a process is created? What is stack and heap memory and compare their difference ?

The memory space of a process is the virtual memory address assigned by OS.

Memory layout from top to down:
stack->heap->BSS->data->text

Stack memory v.s Heap memory<br>
Stack memory is used for function calls and local variables and grows downwards.
Heap Memory is used for dynamincally allocated variables and grows upwards.
Stack memory is allocated automatically by compiler while Heap memory is allocated manually by programmers.

Q2:Where is the heap, stack, data, and text segment? Which segments can a program write to? What are invalid memory addresses?

(high memoery address) stack->heap->data->text (low memory address)

A program can write to heap, stack, data segments.

An 'Invalid Memory Address' refers to a situation that a pointer points to a memory location that has been destroyed or is no longer valid.

Q3:What are file descriptors?

When we open an existing file, the kernel returns a file descriptor to the process. To the kernel, all open files are referred to by File Descriptors. A file descriptor is a pointer that points to an entry in the file table, and the entry on the file table points to inode table. Inode table stores the memory location of files in the computer.

Q4:What is the int status pointer passed into wait? When does wait fail?
The information of how child process terminated will be stored in the memory address pointed by status pointer.(e.g. WIFEXITED(*status)) It can also be NULL if we don't care about the return status.
Wait fails if
(1) The process with pid does not exist or is not a child of the calling process.
(2) The function is interrupted by a signal.

Q5:Can one process alter another processes memory through normal means? Why?

No. Each process has its own virtual memory space and cannot directly access the memory of another process.