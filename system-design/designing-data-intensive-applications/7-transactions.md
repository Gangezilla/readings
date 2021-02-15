# Transactions

There's a lot that can go wrong with distributed systems, and transactions have been the mechanism of choice for simplifying these issues. A transaction is a way to group several reads and writes together in one logical unit. This means an app doesn't need to worry about partial failure because the database provides a **safety guarantee** for us. However, transactions have advantages and limitations that we should understand.

## The meaning of ACID

### Atomicity

Atomic refers to something that can be broken down into smaller parts. ACID atomicity describes what happens if a client wants to make several writes, but a fault occurs after some of the writes have been processed. If the writes are grouped into an atomic transaction and the transaction cannot be completed (committed) then the transaction is aborted and the database is rolled back.

### Consistency

Consistency means a lot of things in a lot of contexts. In the context of ACID it refers to an application-specific notion of the DB being in a "good state". This means you have certain statements about your data (invariants) that must always be true. For example, in an accounting system credits and debits must always be balanced. This means that consistency means different things for different systems, and it's up to you to determine what this means. Consistency is a property of the application, as the database will write whatever you give to it, even if its incorrect. Because of this, C doesn't reaaaaally belong in ACID.

### Isolation

Isolation means that concurrently executing transactions are isolated from each other, so that two updates that are executed at the same time dont step on each others toes. This usually means that when two transactions have committed, the result is the same as if they had run serially even though they may have run concurrently.

### Durability

Durability is the promise that once a transaction has committed successfully, any data it has written will not be forgotten even if there's a hardware fault or a crash or anything.

## Single-Object and Multi-Object Operations

You want a DB to be ACID compliant for single and multi-object writes.

## Weak Isolation Levels

DBs try to hide concurrency issues by providing transaction isolation, this means that you get to pretend it doesnt exist. The DB provides serializable isolation which means that the DB guarantees that transactions have the same effect as if they ran serially. Rather than blindly rely on tools, we should develop an understanding of the concurrency problems that exist.

### Read Committed

The most basic level of transaction isolation is *read committed*, which guarantees:

1. When reading from the DB, you'll only see data that has been committed (no dirty reads). If a transaction is in process, and another transaction can *see* that data, this is a dirty read.
2. When writing to the DB, you'll only overwrite data that has been committed (no dirty writes)

### Snapshot Isolation and Repeatable Read