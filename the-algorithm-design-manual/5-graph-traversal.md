# Graph Traversal

Graphs are one of the unifying themes of computer science - an abstract representation that describes the organization of transportation systems, human interactions, and telecommunication networks.
A graph G = (V, E) consists of a set of vertices (the connecting lines) V together with a set E of vertex pairs or edges (the joining node). Graphs are important because they can be used to represent essentially any relationship. For example, they can model a network of roads with cities as vertices and roads between cities as edges.
The key to solving many algorithmic problems is to think of them in terms of graphs. Graph theory provides a language for talking about the properties of relationships and often simplifies pretty messy problems.
The key to using graph algos effectively lies in correctly modeling your problem to take advantage of existing algos. This chapter presents basic data structures and traversal operations for graphs.

## Flavors of Graphs

A graph `G = (V, E)` is defined on a set of vertices V and contains a set of edges E of ordered or unordered pairs of vertices from V. Examples:

- Road network, where vertices represent the cities or junctions, certain pairs of which are connected by roads/edges.
- In the source code of a computer program, the vertices may represent lines of code with an edge connecting lines x and y if y is the next statement executed after x.
- Human interactions, the vertices typically represent people with edges connecting pairs of related souls.

Several fundamental properties of graphs impact the choice of the data structures used to represent them and algos to analyse them. The first step in any graph problem is determining the flavour of graphs you're dealing with:

- Undirected vs Directed - A graph is undirected if edges dont necessarily flow in one direction, so like a road network since most large roads have lanes going in both directions. Otherwise a graph is directed, like cities with one way streets. Program flow graphs are typically directed, because the execution flows from one line into the next and changes direction only at branches. Most graphs of interest are undirected.
- Weighted vs Unweighted - each edge in a weighted graph is assigned a numerical value or weight. The edges of a road network graph might be weighted with their length, drive-time or speed limit
- Simple vs non-simple - certain types of edges complicate the task of working with graphs. A self-loop is an edge containing only one vertex, and an edge is a multiedge if it occurs more than once in the graph. Both of these structures require special care in implementing an algo for, hence any graph that avoids them is called simple.
- Cyclic vs Acyclic - An acyclic graph does not contain any cycles (a cycle graph is a graph in the shape of a circle). Trees are connected, acyclic undirected graphs and are the simples interesting graphs, they're inherently recursive.
- Embedded vs Topological
