# Intro

## Explain keyword

EXPLAIN gives you the execution plan of a statement with related information. Postgres creates an execution plan for every query it executes. Postgres engine selects the query plan the planner has created.

The more queries you tune, the better you'll get at identifying bottlenecks and tuning them.

## Use Case Scenarios

If we do a `SELECT *` the `EXPLAIN` output says its doing a `Seq Scan` because it has to brr through all the rows.

- Cost is 0.00 which is estimated output cost before the query can begin.
- Rows is an estimated number of rows.
- Width is an estimated average width of the row output in bytes. This can be really important during advanced perf tuning, but its ok for now.
- Cost is measured in an arbitrary scale, not an absolute value. If you see this value going higher than another query, it means it takes more resources. It's neither good nor bad, useful for comparison. Total cost is a relative value and only matters when we compare it.
- The cost is made up of a bunch of shit, I don't know if it's super important tbh.
- When we add a `WHERE` it takes longer. This is because we have an additional filter. A Sequential Scan is still happening. So the planner grabs all the rows and then does an additional filter.
- When we do a `SELECT` when an index is hit the cost is significantly less.
- When there is a scan on table and then a filter, the entire table is first scanned

## EXPLAIN ANALYZE Syntax

- EXPLAIN is an estimation
- EXPLAIN ANALYZE gives an output and is more powerful than EXPLAIN alone.
- VERBOSE, COSTS, and TIMING are on by default. BUFFERS is not.

## Demo

- Using ANALYZE gives us an estimation of the planning time, and also execution time too. This is actual time in ms.
- It also tells us a count of the amount of loops that happen as well, which is pretty interesting.
- It also tells us how many rows were removed from the filter.
- Indexes are silver bullets to a lot of performance problems, apparently.
- If we see that rows being removed is a high number, it means this is a very poorly optimised query.
- The planner will grab things by index first, and then do a filter on that as well.

## Improving Query performance with indexes

Index is a structure that organises data and references to it in a manner that makes it easy to look up data associated with it.

### Types of indexes

- B-tree (b stands for balanced)
- Hash Index, are useful only for comparison. This bloke hasn't ever used one in 14 years lol. They aren't safe with transactions in PG and need to be rebuilt everytime there's a DB crash.
- Generalized Inverted (GIN) Index. Useful for full text search
- Generalized Search Tree (GiST) index. Useful when working with geometric data type and text.

But like, most of the time you're gonna be using a B-Tree index

B-Tree queries are useful when you have equality queries, like `< <= = >=- >`. They're also useful for range queries like BETWEEN and IN. If you see either of these, think of B-tree as being a saviour in these scenarios.

B-Trees improve performance of SELECT queries.

Disadvantages of b-tree queries: They reduce performance for INSERT, UPDATE and DELETE queries. This is why we shouldnt create too many indexes. Important we understand the business logic of a table and understand what operations happen on that table.

`CREATE INDEX [nameOfIndex] ON [tableName] (Column1, Column2);`

`DROP INDEX [nameOfIndex];`

Use multicolumn indexes sparingly, single column indexes are usually sufficient.