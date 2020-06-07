# Introduction to database systems

## Why take this class

- Very useful
  - Data processing backs every app incl databases
  - Principles back nearly all computing
  - Can get analytics information
  - Databases are important for the propagation of the human race (Tinder)
  - Science is increasingly being done through databases. First paradigm of science was experimental, second - theoretical, third - simulation, fourth - data intensive where you use sensing and large data storage to understand what's going on in the real world.
- In the 2000s there was a shift from programs to apps over data-centric storage
- More recently "full-stack" is becoming obsolete as more specialties pop up like Data science, data engineer.
- IT has also evolved, where data is increasingly handled in the cloud.

1. Utility
2. Centrality. Data is at the center of modern society. Data is very particular and voluminous. There's so much data. Data is central to a lot of discussion in sociey. 

**Privacy**

Starting mid 2000s we started seeing the word "database" appear on newspapers, never in a good way. They're very important to the functioning of society. 
It means if you get access to someone's Google account, you can see all their life basically.

**Data Integrity**

Not all data is correct, what implications does this have? For example, if enough users change an entry on Wikipedia and others agree with them, that becomes true.

DJ Patil (first Chief Data Scientist of US) called for a Code of Ethics for Data Science.

3. The core of computing

Data growth continues to grow and outpace computation.

Forces Driving Data Growth:

- Ubiquitous sensors and reporting. Cameras, mobile computing, blogging

Tehcniques you learn in this class unerlie many topics in computing

## What is this class about?

Universal symbol for a database is a cylinder, which is like the platters on a disk drive. First commercial disk drive was from 1956 and weighed a ton, had 5MB.

Rolodex is a type of database. Alphabetically ordered cards, and they even have indexes by character.

Business logic is a term used to describe what you need to do to make your data fit in your DB.

A database is a large, organised collection of data. A Database Management System (DBMS) is software that stores, manages and facilitates access to data.

### Relational DBMSs

This is stuff like Postgres, MySQL. They use SQL. ACID transaction consistency, which is a way of talking about how the data remains consistent so that application developers can reason about it. They typically implement durable writes (preventing data loss).

If you look at db-engines.com you can see the popularity of databases. Oracle is still huge, wow.

Relational DBs have a market of 41 billion dollars which is pretty nutty.

### Market Trends

Cloud DBMS is disrupting on-premises vendors. The cloud is less relational-centric, there's more NoSQL in the cloud than premises. RDBMSs are the fastest growing use of anything in the cloud.

One size doesn't fit all. Special purposes use cases.
- Main-memory DBMS where your data can fit in the RAM of a large node. (maybe redis?)
- Graph DBMS are used to handle graph data
- Timeseries DBMS for like stock tickers and sensors
- KV stores (NoSQL)
- Analytics platforms (Spark, hadoop)

Tools for working with data

Changes in the market happen for a few reasons:
- Hardware trends. RAM cheaper, SSDs cheaper vs HDD, NVRAM (non-volatile RAM), new trends in computation side like using GPUs to do other kinds of computing other than graphics. Hardware trends influence how we do data.
- Cloud and elastic computing. Ability to compute in the cloud is elastic, but you only wanna pay for as much as you use. Elasticity of resources changes how we think about building DBs.
- Need to scale. As data and volume of transactions occur this gives need for scale
- New data-types: full text, json, image and video data people wanna query for.
- New workloads: machine learning and advanced analytics

Lots of change in the DB space that means ideas we learn here are remixed and changed.

Opportunity to shape the future of DBMS. taking advantage of core ideas in the textbook (dunno which one that is).

Going to focus on **Foundational system principles**. Reusable ideas and components, compositional approach.

- Data oriented programming with SQL. 
- Foundations of Data syste design. storage, indexing, query processing and optimisation
- Transactions. how to have multiple users queries and updates at the same time.
- Data-modeling. Application-level representations of data

### Principles

- Data independence.
- Declarative Programming (what you want not how to get it)
- Rendezvous in time and space, how this relates to joins on single and multiple nodes.
- Isolation of diff actors running in a system and consistency
- Data representation principles.
- We'll examine various levels of a DBMS
- How we build systems that can run on lots and lots of data.
