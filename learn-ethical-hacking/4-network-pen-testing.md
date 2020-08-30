# Network Penetration Testing

## What's a network?

Network pen testing can be split into four parts:

1. Pre-connection
2. Gaining access
3. Post-connection
4. Detection + security

Parts 1 and 2 are about wireless networks cos they have encryption and require a key to use the network.

## Basics

A network is a number of devices connected together to share data. Networks achieve this on the principle of a device acting as a server, which all devices communicate with. The server has access to the resources and all other devices can access the data from the server. On most wi-fi networks, the server is the router and all devices connect to it and access internet through it.

They recommend me get a wireless adapter sometime cos it's more powerful than the built in network card.

## MAC Addresses

Each network card has a physical, static address assigned by the card manufacturer. This is the Media Access Control (MAC) address and cos it's physical it never changes. Since they're static and never change you can identify a computer with this. You can change it in RAM, but it'll be reset on a restart.

We can change this to something else using `macchanger`.
