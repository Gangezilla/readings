# Microservices - Martin Fowler

A microservice architectural style is an approach to developing a single application as a suite of small services, each running in its own process and communicating with lightweight mechanisms, such as a HTTP API.

Enterprise apps are often built in three main parts: a client-side interface (HTML, JS), a database, and a server-side app that handles HTTP requests, executes domain logic, does DB operations and sends HTML views to the browser. Historically, these server-side applications are monoliths.

Monoliths can be successful, but they mean that change cycles are tied together. A change made to a small part of the app requires the entire monolith to be rebuilt and deployed. Over time its hard to keep a good modular structure, as changes often leak out into other modules. Scaling a monolith also means scaling the entire app, rather than just the parts that need greater resources.

A monolith puts all its functionality into a single process and scales by replicating the monolith on multiple servers. A microservices architecture puts each element into a separate service and scales by distributing these services across servers, replicating as needed.

## Characteristics of a Microservice architecture

### Componentization via Services

Software designers often want to be able to compose components together to make a greater whole. We define a component as a unit of software that is independently replaceable and upgradeable.

Microservice architectures componentize software by breaking it down into services. We define libraries as components that are linked into a program and called using in-memory function calls, while services are out-of-process components who communicate with a mechanism like a web service request, or remote procedure call.

Using services like this does have downsides. Remote calls are more expensive than in-process calls, and if you need to change the allocation of responsibilities between components this is harder when you have to cross process boundaries.

Services can map to runtime processes, but they may consist of multiple processes that will always be developed and deployed together such as an app and a DB that are only used by that service.

### Organised around Business Capabilities

When teams are separated across technology lines (ie: UI teams, server-side logic teams, DB teams), even simple changes can lead to a cross-team project taking time and budgetary approval. This leads to teams just pumping the logic into whatever they have access to.

The microservice approach to division splits services around business capability, leading to cross-functional teams with a full range of skills.

### Products not Projects

People who push microservices reckon teams should own a product over its full lifetime which means a development team takes full responsibility for the software in production.

This ties into business capabilities, where we look at software as a relationship with it's users, instead of a set of functionality to be completed.

### Smart endpoints and dumb pipes

In terms of communicating between services, the microservice community favours the idea of smart endpoints and dumb pipes. This means that services are often choreographed through simple RESTish protocols.

Sometimes people use a lightweight message bus such as RabbitMQ. In converting monoliths to microservices, the big problem is often in changing the communication pattern.

### Decentralized Governance

Microservices mean that we can use the right tool for the job, like, Node or C++ when appropriate.

### Decentralized Data Management

Data in one context means something different in another, for example customers to sales and support are v different.

It's helpful to think of this in a DDD Bounded Context capacity. DDD divides a complex domain into multiple bounded contexts and maps out the relationships between them.

Monoliths usually have one database, whereas microservices prefer letting each system manage its own database. Decentralizing responsibility for data across microservices has implications for managing updates, which is often handled using transactions to guarantee consistency across multiple resources.

### Infrastructure Automation

We want as much confidence as possible that our software is working, so we run lots of automated tests and we automate deployment.

### Design for failure

A consequence of using services as components is that apps need to be designed so they can tolerate the failure of services. Because of this, microservice teams reflect on how service failures affect the user experience.

Since services can fail at any time, it's important to be able to detect failures quickly and restore service.

### Evolutionary Design 

When you break a software system down into components, you have to decide how you divide up the pieces. As a key property of a component is that pieces are independently replaceable, we look for points where rewriting something wouldn't affect its collaborators.

This emphasis on replaceabilitiy is a special case of a more general principle of modular design, which is to drive modularity through the pattern of change.

Putting components into services adds an opportunity for more granular release planning as you can redeploy just the service you've touched.
