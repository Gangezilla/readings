# Disks, Files and Buffers

## Architecture of a DBMS: SQL Client

- SQL is typed into some client. And theres a DBMS which is a server.
- When a query is executed there are a number of modules that are executed. The first is 'Query Parsing & Optimization', and its job is to verify that SQL is legal, then translate it into a relational query plan to be executed.
- Relational Operators, purpose is to execute a dataflow by operating on records and files.
- Beneath that, 'Files and Index Management', purpose is to organize tables and Records as groups of pages in a logical file.
- Beneath that 'Buffer Management', provides the illusion of operating in memory instead of disk. It's job is to map disk blocks from disk to memory
- Disk Space Management, translate page requests from the buffer manager into physical bytes on one or more disks.

- It's organised in layers, abstracting the layer below. Helps to manage complexity, gives performance assumptions. Example of good systems design.
- Concurrency Control, how we let multiple users use the DB simultaneously without stepping on each others toes.


## Disk Space Management

- Storage media is going to have a big impact on what we make.
- Most DB systems were originally designed for magnetic disks.
- We 'read' and 'write' pages of data from disk to RAM. A page is a 32kb object, which is relatively small. We can't address particular bits or bytes. To change something we have to bring its page into RAM. 
- Reading and writing is super slow though. Sometimes, having a really explicit API can be a good thing. Using pages is a way of discipline to prevent a certain class of error.
- Magnetic disks are way cheaper than SSD/RAM, and you get many orders of magnitude more storage density.
- Storage is in a hierarchy. Things at the top are small and fast, things at the bottom are big and slow. Registers => L1 Cache => L2 Cache => RAM => SSD => Disk. DB, logs, backup are stored in magnetic disks, or on tertiary storage like a tape drive.
- For data thats hot, we want it in RAM. 
- Jim Gray talks about it in terms of distance. Registers are in your head, but getting it off disk is like going all the way to Pluto to retrieve it. This gives you a sense of how bad it is to go to disk or RAM.
- Memory to disk boundary.

## Components of a Disk

- Important to understand how it works to understand its performance characteristics.
- Mechanical object made of a bunch of platters and heads, sitting on a spindle that spinds them all around 15000 RPM. Arm assembly moves in and out to position read/write heads. 
- Looks like a cylinder.
- Only one head reads/writes at a time
- They write a multiple of sector sizes, a sector is a pi shaped piece of circle. Sector is part of track that intersects with one of the arms. Sector is a fixed amount of data, block or page size is a multiple of sector size thats configured by the OS.
- Accessing a disk page takes time
  - Seek time (move arms to position disk head on track) 2-3ms
  - Rotational delay (waiting for block to rotate under head) 0-4ms for 15K RPM
  - Transfer time (moving data to/from disk surface) 0.25ms per 64kb page
  - Key to lowering cost: reduce seek/rotational delays.

## Flash Memory (SSD)

- 2018, NAND. Allows very fine grained reads, 4-8k at a time. Writes are bigger, 1-2MB per writes.
- For a given memory cell on a flash disk, after 2-3K erasures the cell will usually fail. We don't want to write to one spot or we have hotspots. When you're writing to a disk, you want to move hot write units around (wear levellling) to even out the wear and tear. This is controlled by SSD firmware
- Write amplification, big units, means it needs to reorganise for wear and tear, possibly doing a read and write to reorganise.
- Read on a flash disk is fast and predictable, single read access time is about 0.03ms.
- Reading something thats next to something else (sequential read) doesnt speed things up much, but it does on a magnetic disk.
- Writing is slower.
- Using models for magnetic disks are still appropriate, cos random vs sequential is still relevant.
- Locality matters for both flash and magnetic atm.
- Disk offers about 10x the capacity per $.

## Storage Pragmatics and Trends

- Many significant DBs aren't that big. 
- Big data is real, Boeing 787s generate 1/2 TB of data per flight.
- You can get DBs that live in RAM, or bigger ones that deal with really big amounts of data.
- Very large DBs: relatively traditional. Still best cost per MB. SSDs improve performance and reduce variance. For example, a slow vs fast read on HDD vs SSD is much less.

## Disk Space Management

- Most DBMSs store info on Disks and SSDs.

### Block Level Storage

- Read and Write large chunks of sequential bytes, sequential meaning the "next" disk block is fastest.
- You want to maximise usage of data per read/write, "if youre going all the way to Pluto, pack the spaceship full". Try and get full blocks from reads/writes.
- We do this by:
  - predicting future behaviour and caching things.
  - Prefetching likely to be accessed blocks, getting it from disk to memory.
  - Buffer writes to sequential blocks. It means we can buffer writes until we can get runs of sequential writes.

Block is a unit of transfer between disk and RAM, usually 64kb - 128kb. Page and block are synonyms for each other, sometimes you see a page meaning its currently in RAM.

### Arranging Blocks on Disks

- "Next" block concepts
  - Sequential blocks on same track
  - Blocks on same cylinder
  - Blocks on adjacent cylinder.
- We arrange file pages in order of 'next' on disk, to minimize seek and rotational delays.
- For a sequential scan, we pre-fetch several blocks at a time. Read large consecutive blocks.

### Disk Space Management

