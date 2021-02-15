# The Trouble With Distributed Systems

Working with distributed systems is fundamentally different from writing software on a single computer.

## Faults and Partial Failures

There's no fundamental reason why software on a single computer should be flaky, when the hardware is working correctly the same operation always produces the same result. Whereas if there's a hardware problem, the consequence is usually total failure. So an individual computer with good software is either fully functional or entirely broken. This is deliberate in computer design, as we'd rather a computer crash than return an incorrect result.

When you're writing software across several computers, the situtation is fundamentally different, we're no longer in an idealized system model. In a distributed system, some parts of the system may be broken while others are fine. This is a *partial failure*

## Unreliable Networks

The distributed systems we focus on are *shared-nothing* systems, where these machines are connected over a network and don't share any memory or disk etc. The internet and most internal networks are *asynchronous packet networks*. With this, there's tonnes of stuff that can go wrong. If you send a request to another node and don't receive a response, it is impossible to tell why. This is often handled by a timeout, but you still don't know what happened to your request.

### Network faults in practice

Nobody is immune from network faults. So much stuff can go wrong, from software upgrades to a switch delaying packets to a shark biting an undersea cable and damaging them. Even if faults are rare, your software needs to be able to handle them. This doesn't mean you need to tolerate them, showing an error message is a valid approach for example.