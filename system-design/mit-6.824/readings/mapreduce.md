# MapReduce

## Abstract

Users specify a map function that processes a kv pair to generate intermediate kv pairs and a reduce function that merges all intermediate values with the same intermediate key. These programs are automatically parallelized and executed on a large cluster of machines.

## Intro

- Google has tonnes of data, so they built MapReduce to deal with it. 
- A functional model (with map and reduce) lets them parallelize large computations easily and use **re-execution as the primary mechanism for fault tolerance.**

## Programming Model

- Takes a set of input kv pairs and produces an output set of kv pairs.
- Map takes an input pair and produces an intermediate kv pair, these are all grouped together and the Reduce function is run over them.

## Implementation

There's a heap of ways to implement it, but at Google they use:

1) Dual-processor x86 Linux machines, 2-4GB of RAM.
2) Commodity networking hardware
3) A cluster has hundreds or thousands of machines, and therefore machine failures are common.
4) Storage is inexpensive hard drives. A distributed file system manages this data. The file system uses replication to provide availability and reliability on unreliable hardware.
5) Users submit jobs to a scheduling system. Each job consists of a set of tasks and is handled by the scheduler.

### Execution Overview

Map invocations are distributed across multiple machines by partioning the input data into splits. These splits can be processed in parallel by diff machines. 

### Master Data structures

One of the copies of the program is the master, with the rest being workers. The master keeps several data structures and is the task that manages things.

### Fault Tolerance

#### Worker Failure

The master pings every worker periodically. If no response is received the master marks the worker as failed. These tasks are then rescheduled. MR is resilient to large-scale worker failures, cos it will just reschedule things but just take a bit longer, all good.

#### Master Failure

It's easy to make the master write periodic checkpoints of the master data structures. If the master task dies, a new copy can be started from the last checkpointed state.

#### Semantics in the presence of failures

Google relies on atomic commits of tasks to produce the same output as you'd get from a non-distrib version.

### Backup Tasks

One of the things that causes delays is a "straggler" which is a machine that takes an unusally long time. MR alleviates this by scheduling backup execution of the remaining in progress tasks when the whole project is almost done.

## Refinements

### Partitioning Function

Data is partitioned across tasks using a particular algo

### Ordering Guarantees

Within a given partition, the intermediate kv pairs are processed in increasing key order

### Conclusions

Restricting the programming model makes it easy to parallelize and distribute computations and make them fault-tolerant. Network bandwidth is a scarce resource, so a number of optimisations are around reducing the amount of data sent around. Redundant execution can be used to reduce the impact of slow machines and handle machine failures and data loss.