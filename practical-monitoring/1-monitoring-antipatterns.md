# Monitoring Anti-patterns

## Anti-pattern #1: Tool Obsession

Many monitoring efforts start out with someone saying "we need better monitoring!", meaning they blame the existing toolset and then implement something new which will be hated in 6 months time anyway.

Remember, there are no silver bullets.

Monitoring a complex system takes effort, and there's no such thing as a single tool that will provide you with perfect visibility into your network, servers and applications.

Monitoring is a huge problem set, covering metrics and logs for server hardware, the OS, all of the services running and the interactions between them. Plus, paying attention only to the servers isn't enough, as you need to monitor the network infrastructure too.

### Monitoring is multiple complex problems under one name

- If you're trying to profile and monitor your app at the code level, you maybe want some APM tools
- If you need to monitor performance of a cloud infrastructure, you might look at modern server monitoring solutions.
- If you need to monitor for spanning tree topology changes or routing updates, you might look at tools with a network focus.

Don't be afraid of adding new tools as long as they each give you valuable information. It's ok to have multiple teams using multiple tools, but it's concerning if your tools can't work together and you can't correlate the data they give you.

### Avoid Cargo-Culting Tools

Just because a company has released a tool doesn't mean it's right for your use case. Blindly adopting tools like this overlook why these tools exist in the first place and what problems they solve.

## Anti-pattern #2: Monitoring-as-a-job

At first glance, it makes sense to put someone in charge of monitoring instead of having a generalist do a mediocre job. This is an anti-pattern as monitoring is a skill, not a job. Monitoring can't be built in a vacuum as it's a crucial component to the performance of your services.

Strive to make monitoring a first-class citizen when it comes to building and managing services. Remember, it's not ready for production until it's monitored. A team may build the tools that get used, but it's up to everyone to implement said tools.

## Anti-pattern #3: Checkbox Monitoring

Checkbox monitoring is when you have monitoring systems for the sole sake of saying you have them. You'll know this is what you've done if you:
- Capture metrics, but your service still goes down and you don't know hy.
- You find yourself ignoring alerts because they're often false alarms.
- You check for metrics every five minutes or so
- You aren't storing historical metric data.

To fix this you need to understand what you're monitoring. For the app/service you're monitoring, what does "working" mean, and are there any high-level checks you can perform?

If we're talking about a webapp, you could do a GET request to `/` and record the response code and latency. If something's going wrong then we might see the latency increasing, or maybe we don't get a 200 OK response back.

Every service and product your company has will have these high-level checks. They don't necessarily tell you what's wrong, but they're good leading indicators that something could be wrong.

----------------------------------------------------------------;

A leading indicator is a factor that changes before your service starts to go in a particular direction.

----------------------------------------------------------------;

Opt to collect metrics every 30 seconds, or sometimes even more regularly if you're a high traffic system. After this, make sure you configure roll-up at a suitable granularity so you aren't keeping like a years worth of CPU data around.

## Anti-pattern #4: Using Monitoring as a crutch

Avoid the tendency to lean on monitoring as a crutch. It's great for alerting, but it's even more important to actually fix the problems you find. More monitoring doesn't fix a broken system.

## Anti-pattern #5: Manual configuration

Your monitoring should be 100% automated. The difficulty in building a well-monitored infra and app without automation can't be overstated. If you can't quickly add something to monitoring then it just becomes frustrating.
