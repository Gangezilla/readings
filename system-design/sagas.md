# Sagas

Sagas are a pattern used to implement a transaction that spans multiple services.

A saga is a sequence of local transactions. Each service in a saga performs its own transaction and publishes an event which other services listen for and then perform the next local transaction. If a transaction fails, the saga executes compensating transactions to undo the impact of the preceding transactions.

In something like UberEats for example:

- The food ordering service creates an order, which is now PENDING. The saga will manage the chain of events
- The saga contacts the restaurant via the restaurant service.
- The restaurant service attempts to place the order with the chosen restaurant. After confirming, it sends a reply to the saga.
- The sage receives the reply and can either approve or reject.
- The food order service then changes the state of the order. If it was approved, it would inform the customer with the next details.

Two types of sagas:

1. Orchestration-based saga: Here there's a saga orchestrator that manages all the transactions and directs the participant services to execute local transactions based on events.
2. Choreography-based saga: No central orchestrator, each service performs their own transactions and publish events.
