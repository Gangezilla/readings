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

### Web Caching

A web cache, also called a proxy server, is a network entity that satisfies HTTP requests on the behalf of an origin Web server. A cache has its own disk storage and keeps copies of recently requested objects in this storage. A user's brower can be configued so that the users HTTP requests are first directed to the cache. It might work like this:

1. The browser establishes a connection to the cache, and requests an object.
2. The cache checks if it has the object stored and returns it if it does.
3. If it doesn't, the cache opens a TCP connection to the origin server and retrieves the object from there.
4. When the cahce receives the object, it stores a copy in its local storage and sends a copy back to the browser.

## Email

SMTP is the principal application-layer protocol for email. It uses TCP to reliably send mail from the sender to the receiver. There's also IMAP and POP but it's maybe a bit too recent.

### SMTP

SMTP (RFC 5321) is the heart of email. It predates HTTP (the RFC is from 1982, but SMTP was around before that). Cos of this, it's pretty legacy and has some limitations. Let's look at a flow.

1. Alice invokes her user agent for email, and instructs it to send a message to Bob.
2. Alice's user agent sends the message to her mail server where it gets placed in a queue.
3. The client side of SMTP sees this, and opens a TCP connection to Bob's SMTP server.
4. After some initial handshaking, the SMTP client sends Alice's message into the TCP connection.
5. At Bob's mail server, the server side of SMTP receives the message and places it in Bob's mailbox where he can read it.

SMTP has similarities with protocols used for face-to-face human interaction.

1. The client SMTP (running on the sending server) has TCP establish a connection to port 25 at the server SMTP. If the server is down, the client will try again later on.
2. Once there's a connection, the server and client do their handshake. During this handshake, the SMTP server indicates the email address of the sender and email of recipient. Post handshake, the client sends the message.
3. SMTP relies on the reliability of TCP to transfer the message.

There's a few specific commands that get issued by the client.

- `HELO`
- `MAIL FROM`
- `RCPT TO`
- `DATA`
- `QUIT`

The server replies to each command with a reply code and some optional English. If the sender has multiple emails, it can send them all at once.

BTW, assignment 3 has you implement the client side of SMTP. Cool.

### Comparison with HTTP

- Both protocols transfer files from one host to another. HTTP transfers files from server to client, and SMTP transfers from server to server.
- HTTP is a `pull` protocol, someone loads info onto a server and users use HTTP to pull the info. SMTP is a `push` protocol, the sending server pushes the file to the receiving mail server.
- SMTP requires each message to be in 7-bit ASCII, which HTTP doesn't require.
- If a document has text and images, HTTP will break this up into individual responses, SMTP does it all in one go.

### Mail Message Formats

Headers for SMTP are included in RFC 5322. As with HTTP, each header contains readable text consisting of a keyword with a colon and value. Some are required, some are optional.

- `From:` (required)
- `To:` (required)
- `Subject:` (optional)


### Mail Access Protocols

Many people have their email stored on a central server and then use a local user agent to access it, so they can get their email on their computer or phone. A typical flow:

1. Alice's user agent sends an email to her mail server over SMTP
2. Alice's mail server will use SMTP to send an email to Bob's mail server, where it can then retry the send if it fails.
3. Bob's mail server receives the email and can send it to Bob's user agent over POP3, IMAP or HTTP.
4. Bob checks his phone and boom, emails appear.

POP3, IMAP and HTTP are mail access protocols that can be used to speak to the server.

#### POP3

POP3 is quite simple and limited. Once a TCP connection has been established, POP3 progresses through 3 phases:

- Authorization: user agent sends a username and password to authenticate the user.
- Transaction:  user agent retrieves messages and can mark messages for deletion, remove deletion marks, obtain mail stats. here the user agent issues commands and the server responds to each
- Update: Occurs after the client issues the `quit` command, where the mail server deletes messages that were marked for deletion.

