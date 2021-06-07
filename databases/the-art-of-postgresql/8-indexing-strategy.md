# Indexing Strategy

- Indexes allows the system to have new options to find the data your queries need.

## Indexing for Constraints

Postgres uses indexes for modeling primary key, unique and exclusion constraints. This comes from it's MVCC (multiversion concurrency control), which means each SQL statement sees a snapshot of data asit was some time ago. This prevents statements from viewing inconsistent data produced by concurrent transactions, providing transaction isolation for each DB session.

If we think about how to implement the unique constraint, we soon realise that to be correct the implementation must prevent two concurrent statements from inserting duplicates.

So when you declare a unique, primary key or exclusion constraint, postgres creates an index for you.

## Indexing for Queries

- An index duplicates data in a specialised format made to optimise a certain type of searches.
- There's a maintenance cost to having indexes, as inserting, updating and deleting needs to maintain the indexes too.

There are multiple index access methods:

- B-tree (balanced tree): Most commonly used because they're efficient and provide an algo that applies to most cases
- GiST (generalized search tree): Let's you index `point` and `range` data types.
- GIN (generalized inverted index): Appropriate for arrays, or full texat search.
- Hash: Can handle simple equality comparisons only.

## Adding Indexes

Deciding which indexes to add is central to your indexing strategy. You've got the extension `pg_stat_statements` which tells you all the queries executed and the time taken for them. You can start by looking at queries taking longer than 10ms.

You can start analyzing query plans by:

1. `explain (analyze, verbose, buffers)`
2. Use visual tools
3. First check for row count differences in between `estimated` and `effective` numbers. If there''s a big difference, check to see if tables are analyzed frequently by the autovacuum demon
4. Check for time spent doing a sequential scan of your data with a filter step, as that's the part that a proper index might be able to optimize.

The very best query optimisation technique consists of not having to execute the query at all.