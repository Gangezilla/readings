# Perfbook

## When and where to optimize

 Be selective about what you optimize. It's ok to ignore low hanging fruit. 

Don't ignore easy optimizations, better knowledge of algorithms and data structures make more optimizations easy or obvious.

## How to Optimize

Optimization is a tradeoff, and you're usually trading readability for performance improvements. This means you need a solid set of unit tests, as well as a good set of benchmarks to ensure that your changes are having the desired effect on performance.

Good performance work requires knowledge at many different levels. Optimizations should proceed from top to bottom, as optimizations at a system level will have greter impact than expression-level optimizations.

Three questions:

1. Do we have to do this at all?
2. If yes, is this the best algorithm?
3. If yes, is this the best implementation of this algorithm?

## Concrete tips

When thinking of changes you can make to your program, you can either change the data or the code.

### Data changes

This means either adding to or altering the representation o the data you're processing, and could even include preprocessing it into a different more useful format.

- Extra fields: Classic example of this is storing the length of a linked list in the root node. It's a bit harder to keep this updated, but then finding the length is just a lookup instead of an O(n) traversal.
- Extra search indexes: If you need two query types, having an additional view can be a big improvement. A set of structs might have a primary ID that you usually use, but it might have a secondary ID too. Instead of iterating over the slice, you can augment your data structure with a map either from string to ID or diretly to the struct.
- Extra info about elements: Keeping a filter of all the elemnts you've inserted can let you quickly return "no match" for lookups.
- If queries are expensive, add a cache.

With these, you're trading some memory usage for CPU speed.

Reducing memory:

- Rearrange your data: Eliminate structure padding, remove extra fields, use a smaller data type.
- Change to a slower data structure: Simpler data structures often have lower memory requirements.

## Program Tuning

Compilers do a lot of the work here. When you upgrade Go versions, you should make sure that any of your custom optimizations don't get made slower.

You can cache common cases. 