During a POP3 session, the server maintains some state, namely it keeps track of which user messages have been marked as deleted. However, it doesn't carry state info across POP3 session which means you don't get consistency over multiple user agents, but it does make implementation simpler.

#### IMAP

IMAP is a mail access protocol with many more features, and much greater complexity.

IMAP associates each message with a folder, when a message first arrives at the server it is associated with the recipient's INBOX. The recipient can move the messages around, read, delete etc. IMAP also maintains user state across session, like folder names, which messages are in which folder etc.

## DNS - The Internet's Directory Service

Just as humans can be identified in many ways, so too can Internet hosts. One identifier is its hostname, like `www.facebook.com`. But these provide little info about the location within the internet of the host. Cos of this, we identify hosts by IP addresses. TL;DR an IP is 4 bytes and has a rigid hierarchical structure. IPs look like 121.7.106.83 which each period separating a byte. It's hierarchical because we can scan for left to right and get more info about where the host is located.

### Services provided by DNS

You can identify a host by a hostname (for humans) or an IP (for routers). To reconcile this, we use a DNS which is a distributed database implemented in a hierarchy of DNS servers and an application-layer protocol that allows hoststo query the distributed database.

DNS also provides a few other services:

- Host aliasing: Hosts with complicated hostnames can have multiple alias names
- Mail server aliasing: If you're emailing an @yahoo.com email addy, the hostname of Yahoo's email server is more complex than just that. DNS can be invoked by an application to obtain the canonical hostname and IP address. The MX record permits a company's mail server and web server to have identical hostnames.
- Load distribution: DNS is also used to perform load distribution among replicated servers. For replicated web servers a *set* of IP addresses are associated with one hostname. DNS will respond to requests with one of those IPs and rotate them around. In saying this, I don't think this is what you'd use in 2020. You'd probably lean towards something like nginx or Envoy Proxy.

### Overview of how DNS works

We focus on the hostname-to-IP-address translation service.

- An app (like a web browser) running in a user's host needs to translate a hostname to an IP. The app invokes the client side of DNS , specifying the hostname that needs to be translated.
- DNS in the user's host takes over and sends a query into the network. All DNS query and reply message are sent with UDP datagrams to port 53. It will eventually receive a reply that provides the desired mapping which gets passed to the invoking application. To the app, DNS is a black box.
- This black box is complex tho, consisting of a large number of DNS servers around the globe and an app-layer protocl that specifies how the DNS servers and querying hosts communicate.

A simple design consists of one DNS server, where clients simply direct all queries to the one server. This is bad tho cos it's a single point of failure, gets high traffic volume, can't be physically close to all querying clients, and would need to be constantly updated.

#### A distributed, hierarchical DB

DNS uses a large number of servers organised hierarchically and distributed globally to deal with the issue of scale.

There's three approximations of DNS servers:
- Root DNS servers. There are 400+ of these around the world, Australia has 16 of them!
- Top level domain (TLD) DNS servers (com, org, edu...). For each of the TLDs, there's a TLD server (or cluster) and this is maintained by a company. For `com` for example, a company called Verisign Global Registry Services maintains it.
- Authoritative servers (facebook.com, amazon.com, pbs.org...). Every org with publicly accessible hosts must provide publicly accessible DNS records that map these hostnames to IPs.
- Local DNS server. This doesnt strictly belong to the hierarchy but is central to DNS arch. Each ISP has a local DNS server. When a host connects to an ISP, the ISP provides the host with the IP addresses of one or more of its local DNS servers. 

When you try to access amazon.com, your browser contacts the root server, which returns the IP for a TLD server for com. You then contact this and you receive the authoritative server for amazon.com, which returns the IP for the hostname www.amazon.com

#### DNS Caching

DNS uses caching to improve perf, and reduce the number of DNS messages. In a query chain, when a DNS server receives a reply it can cache the mapping in its memory so it can give this info for other requests. This info will usually be invalidated after a period of time.

