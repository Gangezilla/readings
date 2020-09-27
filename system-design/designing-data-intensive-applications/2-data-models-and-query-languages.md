# Data Models and Query Languages

Data models are really important because they impact how the software is written but how we think about the problem we're solving.

## Relational model vs Document model

The relational model is what you're familiar with, so SQL mostly. It was a breath of fresh air cos in the 60s and 70s databases required developers to care about the internal representation of the data. Relational databases are an abstraction on this, that gives a developer an easier interface to work with. Over the last 30+ years, a number of alternatives popped up but relational DBs proved to be versatile and able to be used for a number of situations.

### Birth of NoSQL

Focused on open source, distributed, nonrelational databases. People adopt them because

- a need for greater scalability than relational DBs
- FOSS
- Specialized query operations that aren't well supported by the relational model

Relational and non-relational DBs will probably be used alongside each other for a while, which is apparently called *polyglot persistence*.

### Object-Relational Mismatch

In OOP languages, relational DBs present a problem because a series of tuples of data don't neatly fit into an object. This is what ORMs are used for, to map these tuples into an object. This is also partly why people like non-relational DBs cos they can store all their data in JSON. JSON also has better *locality*, in that if you want to get someone's LinkedIn profile as JSON you just have to do one call instead of a big JOIN query or multiple calls.

### Many-to-One and Many-to-Many relationships

Removing duplication in databases is called *normalization*. Normalization requires *many-to-one* relationships. Some data structures that initially seem to fit into a join-free document model don't work as well when more complex features need to get added.

