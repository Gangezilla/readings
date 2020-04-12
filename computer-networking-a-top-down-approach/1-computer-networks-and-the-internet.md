# Computer Networks and the Internet

## What is the internet?

### A nuts and bolts description

The Internet is a computer network that interconnects billions of computing devices through the world. This encompasses a pretty broad range of devices nowadays. In Internet jargon, all of these devices are called hosts or end systems.

End systems are connected together by a network of communication links and packet switches. There are many types of communication links that are made of different things, like coaxial cable, copper wire etc. Each of these has differing transmission rates, measured in bits/second. When one end system has data to send, the sending end system segments the data and adds header bytes to each segment. These are called packets and get sent to the end system and reassembled.

A packet switch takes a packet and forwards it on, and usually comes as a router or link-layer switch. The sequence of communication links and packet switches from start to end is a route/path through the network.

End systems access the internet through ISPs which is in itself a network of packet switches and communicaiton links.

End systems, packet switches and other pieces of the internet run **protocols** that control the sending and receiving of information within the internet. Two of the most important protocols are Transmission Control Protocol (TCP) and Internet Protocol (IP). IP specifies the format of the packets.

### A services description

We can also describe the internet as an infrastructure that provides services to applications. Many apps are called distributed applications, as they involve multiple end systems that exchange data with one another. Internet apps run on end systems, not on packet switches. The switches just facilitate data exchange.

How does one program running on one end system intruct the Internet to deliver data to another program running on another end system? End systems use a **socket interface** that specifies how a program running on one end system asks the infrastructure to deliver data to a specific destination program.

### What is a protocol?

All activity on the Internet that involves two or more communicating remote entities is governed by a protocol. When you type in a URL your computer sends a connection request to a server which will send a response.

A protocl defines the format and order of messages exchanged between two or more communicating entities, as well as the actions taken on the transmission and/or receipt of a message or other event.

The internet and computer networks make extensive use of protocols. Protocols are used to accomplish different communication tasks.

## The network edge

End systems are referred to as hosts because they host/run applications. Here we use hosts and end systems interchangeably.

### Access networks

An access network is a network that physically connects an end system to the first router (also known as an edge router) on a path from the end system to any other distant end system.

The two most prevalent broadband access networks are DSL and cable.

## The network core

The network core is the mesh of packet switches and links that interconnects the internet's end systems.