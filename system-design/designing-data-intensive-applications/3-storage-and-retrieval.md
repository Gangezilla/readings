# Storage and Retrieval

It's important to understand how a database handles storage and retrieval internally so that you can tune a storage engine to perform well under your workload. We're gonna examine traditional relational DBs and NoSQL DBs and two families of storage engines: *log-structured* storage engines and *page-oriented* storage engines like B-trees.

## Data Structures that Power your Database

Many DBs internally use a *log*, which is an append-only data file for setting a key. To efficiently find the value for a particular key we need a different data structure, *an index*. An index is an additional structure that is derived from the primary data. Many databases allow you to add and remove indexes, which doesn't affect the DB contents. Maintaining additional structures incurs overhead especially on writes. Any kind of index usually slows down writes. This is an important trade-off in storage systems; well-chosen indexes speed up reads, but slow down writes. This is why DBs dont index everything and wait for the application developer to specify an index based on your application knowledge.