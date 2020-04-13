# Prelim Notes

## Scaling

Horizontal scaling means you scale by adding more machines into your pool of resources.

Vertcal scaling means you scale by adding more power (CPU, RAM) to an existing machine.

When you've horizontally scaled, you need a load balancer to distribute user requests among the various systems you have in your cluster (with a cluster being multiple servers that work together). A load balancer distributes load by maintaining the state of each machine (how many requests are being served, which is idle, which is over-loaded etc). The load balancer considers such things before redirecting the request to an appropriate server.

## Caching

In computing, a cache is a high-speed data storage layer which stores a subset of data so that future requests for that data are served up faster than by accessing the data's primary storage location.

The data in a cache is generally stored in fast access hardware like RAM and may also be used in correlation with a software component.

- RAM and in-memory engines: Because RAM supports high I/O operations caching results in improved data retrieval perf and reduces cost at scale.
- Apps: Caches can be applied through various layers of tech incl OS, networking (CDNs) etc. You can use caching to greatly reduce latency for many read-heavy app workloads. Cached info can include the result of DB queries, computationally intense calculations.
- Design patterns: In a distributed computing environment, a dedicated caching layer enables systems and apps to run independently from the cache with their own lifecycles without the risk of affecting the cache.
- Caching best practices: When implementing a cache layer its important to understand the validity of the data being cached. A successful cache results in a high hit rate which means the data was present when fetched. A cache miss occurs when the data fetched wasn't present in the cache.

In short, you cache to:

- Improve app performance
- Reduce DB cost
- Reduce the load on the BE
- Predictable performance
- Eliminate DB hotspots
- Increase Read Throughput

## Load Balancing

Load balancing refers to efficiently distributing incoming network traffic across a group of BE servers, also known as a server farm or server pool. A load balancer acts as the traffic cop sitting in front of your servers and routing client requests across all servers capable of fulfilling those requests in a manner that maximises spped and capacity utilisation. A load balancer performs the following functions:

- Distributes client requests or network load efficiently across multiple servers
- Ensures high availability and reliability by sending requests only to servers that are online
- Provides the flexibility to add or subtract servers as demand dictates.

Benefits of load balancing:

- Reduced downtime
- Scalable
- Redundancy
- Flexibility
- Efficiency
- Global Server Load Balancing

## Database Replication

Database replication is the process of copying data from a central DB to one or more DBs that may be at the same site or at different geographical locations on the same or diff networks. It involves the frequent copying of data from one DB to another so that they all share the same information.

## Database Partitioning

Partitioning is the DB process where large tables are divided into multiple smaller parts. By splitting a large table into smaller tables, queries that access only a fraction of the data can run faster because there's less data to scan.

## Le Cloud Blog - Scalability for Dummies

### Clones

Public servers of a scalable web service are hidden behind a load balancer. The load balancer evenly distributes load onto your cluster of servers. A user should always get the same results of their request back regardless of the server they landed on. This leads to rule number one for scalability:

**Every server contains exactly the same codebase and doesn't store any user related data like sessions or profile pics on local disc or memory**

Sessions need to be stored in a centralised data store thats accessible to all application servers. This can be an external DB or persistent cache like Redis. An external persistent cache will have better perf than an external DB.

### Databases

You've got 2 paths to making a DB like MySQL handle more requests.

1. Stick with MySQL and hire a DBA (database administrator) to do master-slave replication (read from slaves, write to master) and upgrade your master server by adding more RAM.
2. Denormalise from the beginning and include no more Joins in any DB query

Normalised data is where you organise all your data into different tables and you get all of it together through DB joins. Normalised DBs reduce redundancy and maintain data integrity, but after a while get pretty slow. Denormalised DBs work to put all of your data in one table to minimise the number of joins you have. The downside is that you have redundant data

### Cache

Here we refer to in-memory caches. A cache is a simple key-value store and it should reside as a buffering layer between your app and your data storage. Whenever your app has to read data it should first try to retreive it from your cache. Only if it's not in the cache should it hit the main data source. It should do this cos caches are fast as, and hold every dataset in RAM. There are two types of caching patterns:

1. Cached DB queries: Whenever you do a query, store the result in cache. A hashed version of your query is the cache key. The next time you run the query you first check if it's in the cache. The main issue is expiration. It's hard to delete a cached reult when you cache a complex query because when one piece of data changes you need to delete all cached queries that contain that piece of data.
2. Cached objects: Let a class assemble a dataset from your DB and store the complete instance in the cache. If you have a Product class that contains data. When this data is assembled you store this in the cache which allows you to easily get rid of the object when something changes.

