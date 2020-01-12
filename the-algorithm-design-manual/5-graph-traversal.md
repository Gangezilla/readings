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
- Embedded vs Topological - a graph is embedded if the vertices and edges are assigned geometric positions. THus, any drawing of a graph is an embedding which may or may not have algorithmic significance.
- Implicit vs Explicit - Certain graphs aren't explicitly constructed and then traversed, but built as we use them. A good example is in backtrack search. The vertices of this search graph are the states of the search vector, while edges link pairs of states that can be directly generated from each other.
- Labeled vs unlabeled - each vertex is assigned a unique name or identifier, but in unlabeled graphs no such distinctions have been made.

### The Friendship Graph

To demonstrate the importance of proper modeling, let's consider a graph where vertices are people and there are edges between the two of them if they're friends. These graphs are called social networks. We use this opportunity to demonstrate the terminology described above:

- If I'm your friend, does that mean you're my friend? - This question really asks if the graph is directed. The "heard-of" graph is directed, since I've heard of famous people who don't know me. The "had-sex-with" graph is undirected, since a partner is involved. A 'friendship' graph is an undirected graph.
- How close a friend are you? - In weighted graphs, each edge has an associated numerical attribute. We could model the strength of a friendship by associating each edge with an appropriate value.
- Am I my own friend? - This address whether the graph is simple, meaning it contains no loops and no multiple edges. An edge of the form (x, x) is said to be a loop. Sometimes people are friend in different ways. If someone is friends at college and at work, we can model their relationship using multiedges. Simple graphs are often simpler to work with, so we might be better off declaring that no one is their own friend.
- Who has the most friends? - The degree of a vertex is the number of edges adjacent to it. The most popular person defines the vertex of highest degree in the friendhsip graph. In dense graphs most vertices have high degrees as opposed to sparse graphs with relatively few edges. In a regular graph, each vertex has exactly the same degree.
- Do my friends live near me? - A full understanding of social networks requires an embedded graph, where each vertex is associated with the point that they live.
- Oh, you als know her? - Social networks are built on the premise of explicitly defining the links between members and their member friends.
- Are you an individual or just faceless in the crowd? - This boils down to if the graph is labeled or unlabeled.

Graphs can be used to model a wide variety of structures and relationships. Graph-theoretic terminology gives us a language to talk about them.

## Data Structures for Graphs

Selecting the right graph data structure can have an enormous impact on performance. You've got two basic choices, assuming the graph G = (V, E) contains n vertices and m edges:

- Adjacency Matrix: We can represent G using n x n matric M, where element M[i, j] = 1. If (i, j) is an edge of G and 0 if it isn't. This lets us figure out if a particular edge is in a graph, and lets us insert and delete edges quickly. It may use excessive space for graphs with many vertices and few edges though.
- Adjacency Lists: We can more efficiently represent sparse graphs by using linked lists to store the neighbours adjacent to ech vertex. Adjacency lists make it harder to verify whether a given edge is in a graph, since we must search through the appropriate list to find the edge. However, it's easy to design graph algos that avoid any need for such queries. We typically sweep through all edges of the graph in one pass via a breadth-first or depth-first traversal and update the implications of the current edge as we visit it.

Adjacency lists are the right data structure for most applications of graphs. For each graph we keep count of the number of vertices and assign each vertex a unique number from 1 to nvertices. We represent the edges using an array of linked lists:

```c
#define MAXV 1000 // max number of vertices

typedef struct {
  int y; // adjacency info
  int weight; // edge weight, if any
  struct edgenode *next; // next edge in list
}

typedef struct {
  edgenode *edges[MAXV+1] // adjacency info
  int degree[MAXV+1] // number of meaningful entries for vertex
  int nvertices; // number of vertices in graph
  int nedges; // number of edges in graph
  bool directed; // is the graph directed
} graph;
```

To demo the use of this data structure, we show how to read a graph from a file. A typical graph format consists of an initial line featuring the number of vertices and edges in the graph, followed by a listing of the edges at one vertex pair per line.

```c
initialize_graph(graph *g, bool directed) {
  int i; // counter;

  g->nvertices = 0;
  g->nedges = 0;
  g->directed = directed;

  for (i = 1; i <= MAXV; i++) {
    g->degree[i] = 0;
    g->edges[i] = NULL;
  }
}
```

Actually reading the graph requires inserting each edge into this structure:

```c
read_graph(graph *g, bool directed) {
  int i; // counter
  int m; // number of edges
  int x, y; // vertices in edge (x, y)

  initialize_graph(g, directed);
  scanf("%d %d", &(g->nvertices, &m);

  for (i = 1; i<=m; i++) {
    scanf("%d, %d", &x, &y);
    insert_edge(g, x, y, directed)
  }
}
```

```c
insert_edge(graph *g, int x, int y, bool directed) {
  edgenode *p; // temp pointer
  p = malloc(sizeof(edgenode)) // allocate edgenode storage

  p->weight = NULL;
  p->y = y;
  p->next = g->edges[x];

  g->edges[x] = p; // insert at head of list

  g->degree[x]++;

  if (directed == FALSE) {
    insert_edge(g, y, x, TRUE);
  } else {
    g->nedges++;
  }
}
```

It's a good idea to use a well-designed graph data type like LEDA or Boost as a model for building your own.

Even elementary problems like initializing data structures can prove to be bottlenecks in algo development. Most programs working with large amounts of data have to run in linear or almost linear time. Such tight perf demands leave no room to be sloppy. Once you focus on the need for linear time performance, an appropriate algorithm or heuristic can usually be found to do the job.

## Traversing a Graph
