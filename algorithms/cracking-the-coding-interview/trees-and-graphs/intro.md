# Trees and Graphs

## Types of Trees

A tree is a data structure composed of nodes.

- Each tree has a root node
- That root node has zero or more child nodes
- Each child node has zero or more child nodes and so on.

The tree cannot contain cycles. The nodes may or may not be in a particular order and they could contain any data as values, and they may or may not have links back to their parent nodes.

A simple class definition for a node is:

```java
class Node {
  public string name;
  public Node[] children;
}
```

### Trees vs Binary Trees

A binary tree is a tree in which each node has up to two children. Not all trees are binary trees. You can have trees with differing numbers of child nodes. Like, you could have one that represented phone numbers and call it a 10-ary tree (1 for each digit). A node is called a 'leaf' node if it has no children.

### Binary Tree vs Binary Search Tree

A binary search tree is a binary tree in which every node fits a specific ordering property:
`all left descendants <= n < all right descendants`

The definition of a binary search tree can vary with respect to equality. For example, sometimes a tree can't have duplicate values. At other times, the duplicate value will be on the right or can be on either side. These are all valid, but check with your interviewer.

### Balanced vs Unbalanced

Not all trees are balanced. Balancing a tree doesn't mean the left and right subtrees are exactly the same size. One way to think about a 'balanced' tree is that it really means something like 'not terribly imbalanced'. It's balanced enough to ensure O(log n) times for insert and find, but not necessarily perfectly balanced. Two types of balanced trees are red-black trees and AVL trees (which you can read up on later).
