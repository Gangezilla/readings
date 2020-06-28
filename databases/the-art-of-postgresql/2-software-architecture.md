# Software Architecture

PSQL is a RDBMS (Relational Database Management System) and it's role in your architecture is to handle concurrent access to live data that is manipulated by several apps, or several parts of an app.

## ACID

At the heart of the concurrent access semantics is the concept of a transaction. A transaction should be **atomic** (meaning that a transaction cannot happen partially) and **isolated** (isolation defining how visible a transaction is to other parts that access the DB), with isolation allowing for online backups of the data.

**Durable** means that whatever happens, PSQL guarantees that it won't lose any committed change. Your data is safe.

## Data Access API and Service

PSQL allows one to implement a data access API. In a container and microservice world, PSQL is the data access service and its API is SQL. PSQL is stateful, which means that your other services can be stateless which makes solving their problems way easier.

## Structured Query Language

PSQL's data access API is based on SQL which is a declarative language where your job is to describe in detail the result set you're interested in. PSQL's job is then to find the most efficient way to access only the data needed to compute this result set and execute the plan it comes up with.

## Extensible (JSON, XML, Arrays, Ranges)

SQL is statically typed, so every query defines a new relation that must be understood by the system before executing it, which is why we have to `cast` sometimes. Due to how PSQL is implemented, it offers deep coverage for composite data types and documents processing within the language.

When you're designing your architecture, think about PSQL not as a **storage** layer, but as a **concurrent data access service** that is capable of handling data processing.

## Why PSQL?

- OSS
- Done completely in the open, using public mailing lists for everything.
- Most devs on PSQL contribute in a professional capacity.
- The extensibility of it allows it to be continually extended. For example, PSQL is one of the best JSON processing platforms with the `@>` operator reads, contains and implements JSON searches.