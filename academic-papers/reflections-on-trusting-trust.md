# Reflections on Trusting Trust - Ken Thompson 1984

## Stage 1
"More precisely stated, the problem is to write a source program that, when compiled and executed, will produce as output an exact copy of its source".

"simple modification to the compiler that
will deliberately miscompile source whenever a particular pattern is matched. If this were not deliberate, it
would be called a compiler "bug." Since it is deliberate,
it should be called a "Trojan horse.""

The author creates a self reproducing trojan horse in the C compiler and goes on to say that you can't trust code that you didn't totally create yourself. As you end up getting deeper and deeper through the levels of abstraction, how can you really trust what you rely on? I find this pretty interesting in a post-npm world, where SO much of the code we write is reliant upon zillions of other libraries. I mean, there's the likelihood that some bad bit of code has slipped through the cracks.

There was that scandal on GitHub a while ago where that person handed over their library and someone else pushed some bad code to it. It's good that was caught, but what about the stuff that hasn't been caught?
