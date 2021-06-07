# Iterators, Relational Operators and Joins

Query is given to a query optimiser that uses relational algebra to make a logical query plan that produces an optimised physical query plan. Every relational operative 

- Query plan
  - Edges encode flow of tuples
- Query executor instantiates operators. Each instance operator implements an iterator interface and efficiently executes operator logic forwarding tuples to next operator.