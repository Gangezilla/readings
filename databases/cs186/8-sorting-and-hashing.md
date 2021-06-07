# Sorting and Hashing

- We use sorting for a number of reasons.
  - Rendezvous, to get things that need to be processed together in memory at the same time.
    - Remove duplicates (DISTINCT)
    - Summarization (GROUP BY)
    - Upcoming sort-merge join algorithm
  - Sometimes the user asks for order
    - Output will be ordered (ORDER BY)
    - It's the first step in bulk-loading tree indexes
- The problem, is how do we sort 100GB of data with 1 GB of RAM?
  - Virtual memory isn't a good choice because it doesn't understand sorting. Virtual memory will use randomly assigned memory bits which turns sorting into a big mess.

## Out-of-core algorithms

- RAM used to be called core, so algorithms that work on data sets that are bigger than your RAM are called out-of-core algorithms.
  - Single pass streaming data through RAM
  - Divide (into RAM-sized chunks) and conquer

### Single pass streaming

- Simple case: "map"
  - Goal: compute something for each record and write out the result.
  - Challenge: Minimise RAM used, call read/write rarely.
- Approach:
  - Read a chunk from INPUT to an input buffer
  - Write the function output to an output buffer
  - When input buffer is consumed, read another chunk
  - When output buffer fills, write it to output.
  - If you batch it like this, you can minimise the number of writes you do. Number of reads isn't synced to output and viceversa.

### Double Buffering

- Idea is that instead of one thread that does I/O and computation, you split this up into two threads. At some point when each finishes with their current tasks you swap the buffers that the two threads are pointing at.

## Sorting & Hashing

- Sorting: Given a file F, we produce an output file with it's contents stored in order by a given sorting criterion.
- Hashing: Produce an output file that has been hashed, so that it's contents are arranged on disk so that no 2 records that have the same hash value are separated by a record with a different hash value. So, matching records are always stored consecutively.

### Sorting

- 2 Way sorting
  - Pass 0: Conquer a batch. We go through all blocks and do this.
    - read a page, sort it, write it
    - only one buffer page is used
    - A repeated batch job.
  - Pass 1, 2, 3...
    - Merge together with three buffer pages.
    - Pick the smallest value of the input buffer until it's full, then write it to disk and continue the process. Merge the two buffers together