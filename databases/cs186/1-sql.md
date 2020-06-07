# SQL

SQL goes back to a research project at IBM called System R. Worked to prove that the (at the time) theoretical relational model was useful and valuable.

IBM was beaten to market by a startup called Oracle. Oracle had been reading IBMs technical reports and brought it to market. 

SQL is over 40 years old. It's been question repeatedly. 90s, object oriented DBMS. 2000's, XML with 3 different query languages to get data from it. 2010s, NoSQL & MapReduce.

However SQL keeps re-emerging as the standard.

## Pros and Cons

- Declarative language. You say what you want, now how to get it. You leave the decision of how to compute it to the DBMS. It means that the DBMS might implement this differently according to version changes.
- SQL has been implemented widely in various levels of effiency and completeness.
- SQL is a constrained language

## Relational Terminology

- Database: Set of named relations. We typically draw them as cans. Inside our DB we have our tables.
- A relation (called a table) has two parts: Schema (description, metadata) and an Instance (set of data satisfying the schema).
- Attribute (Column, Field)
- Tuple (Record, Row)

There's lots of synonyms...

In a relational table the schema is fixed. Adding and deleting columns is possible but not done too regularly. They'll have unique attribute names.

The instance (data in the table) changes often via inserts and deletes.

Let's look at illegal representations. Schemas must be enforced. Your SQL DB will enforce the schema. If it doesn't you'd say no because the instance doesn't represent the schema. A DB must have "atomic" data types, so you can't use something like tuples.

## SQL Language

SQL contains two sublanguages:
- DDL - Data Definition Language to modify schemas
- DML - Data Manipulation Language, manipulating the instance, actual language in the

RDBMS is responsible for efficiently evaluating the SQL language. The RDBMS chooses and runs algorithms for declarative queries.

We specify a primary key. The primary key provides a unique "lookup key" for the relation. Cannot have any duplicate values. It can be made up of multiple columns if you wanted to. You could do firstname, lastname too. Duplicate constraint would be on the pair of columns in this case.

Foreign keys - foreign keys are like pointers in schemas. so for example,

```SQL
FOREIGN KEY (SID)
    REFERENCES Sailors));
```

sid is a pointer to the Sailors table. If there's a value in the sid column of this table there's a reference to the other table. We don't specify which column in the table this points to, but by definition it points to the primary key of the table it references. The primary key is the referent.

## Basic Single-Table Queries

- Simplest version is straightforward.

```SQL
SELECT [DISTINCT] <column expression list>
FROM <single table>
WHERE <predicate>
```

- Keyword `DISTINCT` specifies removal of duplicate rows before output. 

```SQL
SELECT DISTINCT S.name, S.gpa
FROM students S
```

- You can also ORDER BY when you're getting your output. ORDER BY clause specifies output to be sorted. `ORDER BY s.gpa, s.name, a2`. Lexicographic ordering so it goes by the first one and then uses the next for tiebreaking and so on.
- You can also specify `ASC` or `DESC`. Default is `ASC`. You can mix and match these, so `ORDER BY S.gpa DESC, S.name ASC, a2;`
- `LIMIT 3` argument to limit is the number of rows you wanna see. If you have a LIMIT without ORDER by it's non-deterministic what order you get. So this means you generally wanna use `LIMIT` with `ORDER BY`

## Aggregates

A powerful thing to do is compute an aggregate function in that table. Aggregate functions take a batch of values in a column and compute that. 

```SQL
SELECT AVG(s.gpa)
FROM Students S
WHERE S.dept = 'CS'
```

Before it produces the output it gets all the rows, then computes a summary (aggregate) of some arithmetic expression. This query produces 1 row and 1 column of output. You've also got `SUM`, `COUNT`, `MAX` and `MIN` as well as others.

We often wanna break a table into groups using `GROUP BY`. 
```SQL
SELECT AVG (s.gpa), S.dept
FROM Students S
GROUP BY S.dept
```

For each group we compute that average, that aggregate. Sometimes called the cardinality of that output. If something's in the GROUP BY list, it can also be in the select group to tag them.

After we do a `GROUP BY` there may be groups we don't want in the output and we can use `HAVING ` for this. `HAVING` is applied after grouping and aggregation. `HAVING` can only be used in aggregate queries. 

```SQL
SELECT AVG (S.gpa), S.dept
FROM Students S
GROUP BY S.dept
HAVING COUNT(*) > 2
```

## Putting it all together

```SQL
SELECT S.dept, AVG(S.gpa), COUNT(*)
FROM Student S
WHERE S.gender = 'F'
GROUP BY S.dept
HAVING COUNT(*) >= 2
ORDER BY S.dept;
```

Reading it inside out a bit so:
- We want to view records `FROM` the students table
- `WHERE` the gender is F
- we want to `GROUP BY` department
- I only want to look at the groups that `HAVING` 2 or more tuples.
- For groups with 2 or more tuples, I want the `AVG` GPA, the COUNT and I wanna order by department

`DISTINCT` is used in two places:

- `SELECT DISTINCT COUNT(S.name)` Here we'd count 10 bobs and 4 marys and before sending the output to the user we'd remove any duplicates and still return 14. In aggregates you don't tend to have duplicates.
- `SELECT COUNT(DISTINCT S.name)` first we want to remove all duplicates of names. If we had 10 Bobs and 4 Marys we'd only have two results.

### Summary

- Relational model has well-defined query semantics.
- Modern SQL extends "pure" relational model (dupe rows, aggregates, ordering of output)
- Typically many ways to write a query.