Some ideas of objects to cache:

- User sessions
- Fully rendered blog articles
- Activity streams
- user <-> friend relationships

### Asynchronism

There are two ways asynchronism can work.

1. Imagine a bakery. The first way of async processing is baking the bread at night and selling it in the morning. This means doing the time-consuming work in advance and serving the finished work with a low request time. This paradigm is often used to turn dynamic content into static content like building HTML from a template. Often this is done on a regular basis.
2. In our bakery, if a customer has special requests this won't work. A user comes to our website and starts a computing intensive task that takes som time. The frontend of your site sends a job to a queue that will soon be processed. The FE then waits for the job to be done then informs the user.

You could use something like Kafka or RabbitMQ to implement async processing. The basic idea is to have a queue of tasks or jobs that a worker can process.

## Some definitions

### Performance v scalability

A service is scalable if it results in increased performance proportional to resources added. Typically increasing perf means serving more units of work

- If you have a perf problem, your system is slow for a single user.
- If you have a scalability problem, your system is fast for a single user but slow under heavy load.

### Latency v throughput

Latency is the time it takes to perform some action or to produce some result.
Throughput is the number of actions or results per unit of time.

Generally you want max throughput with acceptable latency.

### Availabilty v consistency

#### CAP theorem

In distributed computing you can only support two of the following guarantees

- Consistency: Every read receives the most recent write or an error
- Availability: Every request receives a response without guarantee that it contains the most recent version of the info
- Partition tolerance: The system continues to operate despite arbitrary partitioning due to network failures.

You need to support partition tolerance so you need to make a software tradeoff between consistency and availability.

CP - consistency and partition tolerance

Waiting or a response from the partitioned node might result in a timeout error. CP is good if your business needs atomic reads and writes (atomic meaning one thing at a time)

AP - availability and partition tolerance

Responses return the most recent version of the data available on a node, which might not be the latest. AP is a good choice if the business needs allow for eventual consistency (meaning that after a write, reads will eventually see it)

#### Consistency patterns

With consistency meaning that every read receives the most recent write there are a few patterns

Weak consistency: After a write, reads may or may not see it. This works well in systems like VoIP and gaming. If you lose reception for a few seconds, you don't hear what was said during connection loss.
Eventual consistency: After a write, reads will eventually see it (typically in milliseconds). Data is replicated asynchronously. This is seen in DNS and email.
Strong consistency: After a write, reads will see it. Data is replicated synchronously.

#### Availability patterns

There are two main patterns to support high availability:

Fail-over:
Active-passive: Active-passive fail-over sends heartbeats between the active and passive servers. If the heartbeat is interrupted, the passive server takes over the active's IP address and resumes service.
Active-active: In active-active, both servers manage traffice and spread the load between them.

### DNS

A Domain Name System (DNS) translates a domain name to an IP address. DNS is hierarchical with a few authoritative servers at the top level. Your router or ISP provides information about which DNS servers to contact when doing a lookup.

You've got managed DNS services like AWS's Route 53. Managed DNS is where a customer utilises authoritative DNS servers to store their authoritative DNS records . You'd use it to route end users to your internet apps.

### CDN

A content delivery network (CDN) is a globally distributed network of proxy servers serving content from locations closer to the user. There are two types:

Push CDN: Push CDNs receive new content whenever changes occur on your server. This means its your responsibility to provide content, upload it, and rewrite URLS pointing to the CDN.
Pull CDN: Pull CDNs grab new content from your server when the first user requests the content. A time-to-live (TTL) determines how long content is cached.

Disadvantages:

- CDNs can be expensive depending on traffic.
- Content might be stale if it's updated before the TTL expires it.
- CDNs require changing URLs for static content to point to the CDN.

### Reverse proxy (web server)

A reverse proxy is a web server that centralizes internal services and provides unified interfaces to the public. Requests from clients are forwarded to a server that can fulfill it before the reverse proxy returns the servers response to the client.

## Application layer

Separating out the web layer from the app layer (also known as platform layer) will let you scale and configure both layers independently. Adding a new API results in adding app servers without necessarily adding web servers. Single responsibility principle (SRP) advocates for small autonomous services that work together.
