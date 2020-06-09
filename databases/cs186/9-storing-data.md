# Storing Data: Disks and Files

## The Memory Hierarchy

Memory in a computer system is arranged in a hierarchy.
- Primary storage: Cache and main memory. Very fast.
- Secondary storage: like an HDD, slower.
- Tertiary storage: optical disks and tape drives. Slowest.

We store data on tapes and disks and build DB systems that can retrieve data from lower levels of the memory hierarchy into main memory as needed.

Storage is called nonvolatile if it persists after the computer is restarted.

Tapes are relatively inexpensive and can store loads of data, but they're really slow. Tapes are sequential access devices, meaning we step through all the data in order and cannot directly access a given location. This makes tapes unsuitable for operational data (frequently accessed). They're usually used for backups.

### Magnetic Disks

- Support direct access to a desired location.
- A DBMS provides seamless access to data on disk, so apps dont need to worry if data is on main memory or disk.
- Data is stored on disk in units called disk blocks. A disk block is a contiguous sequence of bytes and is the unit in which data is read/written to disk.
- Blocks are arranged in rings called *tracks* on one or more platters. Each track is divided into ars called sectors.
- An array of disk heads is moved as a unit and positioned over a block.

## Disk Space Management