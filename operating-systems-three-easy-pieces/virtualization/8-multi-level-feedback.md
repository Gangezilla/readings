# Scheduling: The Multi-Level Feedback Queue (MLFQ)

The MLFQ dates back to 1962 and refinements of it are used in modern OSs. There are two fundamental problems MLFQ tries to address:

1) Optimise turnaround time, which is difficult because we don't know how long a job will run for.
2) Make a system feel responsive to interactive users and minimise response time.

How do we design a scheduler that minimises response time for interactive jobs while also minimising turnaround time without a priori knowledge of job length?

The MLFQ is an excellent example of a system that learns from the past to predict the future

## MLFQ: Basic Rules

An MLFQ has a number of distinct queues which are each assigned a priority level. At any given time, a job that's ready to run is on a single queue. MLFQ uses priorities to decide which job should run at a given time. If more than one job is on a given queue meaning they have the same priority, we just use RR scheduling to run those jobs.

This means we've arrived at two basic rules for MLFQ:

1) If Priority(A) > Priority(B), A run (and B doesn't)
2) If Priority(A) == Priority(B), A & B run in RR.

MLFQ sets priorities of a job based on it's observed behaviour. If a job frequently relinquishes control of the CPU while waiting for input from the keyboard, MLFQ will keep its priority high as this is how an interactive process might behave. If instead a job uses the CPU intensively for long periods of time, MLFQ will reduce its priority. MLFQ thus learns about particular jobs, and will use the history of a job to predict its future behaviour.

## Attempt #1: How to change priority

We must now decide how MLFQ is going to change the priority level of a job (and thus which queue its on) over the lifetime of a job. Here's some more rules:

3) When a job enters the system, it's place at the highest priority (topmost queue)
4a) If a job uses up an entire time slice while running, its priority is reduced (it moves down one queue)
4b) If a job gives up the CPU before the time slice is up, it stays at the same priority level.

### Example 1: A single long-running job

With a single long-running job the job enters in at the highest priority at Q2. Then after a single time-slice of 10ms, it's priority is bumped down to Q1. After running for another time slice, it is bumped down to the lowest priority in Q0 until it's finished.

### Example 2: Along came a short job

In this example there are two jobs: A, which is a long running CPU intensive job and B which is a short running interactive job. Assume A has been running for a while and then B arrives. A is running in the lowest priority queue, Q0. When B arrives, it gets inserted into the highest queue and because it has a short run-time (20ms), B completes before reaching the bottom queue in two time slices, then A resumes running.

This is cool, MLFQ doesn't know if a job will be short or long, it first assumes it might be short. If it's actually a short job, it'll run quickly and complete quickly. If it's not short, it'll move down the queues and eventually RR away in Q0.

### Example 3: What about I/O?

As rule 4b states, if a process gives up the processor before using up its time slice, we keep it at the same priority level. The intent of this is so that if an interactive job, for example, is doing a lot of I/O it will relinquish the CPU before its time slice is complete. In such a case, we don't want to penalize the job and just keep it at the same level.

### Problems with our current MLFQ

There's a few issues here:

1) Starvation: If there are too many interactive jobs, they'll combine to consume all CPU time
2) Someone could rewrite their program to game the scheduler by, say, issuing an I/O operation before the time slice finishes allowing you to remain in the same queue and gain more CPU time.
3) A program may change it's behaviour over time. Like, a program that was CPU bound may become more interactive over time.

## Attempt #2: The priority boost

We can add another rule to periodically boost the priority of all the jobs in the system which will help us guarantee that CPU bound jobs will make some progress.

5) After some time period S, move all jobs in the system to the topmost queue.

This solves two problems:

1) Processes are guaranteed not to starve
2) If a CPU bound job has become interactive the scheduler treats it properly once it has received the priority boost.

Take note, setting S is tricky. If it's too high, long-running jobs can starve; too low, interactive jobs might not get a proper share of the CPU.

## Attempts #3: Better accounting

How do we prevent gaming of our scheduler? The solution is to perform better accounting of CPU time at each level. If we make our scheduler keep track we can handle this better. Let's rewrite rule 4:

4) Once a job uses up its time allotment at a given level, its priority is reduced

## Tuning MLFQ and other issues

How do we parameterise a scheduler? Like, how many queues should there be? How big should a time slice be? How often should we time boost? etc.

## Summary

The MLFQ has multiple levels of queues, and uses feedback to prioritise. There are a few rules to implement:

1) If Priority(A) > Priority(B), A run (B doesn't)
2) If Priority(A) == Priority(B), A & B run in RR fashion using the time slice of the given queue.
3) When a job enters the system, it is placed at the highest priority (topmost queue)
4) Once a job uses up its time allotment at a given level, its priority is reduced.
5) After some time period S, move all the jobs in the system to the topmost queue.