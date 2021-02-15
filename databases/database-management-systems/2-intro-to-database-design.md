# Intro to Database Deign

The entity-relationship (ER) data model allows us to describe the data involved in a real-world enterprise in terms of objects and their relationships.

## Database Design and ER Diagrams

The database design process can be divided into six steps.

1. Requirements Analysis: Understand what data is to be stored in the database, what apps must be built on top of it, what operations are most frequent and perf requirements.
2. Conceptual DB Design: Create a simple description of the data that matches how users and devs think of the data.
3. Logical DB Design: Converting an ER schema into a relational schema

The ER diagram is just an approximate description of data. We then need to consider performance and design the schema, addressing security issues and ensuring that users are able to access the data they need, but not the data we wish to hide from them.

4. Schema Refinement: Analyze the collection of relations in our schema to identify potential problems.
5. Physical DB design: Consider expected workloads and refine so the design meets the perf critiera, which could be as simple as adding some indices.
6. App and Security Design

## Entities, attributes and entity sets

An entity is a real world object, exmaples are a toy, a toy department, the manager of the toy department, the address of the manager of the toy department. It's useful to identify a collection of similar entities, called an entity set. An entity is described using attributes. All entities in a set have the same attributes. With each entity, we must identify possible values, eg a name is a string.

## Relationships and relationship sets

A relationship is an association among two or more entities. Relationships can have descriptive attributes that are used to record info about the relationship

## Additional features of the ER model

### Key constraints

A key constraint could be that each department has a max one manager, no more no less. We'd demonstrate this in an ER diagram with an arrow.

### Aggregation

Aggregation allows us to indicate that a relationship set participates in another relationship set.

## Conceptual design with theER model

- Should a concept be modeled as an entity or an attribute
- Should a concept me an entity or a relationship?
- What are the relationship sets and their entity sets?
- Should we use aggregation?

## Unified Modeling Language

UML is a way of representing workflows in an application. Activity diagrams show the flow of actions in a business project. Statechart diagrams describe dynamic interactions between system objects