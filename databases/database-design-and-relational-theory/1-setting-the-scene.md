# Setting the Scene

## Preliminaries

Normal form is referring to reducing redundancy and data duplication in a database. The starting point for the concept of normal forms is **first normal form (1NF)**.

- To achieve first normal form, each field in a table must convey unique information.
- An entity is said to be in the first normal form when all attributes are single valued, meaning you can't have multiple values in a single field.
- A relation is in 1NF if all underlying domains contain atomic values only.
- There are no repeating groups of attributes.

Table = Relation
Row = Tuple
Column = Attribute
Relvar = Table

### Keys

Every relvar (table) has at least one candidate key. A candidate key is basically just a unique identifer, its a combination of attributes. Candidate keys are always combinations or sets of attributes, even if a set contains one attribute.
