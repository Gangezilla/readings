# Integration

Integration is really important. If you mess it up, disaster awaits.

## Choosing a technology

- Avoid breaking changes
- Keep APIs technology-agnostic.
- Make your service simple for consumers
- Hide internal implementation details

## The shared database

A common way of building microservices is by having one DB. If services want info or to change info, they reach into the DB. This is simple, but hurts you in the long run:

1. We're allowing external parties to view and bind to internal implementation details. If I change my schema, I break my consumers. It means the DB is essentially a brittle shared API.
2. Consumers are tied to a specific tech choice, meaning we can't change from a relational DB to something more appropriate if we need to.
3. Where do you store the logic? If all services need to edit customer info, you have to fix bugs in all places.

With DB integration, we loose the two most important things, strong cohesion and loose coupling.

## Sync vs Async

Two diff modes of communication can enable to diff styles of collaboration, request/response or event-based. Req/res means a client initates a request and waits for the response and this works for sync or async. With event based, we invert things. Instead of a client initating requests and waiting for a response, it says "this thing happened" and expects other parties to know what to do. These are async by nature.

## Orchestration vs Choreography

Orchestration is having a central brain to guide and drive the process. Choreography, we inform each part of the system of its job and let it work out the details. Orchestration is typically where you have a component call several functions or methods and dictate what happens, whereas choreography would mean we publish an event and the downstream services pick up on that event. Doing this means you need to monitor your system and make sure everything happens.

## Remote Procedure Calls

RPC refers to making a local call and having it execute on a remote service somewhere. The core idea of RPC is to hide the complexity of a remote call, but be careful not to hide too much. With RPC theres a cost to marshalling and unmarshalling payloads, not to mention the time taken to send things. You've also gotta think about the network cos the network is unreliable.

When designing RPC services, you need to keep in mind that its remote and not local.