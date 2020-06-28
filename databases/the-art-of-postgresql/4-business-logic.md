# Business Logic

Where to maintain business logic can be a hard question to answer as all apps and devs are different. The author's view is that every SQL query embeds some part of the business logic you're implementing, so the question should really be:

**How much of our business logic should be maintained in the database?**

## Every SQL query embeds some business logic

We need to realise that as soon as you send an SQL query to your RDBMS you're already sending business logic to the DB.

- A `select` clause that mentions the `name`, we know the business logic is only concerned with the track names.
- The `from` clause only mentions the `track` table, somehow we've decided that's all we need and that is strongly tied to the logic being implemented.
- The `where` clause restricts data output, which again is a direct translation of our business logic.
- The `order by` clause implements the idea that we want to display the names in the order they appear on disk.

## Business Logic Applies to Use Cases

Looking at a query and trying to decide if it's implementing business logic is impossible to know without a user story to understand it with. A simple query that does some computation could be split into several complex steps in application code. And sometimes an ORM will hydrate all the intermediate objects with as much info as possible, which translates into `select *` being used. We'll talk later about why this is bad. There's a number of problems with this related to correctness and efficiency.

### Correctness

When using multiple statements, it's necessary to setup the **isolation level** correctly. The SQL standard defines four isolation levels, with PSQL implementing three of them, leaving out dirty reads.

- Read uncommitted: PSQL acceps this setting and implements **read committed** here.
- Read committed: This is the default, and it allows your transaction to see other transaciton changes as soon as they're committed. So if you run a query like `SELECT count(*) FROM stock;` twice, and someone adds an object to stock in between, you'll have different counts at different points in your transaction.
- Repeatable read: Your transaction keeps the same **snapshot** of the whole DB for its entire duration from BEGIN to COMMIT. It's useful to have this for online backups.
- Serializable: This guaranttes a one-transaction-at-a-time ordering of what happens on the server exists with the exact same result as what you're obtaining with concurrent activity.

By using read committed, and doing your logic in SQL it means you get to avoid a bunch of errors. If you fetched everything and processed the data as someone deleted something then you might present the user with an error.

## Efficency

Efficency can be measured in a number of ways, including a static and dynamic analysis of the code written. Static analysis includes the time taken to develop the solution, the maintenance burden, how easy it is to review it etc. Dnyamic analysis is about what happens at runtime in terms of resources we need to run the code around the processor, memory, network and disk.

With a query like this:

```sql
select  album.title as album,
        sum(milliseconds) * interval '1 ms' as duration
from album
    join artist using(artistid)
    left join track using(albumid)
where artist.name = 'Red Hot Chili Peppers'
group by album
order by album;
```

it's pretty simple from a static analysis point of view. To run it frmo the application we need to send the query text on the network and we get the info we need. From the app side, we need to have the list of albums and their duration in memory and we don't do any computing so the CPU usage is limited to what needs to be done to talk to the DB server and organise the result set in memory, then display it to us.

In contrast, with the application code (not included here cos it's mad long), there's a bunch of steps taken.

1. We fetch thr artist from the DB, which is one network round trip and SQL query that returns the artist ID and name. In our use case we don't need the name, so that's a waste of bytes over the network and in memory.
2. We do another network round trip to fetch a list of albums based on the id we just retrieved and store this in memory. 
3. For each album we do another SQL query to the DB server and fetch the tracks and properties
4. In the same loop we sum up the duration.
5. Finally, output the data.

When picturing the network as a resource, we now have to consider both the latency and bandwidth characteristics and usage, which is why we mention round trips.

## Stored Procedures - a Data Access API

When using PSQL you can create server-side functions. You could do this like:

```sql
create or replace function get_all_albums
(
    in artistid bigint,
    out album text,
    out duration interval,
)
returns setof record
language sql
as $$
-- QUERY GOES HERE
$$
```

you then run it like `select * from get_all_albums(127);` If you only had the artist name you could get the id from a subquery:

```sql
select * from get_all_albums(
    (select artistid from artist where name = 'Iron Maiden')
)
```

with the `lateral` join method, you can also reuse this in a join clause.
