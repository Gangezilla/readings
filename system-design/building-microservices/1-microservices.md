# Microservices

## Small and focused on doing one thing well

- Single responsibility principle. Focus our service boundaries on business boundaries and by keeping this service focused on an explicit boundary we avoid the temptation for it to grow too large.
- A dude from REA characterizes a microservice as something that could be rewritten in two weeks as a rule of thumb.

## Autonomous

- Separate entity that can be deployed as an isolated service.
- All communication between the services is done via network calls to enforce separation and avoid tight coupling.
- We need to be careful with what we share, cos if we share too much, our consuming services become coupled to our internals.
- Our service exposes an API and services collaborate through that API.
- The golden rule: can you change a service and deploy it without changing anything else?

## Benefits

### Technology Heterogeneity

- We can use the right tech for the right job. Meaning, if perf is an issue we can rewrite to meet these goals.
- Also means we can adopt tech more quickly and understand how new advancements may help us, as well as do experiments.

### Resilience

- A key concept in resilience engineering is the bulkhead. If one component fails but the failure doesn't cascade, you can isolate the problem and the rest of the system can keep on keeping on. Service boundaries become your obvious bulkhead.
- We do need to deal with the new sources of failure that distributed systems have to deal with, like network and machine failures.

## Scaling

- In a monolith, if perf sucks in one area we have to scale the whole thing. In a microservice we can scale bits and pieces individually.

## Ease of deployment

- Safer and easier to deploy small service repeatedly instead of a big service with heaps of changes less frequently.

## Organisational alignment

## Composability

## Optimising for replaceability