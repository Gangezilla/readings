# The Relational Model

A DB is a collection of one or more relations, where each relation is a table with rows and columns. 

## Intro to the Relational Model

A relation consists of a shema and an instance, with the instance being a table and the schema being the column heads. The table is a set of tuples/records.

## Integrity Constaints over Relations

An integrity constraint is a condition specified on a schema that restricts the data that can be stored in an instance of the database. A key constraint is a statement that a certain minimal subset of the fields of a relation is a unique identifier for a tuple. A set of fields that uniquely identifies a tuple according to a key constraint is a candidate key, or just key.

### Key Constraints

A key constraint is a statement that a certain minimal subset of the fields of a relation is a unique identifier for a tuple. This means:

1. Two distinct tuples cannot have identical values in all the fields of a key (thye can have identical values elsewhere, but every field within the key constraint is unique.)
2. No subset of the set of fields in a key is a unique identifier for a tuple. This means that if your key is `id`, `{id, name}` is not a key. A DB designer can identify a primary key. With a primary key, we can refer to a tuple from elsewhere in the database by storing the value of its primary key. We'd specify this like so

```sql
UNIQUE (name, age),
CONSTRAINT StudentsKey PRIMARY KEY (sid) )
```

### Foreign Key

A foreign key means that if we modify something referring to another table, we need to ensure that the key exists. For example, we can't update the grade of a student who doesn't exist. We add this in like

```sql
FOREIGN KEY (studid) REFERENCES Students
```

This links `studid` to the primary key in the `Students` table.

## Introduction to Views

A view is a table whose rows are not explicitly stored in the database and are computed as needed. 