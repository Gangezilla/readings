# Indexes

- Two options for getting data from a heap file. Give the API a pageId, slotId, or scan through all the tuples.
- An index is a data structure that enables fast lookup and modification of data entries by search key.
  - Lookup can vary depending on index. Can support different operations, typically equality "find me all items in the index that satisfy condition y". Might have indexes for ranges, "find me all items between x and y". You might have 2d ones, often for maps.
    - Many data structures and indexes invented. When someone presents you with an index you want to ask what kind of operations its designed to support.
    - Search key is any subset of columns in the relation, doesn't need to be unique. Could create a search key that's a composite of columns too.
  - Modification: Typically interested in indexes that allow us to fast insert and delete.

## Creating an index

1. Sort heap file by the key we want to index it on, and we leave a bit of space to let us insert easier. We don't need any pointers or anything, cos the pages are physically sorted.

## B+ Tree

- Always balanced, splits at the root.
- B+ tree has data stored at the leaves only instead of the roots.
- Has an occupancy invariant
- Not in sequential order because pages are allocated dynamically.