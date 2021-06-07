# Query Optimisation

- Bridge between declarative domain-specific language and custom imperative computer programs. Automatic generation of programs by computers based off high level specifications.
- Invented in 1979 in the context of System R which was a pioneering data storage software.

## Big Picture

Query parser can be broken down into a few pieces.

- Input: SQL gets parsed into a query parser which outputs an AST.
- This is passed to a query rewriter which puts it into canonical form.
- This is passed into the query optimiser which has to turn this into an efficient plan.
- The query optimiser talks to the catalog manager to understand the schema.
- Once the query optimiser has chosen an optimal plan, the query executor executes this plan using iterators.

- Query parser: checks correctness, verifies that the user is authorized to view the tables. Fairly straight forward parsing tree. It takes SQL text and generates an AST.
- Query rewriter is a bit of a weak spot in some open source DBMSs, including Postgres.
- Query optimiser not perfect, sometimes makes mistakes.

### Query Optimisation Overview

- Query block converted to relational algebra
- Relational algebra converts to tree
- Each operator has implementation choices
- Three components:
  - Plan space (for a given query, what plans are considered)
  - Cost estimation (how is the cost of a plan estimated)
  - Search Strategy (how do we search in the plan space)
- The goal in query optimisation is to find the plan with the least actual cost. The reality is we find the plan with least estimated cost, and try to avoid really bad actual plans.