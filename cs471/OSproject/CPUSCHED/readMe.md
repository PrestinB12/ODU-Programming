This is the directory for the CPU Scheduling

# Overview

Problem 1: CPU Scheduling
This part of the projects simulates a CPU scheduler. Since it is a simulation, there are no
real processes to be scheduled. Instead, you simulate the arrival of new processes.
Whenever a new process arrives (in simulation) into the ready queue, the CPU scheduler
is invoked. Each simulated process has the following parameters: <Process ID, Arrival
time, Priority, CPU burst units>. Each of these is an integer parameter.
For example, if a process <100, 20, 2> is read by your simulator, it means a new process
P arrived at the system at simulation time 100, it executes for a CPU burst time of 20
units before finishing and leaving the system, and its priority is 2. At the time of
invocation of the scheduler, the user indicates the type of scheduling to be enforced. You
are required to implement the following three scheduling types:
1. FIFO
2. SJF without preemption
3. Priority with preemption
Each run will handle scheduling of 500 (simulated) processes. In other words, as soon as
the number of processes that have completed CPU execution reaches 500, you can stop
running the program and print the following statistics. All times are expressed in terms
of CPU burst units. So they are not actual elapsed time (in msec) but simulated times.
Statistics for the Run
Number of processes: 500
Total elapsed time (for the scheduler):
Throughput (Number of processes executed in one unit of CPU burst time):
CPU utilization:
Average waiting time (in CPU burst times):
Average turnaround time (in CPU burst times): Average response
time (in CPU burst times):
Since there are only 500 processes, it may be easy to read all 500 processes data first
(from datafile1-txt), and store the records in a queue in the program, and then process
them. This is an easy way to do it. But you can choose any method you like.
The following formulas will be utilized for calculating Problem 1:
Total elapsed time: The amount of time from initiation to termination of the application.
Throughput (Number of processes executed in one unit of CPU burst time) so you can calculate it using the formula: Total burst
time( It is the sum of all given burst length) / Total number of processes
CPU Utilization: The CPU Utilization measures the percentage of the time that the CPU is performing work so you can calculate it
using the formula: Total Burst Time/ Total elapsed time
Average waiting time: total waiting time / Number of processes
Turnaround time = Burst time + Waiting time
or
Turnaround time = Exit time - Arrival time
Average turnaround time: Total turnaround time / No of processes
Response time = Time at which the process gets the CPU for the first time - Arrival time
Average response time: Total response time / No of processes

## Command in Terminal to operate the CPU Scheduler
To compile run the command in the directory CPUSCHED: g++ prime.cpp -o prime


To run the program (After Compilation): ./prime
