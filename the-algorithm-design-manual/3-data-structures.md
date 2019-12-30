# Data Structures

Important classes of abstract data types such as containers, dictionaries and priority queues have many different but functionally equivalent data structures that implement them.
Changing a data structure doesn't change the correctness of the program, since we presumably replace a correct implementation with a different correct implementation, however the new implementation realizes different tradeoffs so the total performance can improve dramatically.

## Contiguous vs Linked Data Structures
Data structures are either:
- Contiguously-allocated structures meaning they're composed of single slabs of memory and include arrays, matrices, heaps and hash tables.
- Linked data structures, which are composed of distinct chunks of memory bound together by pointers, and include lists, trees and graph adjacency lists.

### Arrays
Arrays are structures of fixed-size data records such that each element can be efficiently located by its index. Advantages of contiguously allocated arrays include:
- Constant-time access given the index, because the index of each element maps directly to a particular memory address, we can access arbitrary data items instantly provided we know the index.
- Space efficency, arrays consist purely of data, so no space is wasted with links or other formatting information. Further, end-of-record information is not needed because arrays are built from fixed-size records
- Memory locality, meaning they're all located next to each other. Programming functions often iterate through all elements in a data structure and arrays are good because they exhibit excellent memory locality. Physical continuity between successive data accesses helps exploit high speed cache memory.

The downside of arrays are that we can't adjust their size in the middle of execution. This is unless we're using dynamic arrays. In most languages this involves allocating a new contiguous array when we run out of space, copying the old array to the lower half of the new one.
This isn't as inefficient as you'd think as most elements don't suffer too much upheaval, if half the elements move once, a quarter of them twice and so on, the total work of managing the dynamic array is the same O(n) as it would have been if a single sufficient array were allocated in advance.

### Pointers and Linked Structures
Pointers are the connections that hold the pieces of linked structures together. Pointers represent the address of a location in memory. A variable storing a pointer to a given data item can provide more freedom than storing a copy of the item itself.
A pointer, p, is assumed to give the address in memory where a particular chunk of data is located. Pointers in C have types declared at compiler time. We use *p to denote the item that is pointed to by pointer p, and &x to denote the address of a particular variable x. A special NULL pointer is used to denote structure-terminating or unassigned pointers.
All linked data structures share certain properties as revealed by the following linked list type declaration:
```c
  typedef struct list {
    item_type item; // data item
    struct list *next; // point to successor
  } list;
```

- Each node in our list contains one or more data fields that retain the data we need to store.
- Each node contains a pointer field to at least one other node, meaning much of the space used in linked data structures has to be devoted to pointers and not data.
- Finally, we need a pointer to the head of the structure so we know where to access it.

### Comparison
The relative advantages of linked lists over static arrays:
- Overflow on linked structures can never occur unless the memory  is actually full
- Insertions and deletions are simpler than for contiguous lists.
- With large records, moving pointers is easier and faster than moving the items themselves

While the relative advantages of arrays include:
- Linked structures require extra space for storing pointer fields
- Linked lists don't allow efficient random access to items.
- Arrays allow better memory locality and cache performance than random pointer jumping.

Dynamic memory allocation provides us with flexibility on how and where we use our limited storage resources.

Accessing them recursively:
- Lists: chopping the first element off a linked list leaves a smaller linked list, which works the samw way for strings
- Arrays: Splitting the first k elements off an n element array gives two smaller arrays.

## Stacks and Queues
We use the term container to denote a data structure that permits storage and retrieval of items independent of content. By contrast dictionaries are abstract data types that retrieve based on key values or content. They're distinguished by the retrieval order they support, and in stacks and queues they depend on the insertion order.
- Stacks: Support retrieval by last in, first out (LIFO) order. They're simple and efficient and are probably the right container to use when retrieval order doesn't matter. You push something onto the stack, and you pop to retrieve. LIFO arises in many real world contexts. People in a subway, food in the fridge...
- Queues: Support retrieval in first in, first out (FIFO) order. Queues help you minimise the maximum time spent waiting. The average waiting time will be the same regardless of FIFO or LIFO. Queues are trickier to implement than stacks and are appropriate where order matters. Put is called enqueue, and get is called dequeue.

Stacks and queues can be implemented using arrays or linked lists, the key issue is whether an upper bound on the size of the container is known in advance, which permits whether you can use a statically-allocated array or not.

## Dictionaries
The dictionary data type permits access to data items by content. You stick an item into a dictionary so you can find it when you need it. Dictionaries have these primary operations:
- Search: Given a search key k, return a pointer to the element in dictionary whose key value is k if it exists
- Insert: Given a data item, add it to the set in the dictionary
- Delete: Given a pointer to a data item in the dictionary, remove it from the dictionary.

Certain dictionary data structures also support other useful operations:
- Max or Min: Retrieve the item with the largest or smallest key, which allows it to serve as a priority queue.
- Predecessor or Successor: Retrieve the item from the dictionary whose key is immediately before or after a certain key, which enables us to iterate through the elements of the data structure.

Many common data processing tasks can be handled using dictionary operations, such as removing all duplicate names from a mailing list and printing the results. There's also more complex dictionary implementations such as binary  search trees and hash tables.

### Perf of dictionaries
A sorted dictionary is generally much faster than an unsorted one, except for the insert operation.
Unsorted:
- Search takes linear time in the worst case, which is when the key is not found at all.
- Insertion takes constant time, as we increment the number of items and then insert at this point in the array.
- Deletion is trickier. Although we have a pointer to the element we need to delete, doing so leaves a hole that must be filled. The easiest way to do this is to overwrite this element with the last element, and then decrement the count.

