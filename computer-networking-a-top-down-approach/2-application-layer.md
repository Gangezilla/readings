# Application Layer

## Principles of Network Applications

At the core of network app dev is writing programs that run on diff end systems and communicate with each other over the network. Most importantly, you don't need to write software for routers or network devices, as these devices function at lower layers than the application layer.

## Network Application Architectures

From the app's perspective, the network architecture is fixed and provides a specific set of services to apps. An app developer will usually draw on either client-server architecture or peer-to-peer architecture.

CLient-server, its what you know and love working off a request-response model. Often a single server is incapable of keeping up with all the requests, so you often have a data center that houses a large number of hosts to create a powerful virtual server.

In P2P you dont have a server, but apps communicate directly with one another. This is used by stuff like BitTorrent and Skype. Some apps have hybrid structures using both.

### Processes Communicating

It's not actually programs communicating but processes, and they communicate by exchanging messages over the network.

#### Client and Server Processes

With client-server and P2P we usually label one party as the client and the other as the server, with the party that initates contact being the client.

#### The interface between the process and computer network

So, most apps consist of pairs of communicating processes, with the two sending messages to each other. A process sends messages into and receives messages from the network through a socket. The sending process assumes theres a transportation infra on the other side to process its message.