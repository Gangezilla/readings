# Sorting and Searching

Sorting and searching comes up very often in computer science curriculum for a few reasons:

- Sorting is the basic building block that many other algorithms are built around. By understanding sorting, we obtain an amazing amount of power to solve other problems.
- Most of the interesting ideas used in algo design appear in the context of sorting, like divide and conquer, data structures, and randomized algos.
- Computers have historically spent more time sorting than doing anything else. A quarter of all mainframe cycles were spent sorting data.
- Sorting is the most thoroughly studied problem in comp sci.

## Applications of Sorting

When you have super big datasets, a naive O(n^2) algo just won't cut it. We instead would opt to use some O(n log n) algos. An important algo design technique is to use sorting as a basic building block, because many other problems become easy once a set of items is sorted. Some applications:

- Sorting: Binary search tests whether an item is in a dictionary in O(log n) time provided all keys are sorted. Search preprocessing is perhaps the single most important application of sorting.
- Closest pair: Given a set of n numbers, how do you find the pair of numbers with the smallest difference between them? Once the numbers are sorted, the closest pair of numbers must lie next to each other somewhere in sorted order meaning a linear-time scan through them completes the job for O(n log n) incl sorting.
- Element uniqueness: This is a special case of the closest-pair problem where we ask if there's a pair separated by a gap of zero. The most efficient algo sorts the numbers and then does a linear scan through checking all adjacent pairs.
- Frequency distribution: Given a set of n items, which element occurs the largest number of times in the set? If the items are sorted, we can sweep left to right and count them since identical elements will be lumped together during sorting.
- Selection: What is the kth largest item in an array? If everythings sorted you can just look at the kth position.

Sorting lies at the heart of many algos. Sorting the data is one of the first things any algo designer should try in the quest for efficiency.

## Pragmatics of Sorting

There's many algorithmic applications of sorting, but the primary issue is: in what order do we want our items sorted? The answers to this are application specific:

- Increasing or decreasing order
- Sorting just the key or an entire record?: Sorting a data set involves maintaining the integrity of complex records. A mailing list may be sorted by names, but they'd better retain the link between names and addresses. Thus, we need to specify which field is the key field in any complex record and understand the full extent of each record.
- What should we do with equal keys?: Elements with equal keys will all bunch together, but sometimes the order matters and in that case you may need to resort to secondary keys to resolve ties meaningfully. If you leave items in the same relative order, the algo is called _stable_. Unfortunately few sorting algos are stable. You can just leave resolving ties to the algo, but some algos (like quick sort) run into perf trouble unless explicitly engineered to deal with large number of ties.
- Non numerical data?: Libraries have very specific and complicated rules concerning the relative order of characters and punctuation.

You usually compare functions with a comparison function, like `a < b`. By abstracting comparison to look like this, we can implement a sorting algo independent of it.

## Heapsort: Fast Sorting via Data Structures

We start with data structure design, because one of the most dramatic algo improvements via appropriate data structures happens in sorting. Selection sort is a simple-to-code algo that repeatedly extracts the smallest remaining element from the unsorted part of the set. A previous implementation partitioned the input array into sorted and unsorted regions. To find the smallest item, we performed a linear sweep through the unsorted portion of the array and swapped the smallest item with the *i*th item and we usually end up with around O(n^2) time. This gives us scope to improve the data structure because it takes O(1) time to remove a particular item from an unsorted array once it's been located, but O(n) time to find the smallest item, which is exactly the sort of operation supported by a priority queue. If we replace the array with a priority queue or heap or balanced binary tree, operations now take O(log n) time instead of O(n). The name, heapsort, is a misnomer, as heapsort is nothing but an implementation of selection sort using the right data structure.

### Heaps

Heaps are a simple and elegant data structure for efficiently supporting the priority queue operations insert and extract-min. They work by maintaining a partial order on the set of elements which is weaker than the sorted order yet stronger than random order. A heap-labeled tree is defined to be a binary tree such that the key labeling of each node dominates the key labeling of each of its children. The heap lets use represent binary trees without using any pointers by storing data as an array of keys and using the position of the keys to implicitly satisfy the role of the pointers.

## Mergesort

