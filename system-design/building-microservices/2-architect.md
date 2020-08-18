# The Evolutionary Architect

This chapter is about the role of an architect in an org.

## Inaccurate Comparisons

- Architects have an important job; making sure we have a cohesive technical vision that delivers the system our customers need.
- Although this is compared to a real world architect who operates with much more rigour and structure than we do.

## An evolutionary vision for the architect

- We should think of our role more as town planners than architects of buildings, like in SimCity. A town planners role is to look at a bunch of information sources and then optimise the layout to best suit the needs of the citizens.
- The way that they influence how the city evolves isn't like "build this here", but more zoning a city. Rather than worry about what happens in one zone, the town planner spends more time working out how people and utilities move from one zone to another.
- Cities change over time evolving to how its occupants use it or as external forces shape it. Town planners do their best to anticipate change.
- As software devs, our software needs to change for users and other devs. We have a duty to ensure that a system is _habitable_ 
- A town planner needs to know when their plan isn't being followed. The number of times he needs to get involved to correct direction should be minimal, but if someone tries to build a sewage plant in a residential area they should be able to shut it down.
- Our architects need to set direction broadly, and get involved in very limited situations.

### Zoning

- Our zones are our service boundaries. As architects we need to be less concerned about what happens inside our zones, but more what happens _between_ them.
- This means we need to spend time thinking about how our services communicate, and ensuring we can properly monitor the overall health of our system.
- This means you can let teams make decisions within their zones. Although there's tradeoffs here, do you standardise on languages, DB choice...
- We should "be worried about what happens between the boxes and be liberal in what happens inside".
- When you're architecting something, it's really valuable to sit and pair with the devs doing the work to empathise. Makes sense, they're your customers after all.

## Strategic Goals

Your job as an architect is to align with where the company is going. The key is that this is where your organisation is headed so you need to make sure the tech is aligned to it.

## The required standard

When you're working on practices and trade-offs, it's important to define what a good service looks like. "It needs to be a cohesive system made of many small parts with autonomous lifecycles but all coming together"

### Monitoring