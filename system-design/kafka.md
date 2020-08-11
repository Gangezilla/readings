# Kafka

## Capabilities

1. Publish and subscribe to streams of records, similar to a message queue or enterprise messaging system
2. Store streams of records in a fault-tolerant durable way
3. Process streams of records as they occur

## Use cases

1. Building real-time streaming data pipelines that reliably get data between systems or apps
2. Building real-time streaming apps that transform or react to the streams of data

## Concepts

1. Kafka is run as a cluster on one or more servers that can span multiple datacenters
2. The Kafka cluster stores streams of **records** in categories called **topics**.
3. Each record consists of a key, value and a timestamp.

## APIs

1. Producer API: allows an application to publish a stream of records to one or more Kafka topics
2. Consumer API: allows an application to subscribe to one or more topics and process the stream of records produced to them.
3. Streams API: allows an app to act as a **stream** processor, consuming an input stream from one or more topics and producing an output stream to one or more output topics, effectively transforming the input streams to output streams.
4. Connector API: allows building and running reusable producers or consumers that connect Kafka topics to existing apps or data systems. eg. a connector to a relational DB that might capture every change to a table.

## Topics and Logs

A topic is a category or feed name that you publish records to. Topics in Kafka are always multi-subscriber so a topic can have zero, one or many consumers that subscribe to the data written to it.

For each topic the Kafka cluster maintains a partitioned log which each partition being an ordered, immutable sequence of records that is continually append to. Each record in a partition is assigned a sequential ID called an **offset** that is a unique identifier.

The cluster persists all published records (consumed or not) within the retention period. The only metadata that is retained by a consumer is the offset of where it's up to. This means a consumer can reset to an older offset to reprocess data from the past or skip ahead to the most recent record. This means consumers are cheap, and can be created or destroyed without impacting the cluster or other consumers.

TLDR: A log is a collection of partitions, and a partiton is a collection of records.

## Distribution

A log's partitions are distributed over the servers in the Kafka cluster with each server handling data and requests for a share of the partitions.

Each partition has one server that acts as the leader and zero ro more that act as followers. The leader handles all read and write requests while the followers passively replicate the leader and one will become the leader if the leader fails.

## Producers

A producer publishes data to the topic of their choice. The producer is responsible for choosing which record to assign to which partition within the topic, which can be done round-robin style or based off some logic.

## Consumers

Consumers label themselves with a **consumer group name** and each record published to a topic is delivered to one consumer instance within each subscribing consumer group. Consumer instances can be in separate processes or on separate machines. If all consumer instances have the same consumer group, then the records will effectively be load balanced over the consumer instances.

## Guarantees

1. Messages sent by a producer to a particular topic partition will be appended in the order that they're sent. That is, if a record M1 is sent by the same producer as record M2 and M1 is first, M1 will have a lower offset and appear earlier in the log.
2. A consumer instance sees records in the order they're stored in the log.
3. For a topic with replication factor N, we tolerate N-1 server failures without losing any records.

## Kafka for Stream Processing

In Kafka a stream processor is anything that takes continual streams of data from input topics, performs some processing on them and produces continual streams of data to output topics.

For this use you'd probably want to use the Streams API. It builds on the core primitives Kafka provides by using the producer and consumer APIs for input, using Kafka for stateful storage, and uses the same group mechanism for fault tolerance.

## Kafka Streams

### Core Concepts

Streams are a way of processing and analysing data stored in Kafka.

#### Highlights

1. Supports fault-tolerant local state which enables very fast and efficient stateful operations like windowed joins and aggregations.
2. Supports exactly-once processing semantics to guarantee that each record will be processed once and only once even when there's a failure on either Streams client or Kafka brokers.
3. Employs one-record-at-a-time processing to achieve millsecond processing latency and supports event-time based windowing operations with out-of-order arrival of records.

#### Stream Processing Topology

1. A stream represents an unbounded continuously updating data set. A stream is an ordered, replayable and fault-tolerant sequence of immutable data records (key value pair).
2. A stream processing application defines its computational logic through processor tolopogies which is a graph of stream processors (nodes) connected by streams (edges).
3. A stream processor is a node in the processor topology representing a processing step to transform data in streams by receiving one input record at a time from its upstream processors in the topology.

You've also got two special processors

1. Source processor: which doesn't have any upstream processors, producing an input stream by consuming records and forwarding them downstream
2. Sink processor: doesn't have any downstream processors, it sends received records to a specified Kafka topic.

#### Time

There are a few common notions of time in streams:

1. Event time: The point that an event or data record occured
2. Processing time: The point in time when the event happens to be processed by the stream processing application. It could be milliseconds - days after event time.
3. Ingestion time: The point in time when an event is stored in a topic partition by a Kafka broker. The difference to processing time is that this is generated when the record is appended to the target topic by the Kafka broker.
