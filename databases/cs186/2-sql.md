# SQL II

So far we've looked at single table queries. When we're understanding these they usually follow a pattern like this:

FROM => WHERE => SELECT => GROUP BY => HAVING => DISTINCT

ORDER BY and LIMIT are applied at the end to 'format' the output.

## Queries with multiple tables

We form a cross product with multiple tables.

## Column Names and Table Aliases

`FROM Sailors AS S` and we can then use `S` to indicate which column we want. The `AS` is called giving it an alias.

## Arithmetic Expressions

You can specify arithmetic expressions like `2*S.age`. You could use SQL as a calculator if you wanted.

```SQL
SELECT log(1000) at three
```

SQL also accepts string functions.

- Old-school SQL `WHERE S.name LIKE 'B_%'`. Where underscore is a wildcard and percent is repeat
- Standard regex `WHERE s.name ~ 'B.*'` with the `~` indicating the instruction following is a regex.

## Combining Predicates

### Boolean logic

`WHERE R.bid=B.bid AND (b.color='red' OR b.color='green')`
OR

```SQL
SELECT R.sid
FROM Boats B, Reserves R
WHERE R.bid = B.bid AND b.color='red'

UNION ALL

Select R.sid
FROM Boats B, Reserves R
WHERE R.bid=B.BID AND B.color='green'
```

We take the union of the red boats and the green boats and output it. `UNION ALL` says we don't want to remove any duplicates.

`AND` is similar to `INTERSECT`

## Set Semantics

Set: a collection of distinct elements
Standard way of manipulating/combining sets: union, intersection, exception
Treat tuples within a relation as elements of a set.

It's easier to look at them like this:

R={A, A, A, A, B, B, C, D}
S={A, A, B, B, B, C, E}

Union: {A, B, C, D, E}
Intersect: {A, B, C}
Except: {D}

## ALL: Multiset Semantics

The keyword ALL indicates we're working with multiset semantics.

We can use nested queries with subqueries and `IN`.

```SQL
SELECT S.name
FROM Sailors S
WHERE s.sid IN
    (SELECT R.sid
    FROM Reserves R
    WHERE R.bid=102)
```

We could also use `NOT IN` instead of `IN`, and `EXISTS` for subqueries too.

There's other forms like `ANY` and `ALL`

```SQL
SELECT *
FROM Sailors S
WHERE S.rating > ANY
    (SELECT S2.rating
    FROM Sailors S2
    WHERE S2.sname='Popeye')
```
rating of all sailors whose name is Popeye, will output if the rating is greater than any rating of a sailor named Popeye.

## ARGMAX?

Queries that try to find the largest thing in a set of things. You could do `SELECT MAX(S.rating)` but you dont have context.

In a query with aggregates, every column in select needs to be listed in aggregates or listed in the group by clause. To get the ARGMAX you'd do something like this

```SQL
SELECT *
FROM Sailors S
WHERE S.Rating =
    (SELECT MAX(S2.rating)
    FROM Sailors S2)
```

or you could do like

```SQL
SELECT *
FROM Sailors S
ORDER BY rating DESC
LIMIT 1;
```

This bottom one gives you one person, but there may be a bunch of tied max results. And in fact everytime you run it, you might get someone different. Sometimes thats what you want. But sometimes you want all of the sailors who are tied.