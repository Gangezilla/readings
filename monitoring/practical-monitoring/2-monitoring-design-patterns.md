# Monitoring Design Patterns

## Pattern #1: Composable Monitoring

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

Unstructured logs have no explicit mapping of meaning to a particular field field. Try and use structured logging where you can. There's guides online on how to switch various services from unstructured to structured and you should do that.

The most common way to collect logs is to set up log forwarding on your system.

### Data storage

Metrics are usually stored in a Time Series Database, which is a sort of database designed for storing time series data (which is basically a KVP with a timestamp as a key, and a value). We refer to these KVP as a datapoint.

Many TSDBs "roll up" data, meaning that as data gets older multiple data points are summarised into one. Generally these are averaged. It's up to you to figure out the right resolution for this.

### Visualisation

You're usually going to use line graphs. Useful dashboards have different perspectives and scopes, and they answer questions you have at a particular time.

It's ok to have multiple dashboards.

The best dashboards focus on displaying the status of a single service or product, and are most effective if they're maintained by people who understand the service the best.

### Analytics and reporting

It can be helpful to go beyond visualisations and into analytics and reporting. One of the most common use cases is determining and reporting on service-level availability (SLA) of your apps.

Availability is referred to by the number of nines. If you have a simple infrastructure, you determine how much downtime you had and compute that in terms of a percentage, `uptime / total time`.

This gets a bit harder when you have distributed systems. It's not worth pursuing super high number of nines, as it gets more and more expensive and your customers won't be able to tell anyway.

### Alerting

Monitoring doesn't exist to generate alerts; they're just one possible question. Monitoring allows us to ask questions. Remember, every metric you collect doesn't need to have an alert that goes with it.

## Pattern #2: Monitor from the User Perspective

The best place to add monitoring first is at the point(s) users interact with your app. A user doesn't care about the implementation details of your app, but they care about whether your app works, meaning you want visibility from their perspective.

One of the most effective things to measure is simply HTTP response codes and response times. These won't tell you what's wrong, only that something is and is impacting users. 

There's defs more, but this is a good place to start.

In short, start monitoring as close to the user as possible.

## Pattern #3: Buy, not build

It says it all ^^^

## Pattern #4: Continual Improvement

It's ok to completely rearchitect your monitoring every couple of years as your needs change and your industry evolves.