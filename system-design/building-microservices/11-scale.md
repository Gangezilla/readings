# Microservices at Scale

## Failure is Everywhere

If we can embrace the possibility of failure then we'll be better off. If we can handle the failure of a service gracefully then we can do in-place upgrades of a service, as a planned outage is much easier to deal with than an unplanned one.

Baking in the assumption that everything can and will fail leads you to think differently about how you solve problems. If you know oyur system can handle the fact that a server can and will fail, why bother spending much on it at all?

## How much is too much?

There's many approaches to problems, but only you know your stack and the lengths you need to go to to solve your problems.

Having an autoscaling system could be great, but could be overkill for a system that only runs twice a month. Likewise, figuring out blue/green deployments to eliminate downtime might make sense for your e-commerce site, but is probably overkill for a corporate intranet. You'll need to figure out what your users require, start with these:

- Response time/latency: The raget for this should include the number of concurrent connections/users you expect your software to handle, like "we expect the website to have a 90th-percentile response time of 2 seconds when handling 200 concurrent connections per second".
- Availability: Can you expect a service to be down, or is it a 24/7 service? 
- Durability of data: How much data loss is acceptable? How long should data be kept for?

## Degrading Functionality

An essential part of building a resilient system is to safely degrade functionality. If we have to hit a bunch of services, but one of them being down crashes our site then we've made a really brittle site.

With a monolith, system health is binary. With microservices we need to be more nuanced. If a shopping cart is down, we might still allow someone to browse or check stock.

## CAP Theorem

Consistency, availability and partition tolerance. 