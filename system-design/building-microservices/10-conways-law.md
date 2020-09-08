# Conways Law and System Design

Conways Law is that any org that designs a system will inevitably produce a design whose structure is a copy of the org's communication structure.

## Adapting to Communication Pathways

A single team of five people finds it easy to communicate about changes, refactoring and has a good sense of ownership. Contrast this to a geographically diverse team and the cost of coordinating changes is much higher. When the cost of coordinating change increases, people either reduce communication, or they stop making changes. Geographical boundaries can be a good way to figure out decomposition. If you have a new office opening, it might be a good time to consider what code ownership can be shifted over there too.

## Service ownership

A team that owns a service is responsible for changes to that service, as long as it doesn't break consuming services. An increased level of ownership increases autonomy and speed of delivery.

## Drivers for shared services

......