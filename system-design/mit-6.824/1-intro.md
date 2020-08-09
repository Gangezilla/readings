# Introduction

Distributed system is a bunch of computers cooperating over a network to get some task done.

- Storage for big sites
- Big data computation (MapReduce)
- P2P file sharing

Lots of critical infra is built around distributed systems. If you're building a system and it's possible you should do it on a single computer and its always easier. You should try everything else before building a distributed system.

People build it for:

- High performance, parallelism 
- Fault tolerance
- Some problems are just naturally spread out in space, for example, making a transaction from Bank A to Bank B.
- Security, if there's some code you don't trust you may wanna split up where that code is executed. Achieved by splitting things up and isolating them.

Challenges:

- Concurrency
- Partial Failure
- Very tricky to obtain the performance speed boost you're striving for, lots of roadblocks get in the way. Takes careful design to get here. 

Distributed systems have moved from a niche thing to a really important part of computing infrastructure.

Infrastructure
Storage
Comunications
Computation

The dream would be to build an interface that look like non-distributed systems but are actually vast high performing fault tolerant distributed systems underneath.

## Performance scalability

If I have some problem I'm solving on a computer, if I buy a second computer how do I solve the problem in half the time?

You can scale your website by adding loads of servers as long as you don't overload your DB. This isn't infinite though. At some point your database starts to become a bottleneck and scaling by throwing servers at it no longer helps you because you've moved thr bottleneck. At this point you need to do a bit of design work, there's really no way to take a straight forward DB and refactor this. We'll see a bunch of examples of a distributed storage system.

## Fault Tolerance

If you're building a system with one computer that computer can stay up for ages, but if you have a thousand computers there's always something that goes wrong. A network cable dies, a switch's fan dies, a computer dies...

Big scale turns very rare events you don't have to worry about into regular occurences that have to be handled in the design of the system.

- Availability. Some systems are designed so that with certain kinds of failures the system keeps operating despite the failure. If you build a replicated service, if one of the replica services fails then maybe the other keeps going.
- Recoverability: The ability for a system to keep going if something bad happens. If too many failures have happened an available system stops responding. You can use non-volatile storage (like a hard drive) to store the state of a system here. You've also got replication here as well, which is tricky! The key problem that comes up is that they'll drift out of sync and stop being replicas.
- Consistency: Suppose we're building a distributed key value storage system, you've got a put and a get operation. In a non-distrib system there's often no ambiguity on what'll be returned with these operations. But with replication, you may have a number of different versions of this value depending on that point in time. Strongly and weakly consistent systems. You want replicas to have different likelihoods of failure, so like, you wouldnt put them on the same racks in the server room.

## MapReduce

Google was running huge computations on terabytes of data. Building an index of the web is like running big sort.

Looking to make non-expert able to run workload across a huge volume of systems. The application designer can write a simple map and simple reduce function that doesn't know anything about the distribution and MapReduce will handle it.

MapReduce starts by assuming there's input across stacks of files. It'll run your map function across each of these files, the output that a map function is required to produce is a list of key value pairs. For example, a word count program would count the words and output like `{a: 1, b: 4}`.

So we run all the maps on the files and get this intermediate output. MapReduce will then run a big reduce function over all of the intermediate values. Each of these is called a task, so map tasks and reduce tasks. IRL, it's routine to have a MapReduce that produces output that's used as input by another MapRreduce job.

IRL, there's some big collection of worker servers and there's a single master server. The master server knows there's some number of input files, and it farms out invocations to individual workers. 