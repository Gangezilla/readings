# Alerts, On-Call and Incident Management

Alerting is just one way of achieving our monitoring goals. Great alerting is harder than it seems. Metrics tend to be spike-y, so alerting on raw datapoints produces lots of false alarms. You can get around this by using a rolling average which makes us lose granularity but make better alert accuracy.

## What makes a good alert?

Let's make a distinction between alerts:

- Alerts meant to wake someone up
- Alerts meant as an FYI.

The second one is a message, the first is an actual alert. An alert should evoke a sense of urgency and require action from the person receiving that alert. Here are six practices that are key to building great alerts:

- Stop using email for alerts
- Write runbooks
- Arbitrary static thresholds aren't the only way.
- Delete and tune alerts
- Use maintenance periods
- Attempt self healing first

### Stop using email for alerts

Emails won't wake someone up, but these can fall into three categories:

1: Response/action required immediately (send to pager/SMS)
2: Awareness needed, but immediate action not required (send to Slack)
3: Record for historical/diagnostic purposes (save to log file)

### Write Runbooks

A runbook is a great way to quickly orient yourself when an alert fires. A good runbook is written for a particular service and answers several questions:

- What is this service, and what does it do?
- Who is responsible for it?
- What dependencies does it have?
- What does the infrastructure for it look like?
- What metrics and logs does it emit, and what do they mean?
- What alerts are set up for it and why?

For every alert include a link to your runbook for that service.

Note: if your runbook contains a lot of steps that are like copy-pasting steps, then you should automate these steps and then delete the alert. A runbook is for when human judgement and diagnosis is necessary to resolve something.

### Arbitrary static thresholds aren't the only way

Having arbitrary thresholds isn't that useful, if they're like, set up to alert you if disk space goes under 10%. I'd probably want to know if it went from 90% free to 10% free in the space of a night.

### Delete and tune alerts

Having lots of alerts that aren't that useful over time leads to *alert fatigure*.

The solution to this is simple: fewer alerts. You can reduce alerts by:

1: Do all your alerts require someone to act?
2: Look at a month's worth of alert history and think: What are they? What were the actions? What was the impact of each one? Are there alerts that can be deleted? Could you redesign the underlying check to be more accurate?
3: What automation can you build to make the alert obsolete?

### Use maintenance periods

If you're doing work on a service and expect it to trigger an alert, set that alert into a maintenance period.

### Attempt automated self-healing first

If the most common action to an alert is to perform a known and documented series of steps, you should automate it and make sure you don't have to worry about it.

The most straightforward way to implement auto-healing is to implement any standardized fix into code and let the monitoring system execute the script instead of notifying a human. If the problem wasn't resolved, THEN send an alert.

## On-Call

On-Call can be really crappy because you might be getting lots of false alarms, unclear alerts and constant firefighting. But you can fix this so it doesn't have to be like this.

### Fixing false alarms

Achieving 100% accuracy is really hard, but you can tune them. When you're on call, compile a list of every alert that was fired and go through them. Think about how they can be improved or if they can be deleted.

### Cutting down on needless firefighting

To get out of firefighting mode, you must spend time and effort on building better underlying systems. You can help this by:

- Making it the duty of on-call to work on systems resiliency and stability during their on-call shift when they aren't fighting fires.
- Explicitly plan for systems resiliency and stability work during the following week's sprint planning based on the previous on-call week

------

When you get to doing some on call rotations, come back and read this section.

------