- Lowest layer of DBMS
- Maps pages to locations on disk physically (keeps track that page 4 is in a particular physical location)
- Load pages from disk to memory (please transfer page 4 to memory)
- Save pages back to disk 
- Higher levels call on this layer to read/write a page, allocate/deallocate logical pages.
- It gets requests for pages/sequences of pages. It's job is to do this fast. Higher layers will do an assumption of pages, will know that sequential page reads are faster. It has to do this by laying out pages intelligently.

#### Implementation

- Proposal 1: DBMS is directly talking to storage device, skips the OS.
  - Goes directly to hardware and its really fast. If you know your device and its drivers its really quick.
  - The problem is that disk drives aren't forever, and now you have software that needs to be ported to the new disk. Because of this we don't do this.
- Proposal 2: Let the OS worry about the device, and run this over the filesystem.
  - DBMS allocates one large contiguous file to an empty disk and assume the pages are sequential.
  - Most file systems are pretty good at this if they're presented with an empty disk.
  - DBMS have a notion of a "file" that spans multiple disks/machines.
  - For example, when page 4 is requested, this is passed down to a "big file", which contains certain pages, the page is then requested from the physical disk.
  
- Disk Space Management Layer provides an API to read and write pages to device.
- Pages: block level organization of bytes on disk
- Provides "next" locality and abstracts FS/device details.

## Files

- Logically we have a relational table with rows and columns, which gets mapped to a file with pages/blocks. The table is made up of logical records, which are represented in memory as arrays of bytes which are packed onto pages in memory.
- Pages are managed by the disk space manager to read/write. They're added to the buffer manager in memory.

### Database Files

- File: a collection of pages containing a collection of records.
- API for higher levels of DBMS is they can
  - insert/delete/modify
  - Fetch a record by record ID, like a pointer which encodes a pair (pageID, location on page)
  - Scan all records (possibly with some conditions on the record to be received)
- Could span multiple OS files and even machines.
- Many types of file structures
  - Unordered heap files
    - Collection of records in no particular order. Not a heap data structure.
    - As file shrinks/grows, pages are allocated and deallocated
    - To support these operations we need to keep track of pages, free space and records on a page.
  - Clustered heap files, record and pages grouped
  - Sorted files pages and records sorted
  - Index files, 

### Page Layout

- Header may contain
  - number of records
  - free space
  - next/last pointer
  - bitmaps/slot table.
- If records are all the same length they're fixed, otherwise they're variable. This matters for designing the page layout.
- Find records by record ID (page, location in page)
- How do we add and delete records?
- Pages are linear arrays of bytes on disk
- Fixed length records, packed
  - Pack records densely
  - with fixed length records we can just store each as an offset so we can just move along this. Empty space can be calculated by knowing the number of records and the page size.
  - Deletion means we need to repack the page too. This means that record IDs pointing into this page need to be changed.
- Fixed length records, unpacked
  - We keep a bitmap for each slot on the page.
  - Inserting we just find an empty slot, for deletion we just clear the bit. This means the pointer to the next record doesn't need to change.
  - The only overhead is the bitmap which isn't a lot of work. 
  - Very small space overhead, but you get stability on the page IDs.
- Variable length records
  - How do we know where each record begins?
  - What happens when we add/delete records? (variable sized holes)
  - We relocate metadata to the footer.
    - We then fill this up with a slot directory. The first entry is a pointer to free space. For each other record we know the size and offset. This pair of length and pointer.
    - Slots are stored in reverse order from right to left.
    - We delete by removing the data in the slot directory. If we want to insert we put the record in free space at the end of the page.
    - The problem this creates is free space fragmentation. We resolve this by reorganizing the data, changing the pointers.
      - Is it safe to reorg? Yeh, it's safe because people using the API use page ID and slot ID
      - When should i reorganize?
        - Eager, reorg whenever we delete a record
        - Delete, only do it when we run out of space. It often pays to be a bit more lazy.
        - What if we run out of slots in the footer, but there's new space. We track the number of slots in slot entry. We need to count the number of slots whether they're full or empty.
        - If we want to extend the slot directory, we can add a new slot from right to left. Update the count and things are ok. The slot directory grows inwards from the end to the middle and when the slot directory and records meet each other the page is full.
    - Slotted page is a good general purpose data structure for storing records.
  
### Record Layout

- How to pack fields in a record
- In relational model, each record has a type. We assume we have a schema which lives in the system catalog, so every record doesn't need to describe itself, we can refer to the schema. The system catalog is just more tables lol.
- Records should be compact in memory and disk, and we can do fast access to fields.
- Easy case with fixed length fields, tricker with variable length.

Record formats: fixed length
- Types are stored in system catalog, disk representation is the same as in memory. No need to serialize between formats, they are the same.
- Interpreting bytes stored on these pages. We can find x field by doing arithmetic.
- One of the challenges here is nulls, we need to waste empty space on nulls.

Record formats: Variable length
- What happens if fields are variable length? Can't use padding on small fields cos big names may be bigger.
- Could do char delimitation, but we might want to use that char in data. It also requires counting delimiters till you get to the right place.
- The idea is that we move all variable length fields to end of record. All fixed length fields go at the start, and all variable length ones go to the end.

## Summary

Logical structure, table. Maps downwards to a file full of pages, abstract page which is a record, goes to byte representation in file. Putting records on pages using slotted page architecture.