Recursive algos reduce large problems into smaller ones. A recursive approach to sorting involves partitioning the elements into two groups, sorting each of the smaller problems into two groups, sorting each of the problems recursively, and then interleaving the sorted lists to order the elements. The base case of the recursion occurs when the subarray to be sorted consists of a single element.
The efficiency of mergesort depends upon how efficiently we combine two sorted halves into a single sorted list, and the most efficient way is to merge the two lists together. The smallest overall item in two lists sorted in increasing order must sit at the top of one of the two lists.
Mergesort is a great algo for sorting linked lists, because it doesn't rely on random access to elements as does heapsort or quicksort. It's a classic divide-and-conquer algo.
We get ahead of the game when we can break one large problem into two smaller problems because smaller problems are easier to solve.

### Implementation

You have an algo that looks kind of like this:

```c
mergesort(item_type s[], int low, int high) {
  int i; // counter
  int middle; // index of middle element

  if (low < high) {
    middle = (low+high)/2;
    mergesort(s, low, middle);
    mergesort(s, middle+1, high);
    merge(s, low, middle, high);
  }
}
```

Merging is the complicated part, because we have to put our merged array somewhere. To avoid losing any elements, we copy each subarray into a separate queue and then merge these elements back into the array.

## Quicksort: Sorting by Randomization

Suppose we select a random item p from the n items we need to sort. Quicksort separates the n - 1 other items into a pile containing all elements that appear before p, and a high pile containing all the elements that appear after p. Partitioning like this buys us two things:

- The pivot element, p, ends up in the exact array position it will reside in the final sorted order
- After partitioning no element flops to the other side in the final sorted order which means we can now sort the elements to the left and right of the pivot independently. This gives us a recursive sorting algo since we can use the partitioning approach to sort each subproblem.

It kinda looks like this:

```c
quicksort(item_type s[], int l, int h) {
  int p; // partition index

  if ((h - 1) > 0) {
    p = partition(s, l, h);
    quicksort(s, l, p - 1);
    quicksort(s, p + 1, h);
  }
}
```

We can partition the array in one linear scan by maintaining three sections of the array: less than the pivot, greater than or equal to the pivot, and unexplored.

Since the partitioning step consists of at most n swaps, it takes linear time in the number of keys. As with mergesort, quicksort builds a recursion tree of nested subranges of the n-element array and it also spends linear time processing (partitioning instead of merging), and it also runs in O (n x h) where h is the height of the recursion tree. The difficulty is that the height of the tree depends upon where the pivot element ends up in each partition.
At it's worst, quicksort performs at O(n^2). This means it's worse than heapsort or mergesort, which means it has to be good on average.

### Intuition: The Expected Case for Quicksort

The expected performance of quicksort depends upon the height of the partition tree constructed by random pivots. Quicksort is on average O(n log n). The best possible selection for the pivot would be the median key, but we only have a probabibility of 1/n of randomly selecting the median as pivot which is quite small.
Suppose a key is good enough if it lies in the center half of the sorted space of keys, these are quite plentiful and we'll pick one 1/2 the time. Even if we get half good and half bad pivot points, we end up with O(log n).
On average, random quicksort partition trees are very good.

### Randomized Algos

If we gave our quicksort implementation a sorted array as input, it would pick the worst possible pivot at each step and run in quadratic time. If we add an initial step where we randomly permute the order of the n elements before we try to sort them we could do this in O(n) time and guarantee that we'd expect O(n log n) running time.

Randomization is a powerful tool to improve algos with bad worst-case but good average-case complexity.
Hypothetically we have n bolts and n nuts to match them with. We can go through each bolt and each nut which gives us O(n^2). However we can pick a random bolt and we'd on average get halfway through the set of nuts before finding a match. Randomized quicksort achieves the desired expected-case running time if we sort the nuts and bolts by size because it would mean the ith largest nut must match the ith largest bolt. What's interesting about this problem is that no simple deterministic algo (being that the same input will return the same result every time). It illustrates how randomization makes the bad case go away, leaving behind a simple and beautiful algorithm.

## Distribution Sort: Sorting via Bucketing

We could sort name for a telephone book by partitioning them according to the first letter of the last name, which will make 26 different buckets. We can then sort each pile individually and concat the sorted piles together at the end. If the names are distributed evenly, the resulting 26 sorting problems should be smaller than the original problem. We can then partition each pile based on the second letter of each name to generate smaller and smaller piles. The names will then be sorted as soon as each bucket contains only a single name.
Bucketing is a very effective idea whenever we're confident that the data distribution will be roughly uniform.

## Binary Search and Related Algos - p132 (to be returned to)
