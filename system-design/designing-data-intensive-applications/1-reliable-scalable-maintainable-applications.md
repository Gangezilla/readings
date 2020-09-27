# Reliable, Scalable and Maintainable Applications

Many apps are *data-intensive*, as opposed to *compute-intensive*. Raw CPU power is rarely a limiting factor, its usually the amount, complexity and rate of change of the data. Many apps need to:

- Store data so that they, or another app, can find it later (databases)
- Remember the result of an expensive operation to speed up reads (caches)
- Allow users to search data by keyword or filter it in various ways (search indexes)
- Send a message to another process to be handled asynchronously (stream processing)
- Periodically crunch a large amount of accumulated data (batch processing)

## Thinking about data systems

We lump data systems like databases, queues, caches etc into one category (although they're very different!) because:

- Many new tools have been released and they're optimised for a variety of different use cases and they don't fit neatly into traditional categories.
- Many apps have such wide-ranging requirements that a single tool can't meet all of its data processing and storage needs. This means the work is broken down into tasks that can be performed efficiently on a single tool, and all of the tools are stitched together using code.

When you combine several tools, the service's API typically hides this implementation. You've essentially created a new data-system from smaller, general-purpose components. When you're developing a new system, you typically think about it in terms of reliability, scalability and maintainability.

## Reliability

Reliability essentially means that a service will continue to work correctly even when things go wrong. Things that can go wrong are called *faults* and systems that cope with them are called *fault-tolerant* or *resilient*. Note, it's unrealistic (and expensive) to account for every kind of fault, so it only makes sense to talk about tolerating *certain types* of faults.

BTW, faults and failures are different things. A failure is when the system as a whole stops providing the required service, whereas a fault is one component deviating from its spec. You can't reduce probability of a fault happening to zero, so we should design systems to allow faults to prevent failures from occuring.

### Hardware Faults

Hardware faults are things like hard disks crashing, RAM becoming faulty, power grids blacking out etc. These happen all the time when you have a lot of machines. Our first response is to add redundancy, so hard disks in RAID configuration, hot-swappable CPUs... When one component dies, the redundant component takes over.

In cloud systems, its common for VM instances to suddenly become unavailable. This means theres a move towards systems that can tolerate the loss of entire machines. These have operational advantages: a single-server system requires planned downtime if you need to reboot, whereas a system that can tolerate machine failure can be patched one node at a time without the downtime of the entire system.

### Software Errors

Another class of fault is a systematic failure in the system. These are harder to anticipate, as they're correlated across nodes and cause more failures than hardware faults. These bugs often lie dormant for ages until an unusual set of circumstances triggers them. There's no quick solution to this, but there's lots of small things. 

- Carefully thinking about assuptions and interactions in the system
- Thorough testing
- Process isolation
- Allowing processes to crash and restart
- Measuring, monitoring and analyzing system behavior in production

### Human Errors

Humans design, build and run software systems. How do we make our systems reliable?

- Design systems in a way that minimizes opportunities for error. Well designed abstractions, APIs and admin interfaces make it easy to do the right thing. If the interfaces are too restrictive, people will work around them so be careful.
- Decouple the places where people make the most mistakes from the places where they can cause failures In particular, provide fully feature non-production sandbox environments that have real data so that real users aren't affected.
- Test thoroughly at all levels.
- Allow quick and easy recovery from human errors.
- Set up detailed and clear monitoring
- Implement good management practices and training

## Scalability

Scalability is the term we use to describe a system's ability to cope with increased load. When discussing scalability we should be considering questions like "if the system grows in a particular way, what are our options for coping with the growth?" and "how can we add computing resources to handle the additional load?"

### Describing load

Load can be described with a few numbers which we call *load parameters*. The best choice of parameter depends on your architecture. This might be:

- requests per second to a web server
- the ratio of reads to writes in a database
- the number of active users in a chat room
- the hit rate on a cache etc etc...

### Describing performance

Once you've described the load you can investigate what happens when that load increases.

- When you increase a load parameter and keep the system resources (CPU, memory, network bandwidth) unchanged, how is the performance of your system affected?
- When you increase a load parameter, how much do you need to increase the resources if you want to keep performance unchanged?

Both questions require perf numbers, so lets look at describing the perf of a system.

In a batch processing system such as Hadoop, we usually care about *throughput*, the number of records we can process per second. In online systems, you're usually more interested in the *response time*.

Because you can make a request multiple times, you should think about response times not as a single number, but as a *distribution* of values that you can measure. Even in a situation where you'd think all requests should take the same time you get variation, like, random additional latency could be introduced by a context switch to a background process, the loss of a network packet and TCP retransmission, a garbage collection pause, a page fault forcing a read from disk, mechanical vibrations in the server rack or many other causes. Because of this you'll often report the *average* response time of a service.

However, the mean isn't a very good metric if you want to know your "typical" response time, because it doesn't tell you how many users actually experienced that delay. Because of this it's better to use *percentiles*. If you take your list of response times and sort it from fastest to slowest, then the *median* is the halfway point. This makes the median a good metric if you want to know how long users typically have to wait. The median is also known as the *50th percentile*, or *p50*. To figure out how bad your outliers are, you should get your *p95, p99, and p999* percentile times as well.

High percentiles, or *tail latencies* are important because they directly affect user's experience of the service. Percentiles are often used in *service level objectives* and *service level agreements* (SLOs and SLAs) which are contracts that define the expected perf and availability of a service.

### Approaches for coping with load

An architecture thats appropriate for one level of load is unlikely to cope with 10 times that load. It's likely that you'll have to rethink your architecture on every magnitude load increase.

- *Scaling up/vertical scaling* means to move to a more powerful machine
- *Scaling out/horizontal scaling* means to distribute the load across multiple shared machines.
- Distributing load across multiple machines is also known as a shared-nothing service.
- *Elastic* systems are ones that can automatically add resources when they detect a load increase. This can be useful if load is highly unpredictable.

Distributing stateless systems is pretty easy, but stateful data systems can introduce a lot of complexity. The architecture of systems that operate at scale is usually highly specific to the app. The problem may be the volume of reads, the volume of writes, the volume of data, the complexity of the data, response time requirements.

## Maintainability

### Operability

Make it easy for operations teams to keep the system running smoothly. Operations teams are vital to keep software running smoothly, and are usually responsible for the following and more:

- Monitoring the health of the system and quickly restoring service if it goes bad.
- Tracking down the cause of problems, such as system failures or degraded performance.
- Keeping everything updated
- Keeping tabs on how diff systems affect each other
- Establishing good practices and tools for deployment.
- Performing complex tasks, like moving an app from one platform to another.
- Maintaining security
- Preserving organisational knowledge about the system, even through individuals

### Simplicity

Make it easy for new engineers to understand the system, by removing as much complexity as possible from the system.

One of the best tools we have for removing accidental complexity is abstraction. A good abstraction can hide implementation behind a clean facade. Good abstractions can be used in a number of places. For example, programming languages hide machine code, CPU registers and system calls.

### Evolvability

Make it easy for engineers to make changes to the system in the future. The ease with which you can modify a data system and adapt it to changing requirements is closely linked to its simplicity and its abstractions: simple and easy-to-understand systems are usually easier to modify than complex ones.