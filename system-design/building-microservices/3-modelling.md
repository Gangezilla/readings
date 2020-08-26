# How to Model Services

## What makes a good service?

### Loose Coupling

- A change to one service shouldn't require a change to another.
- A classic mistake that couples is to pick an integration style that tightly binds one service to another, causing changes in one service to require a change in another.
- A loosely coupled service knows as little as it needs to about the services with which it collaborates.

### High Cohesion

- Related behaviour sits together, unrelated behaviour sits elsewhere. If we want to change behaviour, we want to change it in one place and release that ASAP. If we have to change it in a few spots, we'll have to release lots of services which is risky and slow.

## Bounded Context

- Comes from Domain-Driven Design, bounded context is the idea that any given domain consists of multiple bounded context, within which are things that don't need to be communicated outside, as well as things that are shared with other bounded contexts. Each bounded context has an explicit interface where it decides what models to share.
- "A specific responsibility enforced by explicit boundaries"

### Shared and Hidden Models

- In a company, we have a finance department and a warehouse. They both have an explicit interface (inventory reports, pay slips) and have details only they need to know about (forklift controls, calculators).
- Finance doesn't need to know the inner workings of the warehouse, but they need to know some things like stock.

### Modules and Services

By thinking carefully about what should and should not be shared, we can avoid one of the pitfalls that leads to tight coupling, and we have identified a boundary where we have high cohesion.

## Business Capabilities

When you think about the bounded contexts that exist in your org, you should be thinking not in terms of data that's shared, but about the capabilities those contexts provide the rest of the domain.