An unsorted dictionary reverses our notions of what is easy and hard, as searches are now much faster but insertions and deletions become much more expensive.

Data structure design must balance all the different operations it supports. The fastest data structure to support both operations A and B may well not be the fastest structure to support either operation A or B.

## Binary Search Trees
We've seen data structures that allow fast search or flexible update, but not fast search AND flexible update. Binary search requires we have fast access to two elements, the median elements above and below the given node. To combine these ideas, we need a 'linked list' with two pointers per node, which is the basic idea behind binary search trees.

A *rooted binary tree* is recursively defined as either being empty or consisting of a node called the root, together with two rooted binary trees called the left and right subtrees. A binary search tree labels each node in a binary tree with a single key such that for any node labeled x, all nodes in the left subtree of x have keys < x while all nodes in the right subtree of x have keys > x. For any binary tree on n nodes, and any set of n keys, there is exactly one labeling that makes it a binary search tree.

### Implementing Binary Search Trees
Individual binary tree nodes have left and right pointer fields, an optional parent pointer and a data field, so a struct of one may look like:
```c
typedef struct tree {
  item_type item;
  struct tree *parent;
  struct tree *left;
  struct tree *right;
} tree;
```
The basic operations supported by binary trees are searching, traversal, insertion and deletion.

#### Searching in a tree
The binary search tree labeling uniquely identifies where each key is located. Start at the root. Unless it contains the query key x, proceed left or right depending on whether x occurs before or after the root key. You can do this recursively, because the left and right subtrees of a binary search tree are themselves binary search trees.

```c
tree *search_tree(tree *l, item_type x) {
  if (l == NULL) return(NULL);
  if (l->item == x) return(l);
  if {
    (x < l->item) return(search_tree(l->left, x));
  } else {
    return (search_tree(l->right, x));
  }
}
```

#### Finding Minimum and Maximum Elements in a Tree
Implementing the find-minimum operation requires knowing where the minimum element is in the tree. By definition, the smallest key must reside in the left subtree of the root, which means the minimum element must be the leftmost descendant and the maximum must be the rightmost element.

```c
tree *find_minimum(tree *t) {
  tree *min;

  if (t == NULL) return NULL;
  min = t;
  while(min->left != NULL) {
    min = min->left;
  }
  return (min);
}
```

You'd do the same but to the right for the maximum.

#### Traversal in a Tree
Visiting all the nodes in a rooted binary tree is important in many algos, it's a special case of traversing the nodes and edges in a graph. A prime application of tree traversal is listing the labels of the nodes. Binary search trees make it easy to report the labels in sorted order by visiting the nodes recursively via in-order traversal.

```c
void traverse_tree(tree *l) {
  if (l != NULL) {
    traverse_tree(l->left);
    process_item(l->item);
    traverse_tree(l->right);
  }
}
```

This works by basically going all the way down to the bottom of the tree, and then going back up the tree once its hit the bottom, processing each node and then doing the same for the rightmost nodes of an individual node.

This processes each node once which runs in O(n) time, where n is the number of nodes. Alternate traversal orders come from changing the position of process_item relative to the traversals of the left and right subtrees. Processing the item first yields a pre-order traversal, while processing it last gives a post-order traversal. This isnt as useful with search trees, but can help when the tree represents arithmetic or logical expressions.

#### Insertion in a Tree
We can only insert a new item into a binary search tree in a single correct spot. We have to replace the NULL pointer found in T after an unsuccessful query for the key k. We use recursion to combine search and node insertion.

```c
insert_tree(tree **l, item_type x, tree *parent) {
  tree *p;
  if (*l == NULL) {
    p = malloc(sizeof(tree)); // allocate new node
    p->item = x; // set value of new node to value
    p->left = p->right = NULL; // set right and left to null, this is a leaf node
    p->parent = parent;
    *l = p; // link into parent's record
    return;
  }

  if(x < (*l)->item) { // find the spot the item should live by searching through the tree.
    insert_tree(&((*l)->left), x, *l)
  } else {
    insert_tree(&((*l)->right), x, *l)
  }
}
```

#### Deletion from a Tree
Deletion is trickier, because removing a node means linking its two descendat subtrees back into the tree somewhere else. There's a few different cases:
- Deleting a leaf node that has no children is easy, and can be deleted by simply clearing the pointer to the given node. I think you do this by going back up to it's parent and setting the left or right as NULL.
- If the node to be deleted has one child, that's ok too. There's one parent and one grandchild, and we can link the grandchild directly to the parent without violating the in-order labeling property of the tree.
- If the node to be deleted has two children, the solution is to relabel this node with the key of its immediate successor in sorted order. This successor must be the smallest value in the right subtree, which is the leftmost descendant in the right subtree.

### How good are binary search trees?
When implemented using binary search trees, all three dictionary operations take O(h) time, where h is the height of the tree. When a tree is perfectly balanced, the smallest height is `h = log n`. This is hella good, but the tree **must** be perfectly balanced.
Bad things can happen when building trees through insertion. If you inserted all your keys in order, you'd get a weird skinny tree with only right pointers. One of the ways to do this is through randomisation.

### Balanced Search Trees
Balanced search trees are usually good, but if we get unlucky we can have a linear-height tree in the worst case. The best solution is an insertion/deletion procedure which adjusts the tree a little after each insertion. Sophisticated balanced binary search tree data structures have been developed that guarantee the height of the tree to always be O(log n), meaning all dictionary operations take O(log n) time.
From an algorithm design perspective, it's important to know these trees exist and can be used as black boxes to provide an efficient dictionary implementation.

Picking the wrong data structure for the job can be disastrous in terms of performance. Identifying the very best data structure isn't as critical because there can be several choices that perform similarly.

## Priority Queues