### DNS Records and Messages

DNS servers store resource records (RRs). Each DNS reply carries one or more RRs. An RR is a four-tuple containing these fields:

`(Name, Value, Type, TTL)`

TTL is time to live, determining when a resource should be removed from a cache

- If `Type=A` then `Name` is a hostname, and `Value` is it's IP. Therefore a Type A record provides standard hostname-to-IP mapping, like
`(relay1.bar.foo.com, 145.37.93.126, A, 0)`
- If `Type=NS` then `Name` is a domain (foo.com) and `Value` is the hostname of an authoritative DNS server that knows how to obtain the IP for hosts in the domain. This is used to route DNS queries further along in the query chain.
`(foo.com, dns.foo.com, NS, 0)`
- If `Type=CNAME` then `Value` is a canonical hostname for the alias hostname `Name`. This record can provide querying hosts the canonical name for a hostname.
`(foo.com, relay1.bar.foo.com, CNAME, 0)`
- If `Type=MX`, `Value` is the canonical name of a mail server that has an alias hostname `Name`.
`(foo.com, mail.bar.foo.com, MX, 0)`. MX records allow the hostnames of mail servers to have simple aliases. This also allows a company to have the same aliased name for its mail server and for one of its other servers.

If the DNS server is authoritative for a hostname, the DNS server will contain a Type A record for the hostname. If it's not authoritative, the server will contain a Type NS record.

## P2P File Distribution

With P2P architectures, there's minimal (or no) reliance on always-on infra servers. Instead pairs of intermittently connected hosts (peers) communicate directly with each other. They're not owned by a service provider, but are computers controlled by users.

As of 2016, the most popular P2P protocol is BitTorrent.

P2P is super scalable.

## Video Streaming and CDNs

### Internet Video

Prerecorded videos are placed on servers and users send requests to the servers to view the videos on demand. Video content can be compressed by trading video quality with bit rate.

From a networking perspective, the most important characteristic of video is its high bit rate. This ranges from like 100kbps to 10Mbps

### HTTP Streaming and DASH

In HTTP streaming, the video is stored on a server as a file with a specific URL. The server then sends the video file. On the client side, the bytes are collected in a buffer. Once the number of bytes in this buffer exceeds a threshold the client begins playback. HTTP streaming's biggest shortcoming is that all clients receive the same encoding of the video which has led to a new type of streaming called Dynamic Adaptive Streaming over HTTP (DASH). In DASH, the video is encoded into several different versions with diff bit rates. The client dynamically requests chunks of video segments of a few seconds in length. When the amount of bandwidth is high, the client grabs chunks from the high-rate version and vice versa.

### CDNs

For an internet video company, the most straightforward way to provide streaming is to build one huge data center, store everything there and then stream them from here to the clients. But there's 3 probs:

1. If the client is far away, packets from the server go through many links and it takes ages. If a link provides a throughput less than video consumption rate, the user will get lots of delays.
2. A popular video will likely be sent many times over tge same links, wasting bandwidth and also network costs to the ISP
3. A single data center represents a single point of failure.

To distribute lots of video data, companies use CDNs. A CDN manages servers in multiple geographically distributed locations, stores copies of the videos and other content in its servers, and attempts to direct each user request to a CDN location that'll give the best experience. Some companies own and operate their own CDN (like Google), other times 3rd parties do this (like Akamai, Limelight, AWS Cloudfront, Cloudflare). CDNs usually do one of two server placement philosophies:

1. Enter Deep into the access networks of ISPs by deploying server clusters in access ISPs around the world. Akamai does this approach with clusters in ~1700 locations with the goal of getting close to end users.
2. Bring home, by bringing ISPs home by building large clusters at a smaller number of sites. These CDNs typically place their clusters in Internet Exchange Points (IXPs). This is usually a bit cheaper and easier to manage, but often with higher delay and lower throughput.

Up to p188