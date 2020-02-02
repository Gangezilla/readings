# Stacks and Queus

## Stack

In certain types of problems it can be favourable to store data in a stack rather than an array. Stacks use LIFO (last-in first-out) ordering. Think of a stack of dinner plates, the most recent item added is the first to be removed. They typically use these operations:

- `pop()`: Remove the top item from the stack
- `push()`: Add an item to the top of the stack
- `peek()`: Return the top of the stack
- `isEmpty()`: Return the top of the stack.

Stacks don't offer constant-time access to the ith item, however, they do allow constant time adds and removes as they don't require shifting elements around.

Stacks are often useful in certain recursive algorithms. Sometimes you need to push temporary data onto a stack as you recurse, but then remove them as you backtrack. It can also be used to implement a recursive algorithm iteratively.

## Queues

A queue implements FIFO (first-in first-out) ordering. As in a line or queue at a ticket stand, items are removed from the data structure in the same order that they're used. They typically have these operations:

- `add(item)`: Add an item to the end of the list.
- `remove()`: Remove the first item in the list
- `peek()`: Return the top of the queue
- `isEmpty()`: Return true if the queue is empty.

Queues can also be implemented as linked lists, in fact, they're essentially the same thing as long as items are added and removed from opposite sides.

Queues are useful in breadth-first search, because if we used a queue to store a list of the nodes that wee need to process.
