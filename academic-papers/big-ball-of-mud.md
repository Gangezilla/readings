# Big Ball of Mud

## Abstract

This paper discusses the de facto software architecture pattern, 'the big ball of mud' which is a haphazardly structured system

## Intro

- A big ball of mud is haphazardly structured, sprawling sloppy spaghetti code.
  - Information is shared very easily to the point where all important info becomes global.
  - Structure may have never been well defined, or has since eroded.
- What causes good programmers to build ugly systems?

Why does a system become a big ball of mud?

Sometimes they emerge from **throwaway code**. It works, so why fix it? When a problem arises, the quickest fix is often to modify the working code than design a proper program from the ground up.

Sometimes constant changes can undermine a programs structure. Systems that once were tidy become overgrown as **piecemeal growth** gradually allows the system to sprawl uncontrollably. If this keeps going, it becomes like a decaying neighbourhood. The equivalent of gentrification is a sustained commitment to refactoring.

To resolve this, there are some strategies we can take:

Sometimes change takes place one piece at a time. Once established, a strategy of **keeping it working** starts to occur.

You can also start to abstract changes away by **sweeping them under the rugs** and slapping a nice facade around them.

## Forces

- Time: Sometimes there's not enough time to consider long term architectural implications. Architecture often takes a back seat to other things, and is often seen as a luxury. This is because architecture is a long term concern that's realised later in the lifecycle. You can choose to view it as a risk that takes resources, or an opporunity to lay the groundwork for a future advantage.
- Cost: Architecture doesn't pay off immediately, and if it delays a product too long then long-term concerns don't matter. Architecture doesn't matter if your company has gone bankrupt. If you think good architecture is expensive, try bad architecture.
- Experience: Experience can impact architecture in a number of ways. A good architect may lack domain experience, or a domain expert may lack architectural experience. That, and employee turnover can totally wreck an org's institutional memory too.
- Skill: Programmers differ tremendously in their degrees of experience with particular domains, they have different strengths and weaknesses.
- Visibility: The fashion in which we present our architectures affects our perceptions of whether they are good, clear, and elegant. Different people prefer to see these things differently. That, and architecture is often neglected because it's under the hood.
- Complexity: Architecture often gets muddled because software often reflects the complexity of the application domain, which is called "essential complexity". The architecture also often reflects the history of the organisation that built it and the compromises made along the way. It often reflects real life cities, and how a poorly thought out addition can often make things reaaaal bad.
- Change: Architecture is a hypothesis about the future that holds that subsequent change will be handled, but things often don't quite work out that way.
- Scale: Managing a large project is very different from a small one

## Types of bad architectures

### Big ball of mud - Shantytown/spaghetti code

People view shantytowns as bad, but forces conspire to promote their emergence anyway. What do they do right?

They're inexpensive and can be built with unskilled labor. There's little concern for infrastructure because infrastructure requires coordination and capital. Shantytowns fulfill an immediate, local need for housing, higher architectural goals have to wait.

Lots of our software systems are like shantytowns. Investment in tooling and infra is often inadequte. Problems in part of a system erode other portions. This happens often with real buildings too, where as a deadline approaches, compromises have to be made.
