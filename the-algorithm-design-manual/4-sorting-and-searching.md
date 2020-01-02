# Sorting and Searching

Sorting and searching comes up very often in computer science curriculum for a few reasons:
- Sorting is the basic building block that many other algorithms are built around. By understanding sorting, we obtain an amazing amount of power to solve other problems.
- Most of the interesting ideas used in algo design appear in the context of sorting, like divide and conquer, data structures, and randomized algos.
- Computers have historically spent more time sorting than doing anything else. A quarter of all mainframe cycles were spent sorting data.
- Sorting is the most thoroughly studied problem in comp sci.

## Applications of Sorting
When you have super big datasets, a naive O(n^2) algo just won't cut it. We instead would opt to use some O(n log n)  algos. An important algo design technique is to use sorting as a basic building block, because many other problems become easy once a set of items is sorted. Some applications:
- Sorting: Binary search tests whether an item is in a dictionary in O(log n) time provided all keys are sorted. Search preprocessing is perhaps the single most important application of sorting.
- Closest pair: Given a set of n numbers, how do you find the pair of numbers with the smallest difference between them? Once the numbers are sorted, the closest pair of numbers must lie next to each other somewhere in sorted order meaning a linear-time scan through them completes the job for O(n log n) incl sorting.
- Element uniqueness: This is a special case of the closest-pair problem where we ask if there's a pair separated by a gap of zero. The most efficient algo sorts the numbers and then does a linear scan through checking all adjacent pairs.
- Frequency distribution: Given a set of n items, which element occurs the largest number of times in the set? If the items are sorted, we can sweep left to right and count them since identical elements will be lumped together during sorting.
- Selection: What is the kth largest item in an array? If everythings sorted you can just look at the kth position.

Sorting lies at the heart of many algos. Sorting the data is one of the first things any algo designer should try in the quest for efficiency.

## Pragmatics of Sorting
