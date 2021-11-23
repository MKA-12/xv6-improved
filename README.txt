OS Assignment 5 Report
System calls
Waitx system call 
    Updated fields in proc as follows
        Field in proc       State
         ctime               In alloc proc during creation of process
         etime               In exit function before process is exited
         rtime               Total time   
         wtime               updated when process in Runnable state 
         stime               updated when process in Sleeping state
         runtime             updated when process in Running state
Getpinfo system call
    Updated fields for filling proc_stat as follows
    num_run -- updated everytime the process is given the cpu
    current_queue -- during MLFQ scheduling
    ticks[5] -- during MLFQ scheduling
    runtime -- updated when process in Running state
    pid -- when process is created in allocproc 
Setpriority system call
    Implemented by adding an extra field in struct proc priority
    this is updated whenever set_priority is called

Scheduling
    FCFS
    
    Iterate through table and find the process which is RUNNABLE with minimum
pid (!= 1 or 2)
 We ignore 1 or 2 pids in the iteration because they are created at the start, if
we don’t ignore them, they will be run forever. But since iteration through table
is a nested loop, we make sure that we get control back to shell after all the
processes created by first command are run.
 Run that process chosen in first step
 Disabled yield() for FCFS
Chosen pid instead of ctime because two processes can have the same ctime
but pid are always different as kernel does pid++ every time it allocates a
process

    PBS

    Set priority of a new process to default value 60. (Except that init(pid 1) &
sh(pid 2) have priority 0). Each process has priority variable in struct proc
Iterate through table and find the value of highest priority i.e, the minimum
priority value set in struct proc
Iterate again through the table and run all RUNNABLE processes which have
the same priority value in the struct proc as the value found in previous step
The previous step ensures that processes which have the same priority are
executed in round robin fashion

    MLFQ

    Initially set all newly created processes to queue 0. Each process has
current_queue variable in struct proc
Iterate through table and find if any runnable processes in queue 0, if none
then check in queue 1, then in queue 2 and so on
If you find a process say in queue x. Then iterate through the whole table and
run all the RUNNABLE processes which are in queue x
The previous step ensures that all the processes which are in the same
queue are run in round robin fashion
Aging (Starvation Prevention)
this is handled by changing queue if the process waits for a long time

Tests for the algorithms ()
ctime etime totaltime
MLFQ
341 3252 2911
PBS
146 2912 2766
Default
412 3317 2905
FCFS
82 3026 2944
