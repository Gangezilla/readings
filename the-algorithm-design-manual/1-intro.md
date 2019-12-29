# Chapter 1
- There is a fundamental difference between algorithms which always produce a correct result, and heuristics, which may do a good job but don't provide any guarantee.
- Reasoning about an algorithm is impossible without a description of the sequence of steps to be performed, whether this is in English, pseudocode or actual code. Pseudocode is a good happy medium usually. The author prefers to describe ideas in English, and then move onto pseudocode after this is nailed down.
- The heart of any algorithm is an idea. If your idea is not clearly revealed when you express an algorithm, then you're using too low-level a notation to describe it.
- You'll also need a problem specification, which has two parts. The set of allowed input instances, the required properties of the output.
- An important and honorable technique in algorithm design is to narrow the set of allowable instances until there is a correct and efficient algorithm. For example, we can restrict a graph problem from general graphs down to trees, or a geometric problem from two dimensions down to one.
- Common traps are asking an ill-defined question, and creating a compound goal.
- The best way to prove that an algorithm is incorrect is to produce an instance in which it yields the incorrect answer with a counter-example. Good counter-examples are verifiable and simple, so that you can easily state why a given algorithm is incorrect.
- Hunting for counter-examples is worth practicing. Some tips:
  - Think small, as there's often a simple example that a complex algorithm fails on.
  - Think exhaustively, as there's only a small number of possibilities for the smallest nontrivial value of n.
  - Hunt for the weakness, if a proposed algorithm is of the form "always take the biggest" (ie a greedy algorithm) think about why that might be the wrong thing to do.
  - Go for a tie, a devious way to break a greedy heuristic is to provide instances where everything is the same size. Suddenly the heuristic is to provide instances where everything is the same size.
  - Seek extremes, many counter examples are mixtures of huge and tiny, left and right, near and far. It's usually easier to verify or reason about extreme examples.
  - Therefore, searching for counterexamples is the best way to disprove the correctness of a heuristic.
- Failure to find a counterexample of a given algorithm doesn't mean that its "obvious" that the algo is correct, a proof or demonstration is still needed.
- You've got this thing called induction, which is a technique for proving a statement (formula or theorem) that's asserted about every natural number. Considering insertion sort, we can reason that it is correct inductively. Many recursive algos work similarly.

## Stop and think: Incremental Correctness
- We have a base case of 0, where we return 1.
- y = n - 1. It's easy to prove this with the even numbers because we explicitly handle it.

## Summations
- Mathematical summation formulae arise often in algo analysis. Proving the correctness of summation formulate is a classic application of inductrrion. Summation formula are concise expressions describing the addition of an arbitrarily large set of numbers.
- There's two basic classes of summation formulae, arithmetic and geometric progressions.

## Modeling the Problem
- Modeling is the art of formulating your application in terms of precisely described, well-understood problems. Proper modeling is the key to applying algorithmic design techniques to real-world problems. Proper modeling can eliminate the need to design or even implement algorithms by relating your application to what has been done before. This is because many algorithms are designed to work on  abstract data sets, but your problems will most likely involve a real-world object or problem. Therefore, learning to describe your problem abstractly will allow you to lean on these prior solutions.
- Odds are good that others have stumbled upon your problem before you, perhaps in very different contexts. To figure this out you need to search  in terms of computing properties of common structures, such as:
  - **Permutations**, which are arrangements or ordering of items. Like, [4, 3, 2, 1] and [1, 2, 3, 4] are distinct permutations of the same set. Permutations are likely the object in question whenever your problem seeks an arrangement, tour, ordering or sequence.
  - **Subsets**, which represent selections from a set of items. Like, [1, 3, 4] and [2] are two distinct subsets of the first four integers. Order doesn't matter in subsets the way it does with permutations, so the subsets [1, 3, 4] and [4, 3, 1] are considered identical. Subsets are likely the object in question whenever your problems seeks a cluster, collection, committee, group, packaging or selection.
  - **Trees**, which represent hierarchical relationships between items. Trees are likely the object in question whenever your problem seeks a hierarchy, dominance relationship, acestor/descendat relationship, or taxonomy.
  - **Points**, which represent locations in some geometric space. They're likely the object in question when your problems work on sites, positions, data records, or locations.
  - **Polygons**, which represent regions in some geometric spaces. Polygons and polyhedra are likely the object in question whenever you're working on shapes, regions, configurations or boundaries.
  - **Strings**, which represent sequences of characters or patterns. Strings are liekly the object in question when you are dealing with text, characters, patterns or labels.
- Familiarity with these problems is important, because they provide the language we use to model applications.
- The act of modeling reduces your application to one of a small number of existing problems and structures. Such a process is inhernetly constraining and certain details might not fit easily into the given target problem.
- Modeling your application in terms of well defined structures and algorithms is the most important single step towards a solution.

### Recursive Objects
- Learning to think recursively is learning to look for big things that are made from smaller things of exactly the same type as the big thing.
- Recursive structures occur everywhere in the algorithmic world. Each of the above data structures can be thought of recursively, you just have to know how:
  - **Permutations**, delete the first element of a permutation of things and you get a permutation of the remaining n-1 things
  - **Subsets**, every subset [1, ... n] contains a subset of [1, ... n- 1] made visible by deleting element n if it is present.
  - **Trees**, delete the root of a tree and you get a collection of smaller trees, same with a leaf.
  - **Graphs**, delete any vertex from a graph and you get a smaller graph.
  - **Points**, take a cloud of points and separate them into two groups and you have a smaller cloud of points.
  - **Polygons**, inserting any internal chord between two nonadjacent vertices of a simple polygon on n vertices cuts it into smaller polygons.
  - **Strings**, delete the first character from a string, and you've just got a shorter string.
- Recursive descriptions of objects require both decomposition rules and basis cases.

## Exercises
1-1: If both a and b are negative, a + b can be less than min(a, b).
  a = -3, b = -8
  -3 + -8 = -11
  min(-3, -8) = -8

1-2: If either a or b is negative, a x b can be less than min(a, b).
  a = -1, b = -100
  -1 x 100 = -100
  min(-1, 100) = -1

1-3: If you had two roads, one at 5km/h that's 10km, but you had one thats 11km at 100km/h the longer road would be the shortest one.

1-4: Could be similar to the above question, where you have a road with two turns and you can go faster on that road, vs a  road with one turn. Also depends on how you're defining a turn, like, it could be this big hectic corkscrew like the kind you'd use to get onto a motorway vs two quick little turns.

1-5a: Putting the elements in left to right, with the given example, where T = 22 won't work.
1 + 2 = 3
3 + 5 = 8
8 + 9 = 17
17 + 10 = 27
Therefore, this doesn't work reliably.

1-5b: In the given example, putting the elements in smallest to largest won't work reliably, where T = 22.
1 + 2 = 3
3 + 5 = 8
8 + 9 = 17
17 + 10 = 27
Therefore, this doesn't work reliably.

1-5c: Adding the numbers in largest to smallest, with the given example, this won't work reliably either, because there's a good chance you'll overshoot when T = 22.
10 + 9 = 19
19 + 5 = 24
Therefore, this doesn't work reliably.

1-6: Let U = {1, 2, 3, 4, 5, 6}, with S1 = {1,2,3,4}  S2 = {1,2,5} S3 = {3,4,6}.
Largest set is S1 {1,2,3,4}, so deleting these elements from U gives us {5,6}. This means we would need to bring in S2 for 5, and S3 for 6. This means we would need all three sets for this algorithm, but the most efficient way to complete the universal set would be by pulling in just S2 and S3.
