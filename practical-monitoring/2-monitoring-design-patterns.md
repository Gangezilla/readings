# Monitoring Design Patterns

## Pattern 1: Composable Monitoring

Use multiple specialised tools and couple them loosely together to form a monitoring "platform". 

One of the biggest perks of composable monitoring is that you're no longer committed to a particular tool or way of doing things. If one tool no longer suits your needs you can remove it and replace it instead of your entire platform.

### The components of a monitoring service

A monitoring service has five primary facets:

- Data collection
- Data storage
- Visualization
- Analytics and reporting
- Alerting

### Data collection

There are two primary ways for data collection to happen: push or pull. A pull model will request a remote node send data bout itself where this central service is responsible for scheduling when these requests happen. Generally a push model is better.

A push model has a client (server, app etc) push data to another location on a regular schedule. A push model is easier to scale in a distributed architecture, such as those in cloud environments. Nodes pushing data need only know where to send it, and don't need to worry about underlying implementation of the receiving end. 

The data we want to gather is either a metric, or a log.

#### Metrics

Metrics come in different representations

A *counter* is an ever-increasing metric, and they're good for measuring cumulative numbers of visitors to your website.

A *gauge* is a point-in-time value. The speedometer in your car is an example of a gauge. These are good, but they don't give you any historical data nor do they provide any hints for future values. However, by storing them you can retrieve them later and plot them on a graph

#### Logs

Logs are essentially strings of text with a timestamp associated with them.They contain much more data than metrics do and they are either structured or unstructured.