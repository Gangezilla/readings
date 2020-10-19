# Scheduling: Proportional Share

Here we talk about another way of scheduling, called a **proportional share/fair share** scheduler. It's designed around the concept that instead of optimising for turnaround or response time, a scheduler might instead try to guarantee that each job obtains a certain percentage of CPU time.

Our main problem: How can we design a scheduler to share the CPU in a proportional manner? What are they key mechanisms for doing so? How effective are they?

## Basic Concept: tickets represent your share

Underlying lottery scheduling is the basic concept of tickets, which are used to represent the share of a resource that a process should receive. The percent of tickets a process has represents its share of the system resource in question.

For example, imagine two processes, A (with 75 tickets) and B  (with 25 tickets). Thus, we want A to have 75% of the CPU and B to have 25%. Lottery scheduling achieves this by holding a lottery every so often (every time slice for example). The scheduler then picks a random ticket and then runs this process.

Side note: Randomness is often a really good way to make decisions sometimes. They help us avoid strange corner cases, they're lightweight and don't require much state, and it can also be quite fast.

## Ticket Mechanisms

You can define currency for tickets and then give them to users to self-allocate.
You've also got ticket transfer that lets a process hand off its tickets to another process. This can be useful in a client/server capacity, where a client could hand its tickets off to the server for a faster response.
Ticket inflation can also be useful, which can allow a group of trusted processes to share CPU time if a process needs a bit more.

Theres quite a bit more in here about the implementation of them, but I'm not that interested in that right now. Good to know the overview.