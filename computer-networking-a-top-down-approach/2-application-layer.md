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

### Transport Services Available to Applications

The app at the sending side pushes messages through the socket, and at the other side, the transport-layer protocol has the responsibility of getting the messages to the socket of the receiving process. The choice is figuring out which transport-layer protocol you go with. There are four dimensions we classify a transport-layer protocl with.

#### Reliable Data Transfer

Packets can get lost in a network, for example, a packet can overflow a buffer in a router or discarded if its bits are corrupted. For some apps, missing some data is fatal. Therefore, we need to guarantee that data sent will equal data received. If a protocol provides a guaranteed data delivery service, it is said to provide **reliable data transfer**.

#### Throughput

Throughput is the rate at which the sending process can deliver bits to the receiving process. Throughput can vary, so a transport-layer protocol could provide a guaranteed available throughput at some rate. With such a guarantee, a client can utilise this. For example, if a telephony app encodes at 32 kbps, it needs to send data into the network and have it delivered at this rate. Apps with throughput requirements are said to be **bandwidth-sensitive**. If an app is not sensitive it is called **elastic**, such as email, file transfer.

#### Timing

A transport-layer protocl can also provide timing guarantees, such as a guarantee that every bit the sender sends into the socket will arrive at the receiver's sockets no more than 100 msec later.

#### Security

A transport protocol can provide an app with one or more security services. For example, a sending host can encrypt all data transmitted.

### Transport Services Provided by the Internet

#### TCP Services

- Connection oriented service: Client and server exchange transport-layer control information before app level messages flow, which is called a handshake. After the handshake, a TCP connection exists between the sockets.
- Reliable data transfer service: Communicating processes rely on TCP to deliver all data sent without error and in the proper order.
- Congestion control: This mechanism throttles a sending process when the network is congested between sender and receiver.
- Security: TCP doesn't have built in security, so an enhancement was made; SSL. SSL is not on the level of TCP or UDP, but is an enhancement to TCP.

#### UDP Services

- Connectionless, so no handshaking.
- Unreliable data transfer service.
- No congestion control mechanism.

#### Services NOT provided by internet transport protocols

So you've basically got TCP or UDP as the underlying transport protocol. You've then got an application-layer protocol that makes these things work. For example:

- email: SMTP (app), TCP (transport protocol)
- remote terminal access: telnet (app), TCP
- Web: HTTP, TCP
- File transfer: FTP, TCP
- YouTube: HTTP, TCP

### Application-layer Protocols

An application-layer protocol defines how an app's processes pass messages to each other, defining:

- Types of messages exchanged, for example, request and response messages.
- Syntax of message types, like fields in the message and how the fields are delineated.
- The semantics of the fields, meaning the info in the fields.
- Rules for determining when and how a process sends and responds.

## The Web and HTTP

### Overview of HTTP

The HyperText Transfer Protocol is the Web's application-layer protocol and is implemented on a client program and a server program. They talk to each other by exchanging HTTP messages.

- Web browsers implement the client side of HTTP, and web servers (obvis) implement the server part.
- HTTP defines how Web clients request web pages from servers, and how servers transfer Web pages to clients. TL;DR, when a client requests data, the server responds with HTTP messages that contain the data.
- HTTP uses TCP as its underlying transport protocol (instead of UDP). The client initates a TCP connection with the server and once that connection is established, the browser and server processess access TCP through their socket interfaces.
- The server sends info to clients without storing any state info about the client, meaning HTTP is a stateless protocol. Web servers use a client-server app architecture, meaning a web server is always on with a fixed IP address, servicing requests from millions of diff browsers.

### Non-Persistent and Persistent Connections

Non-persistent:

- Client initiates a TCP connection to server.
- HTTP client sends an HTTP request to the server via socket. 
- HTTP server processes this via its socket, and sends the data in a HTTP response message via socket.
- HTTP server tells TCP to close the TCP connection, which it does after its confirmed the client received the message intact.
- The TCP connection is closed, the message indicates that another 10 JPEGs are needed, and then these steps are repeated for each of those JPEGs

Persistent:

With HTTP 1.1 persistent connections, the server leaves the TCP connection open after sending a response, allowing subsequent messages to be sent over the same connection. The server will close a connection when it isn't used for a certain time.

### HTTP Message Format

HTTP specs define the HTTP message formats of the two types of HTTP messages, requests and responses. Here is a humble HTTP request

```http
GET /somedir/page.html HTTP/1.1
Host: www.someschool.edu
Connection: close
User-agent: Mozilla/5.0
Accept-language: fr
```

The first line is the request line (which consists of method, URL and HTTP), and the other lines are the headers.

- The `Host` line is required by Web Proxy caches.
- The `Connection` header is the browser telling the server not to bother with persistent connections.
- There's a number of status codes associated with HTTP requests: 200, 301, 400, 404, 500...

### User-Server Interaction: Cookies

