# Scheduling: Introduction

We haven't yet touched on the high level policies that an OS scheduler employs. 

How should we develop a basic framework for thinking about scheduling policies? What are the key assumptions? What metrics are important? What basic approaches have been used in the earliest of computer systems?

## Workload assumptions

Let's first make some assumptions about the processes running in the system, collectively called the workload. The workload assumptions we make here are mostly unrealistic, which is ok because we'll relax them as we go. We'll eventually spin this into a **fully-operational scheduling discipline**. These are the assumptions we'll make about processes, which are often called **jobs** that run in the system:

1) Each job runs for the same amount of time.
2) All jobs arrive at the same time.
3) Once started, each job runs to completion.
4) All jobs only use the CPU (meaning they perform no I/O)
5) The run-time of each job is known.

These are quite unrealistic, but useful for our purposes.

## Scheduling Metrics

To compare different scheduling policies, we need a **scheduling metric**. We'll have one metric that we use called **turnaround time**. This is defined as the time at which the job completes minus the time at which the job arrived in the system. Turnaround time is a perf metric, and there are others you may be interested in later on.

## First in, First Out (FIFO)

The most basic algo we can implement is a FIFO one. It's good because it's pretty simple and easy to implement. FIFO works fine with each job running for the same length of time. But, it starts to fall apart if relax constraint 1, say, we have 3 jobs and the first of those runs significantly longer than the others. This problem is referred to as the convoy effect where short items get queued behind a resource hog.

## Shortest Job First (SJF)

SJF is quite easy to grasp, as it is what it's called. This works when we have everything arriving at the same time, but if we relax this constraint 2 and get tasks in at different times. If we got the chunky task in first, and then two short tasks then we still have a crappy average turnaround time.

## Shortest Time-to-Completion first (SCTF)

To address this concern, we relax constraint 3. When we're running job A (the long one), and B and C arrive, the scheduler can **preempt** job A. This means that any time a new job arrives, the STCF scheduler determines which of the remaining jobs (incl running ones) has the least time left and schedules that one. It'll then schedule the rest in terms of length of time left.

## A new metric: response time

SCTF works really well if we know job lengths, if jobs only used the CPU, and if our only metric was turnaround time. STCF was used for a number of early batch computing systems, but time-shared machines changed all this where users demanded interactive performance. This leads to a new metric: **response time**. Response time is the time from when the job arrives to the first time it is scheduled. SCTF is crappy in this world, because it would mean you'd type something and then wait 10 seconds to see a response just because the scheduler has another task in front of yours.

## Round Robin (RR)

RR basically runs a job for a **time slice** and then switches to the next job in the queue. It does this repeatedly until the jobs are finished. RR is sometimes called time slicing. Each time slice must be a multiple of the timer-interrupt period, meaning if the interrupt period is 10ms, the time slice could be 10, 20, 30 etc ms.

For example, we have tasks A, B and C which all arrive simultaneously and wish to run for 5 seconds. An SJF scheduler runs each job to completion before running another. RR with a time-slice of 1s cycles through the jobs quickly and it has a significantly slower response time.
SJF: (0 + 5 + 10) / 3 = 5
RR: (0 + 1 + 2) / 3 = 1

Having short time slices makes response time better, but if it's too low you spend too much time context switching and this dominates performance. Deciding on the length of the time slice presents a trade-off to a system designer, making it long enough to **amortize** the cost of switching without making it so long that the system is no longer responsive.

BTW: amortization is a technique to minimise a fixed cost in an operation. For examplke, if context switching takes 1ms and we have time-slices of 10ms, 10% of time is spent context switching and is wasted. If we want to amortize this cost, we can increase the time slice to 100ms meaning 1% of time is spent context-switching. Thus, the cost of time-slicing has been amortized.

However, if we think about RR in terms of turnaround time, it's pretty bad. This makes sense as RR basically stretches out each job as long as it can. Any algo that's fair (evenly distributes CPU) like RR will perform poorly on turnaround time. This is a trade-off in systems design.

## Incorporating I/O

The scheduler needs to make decisions while an I/O operation is running. As the CPU is blocked while we're waiting to pull data from disk, we should probably schedule something else to use the CPU in the meantime.

For example, let's assume we have two jobs that each need 50ms of CPU time. A runs for 10ms and then issues an I/O request (that takes 10ms) whereas B just hits the CPU for 50ms and performs no I/O. We can do this by treating each 10ms sub-job of A as an independent job. When the system starts it's easier to schedule a 10ms A over a 50ms B. Thus when the first sub-job of A is done, we preempt B and run it for 10ms which allows us some overlap where the CPU can be used by another process while we wait for the I/O to complete. A scheduler can treat each CPU burst as a job which allows processes that are 'interactive' to be run frequently and while they're performing I/O other CPU-intensive jobs run.

## No more oracle

We still need to relax our final restraint of knowing how long a task will run for, which we will look at in the next chapter with something called a **multi-level feedback queue**.


