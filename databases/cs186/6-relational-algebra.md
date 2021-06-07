# Relational Algebra

- We start with a query, and the query parser and optimiser turns this into a form that the optimiser can work with. It uses relational algebra expression, which can be represented as a tree or logical query plan. It's a strategy for the query. The optimiser itself will actually produce an optimised query plan using iterators.
- SQL (declarative expression of the query result) => Relational Algebra (operational description of a computation). Somewhat operational, operations are on big objects.
- We like SQL cos it's declarative, so we say what we want not how to get it. This lets the system optimise the how.
- History of formal relational query languages
  - Relational calculus (basis of SQL)
  - Relational algebra is based on sets, provides an operational description.


## Unary Operators

- Algebra of operators on tables full of tuples (relation instances).
- 