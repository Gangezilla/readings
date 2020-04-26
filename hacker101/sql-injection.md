# SQL Injection,

## Directory traversal

Path injection attack when a users input is used for a path. In most OSes you have . and .. and by combinining these you can walk in the file system. DB files, personal info and stuff could be accessed this way.

When you send an HTTP multipart upload, what if you had a filepath in there. You could realistically upload malicious files in here too.

You can mitigate this by not allowing path separators or strip instances of . and ../ from path. Don't let users control paths whatsoever. Generate a hash of the filename and use that instead of user generated.

## Command Injection

Backticks let you embed a subcommand. If you discover that your input is being used for like a Unix command in the backend, you can test to see if your input is sanitised.

User input is used in lots of apps, especially enterprise apps.

## SQL Injection

Used to be everywhere but still is.

We care mostly about SELECT, WHERE and DELETE.

If an app builds a query directly from user input then that's bad.

Mitigate:

Ensure that all strings are properly quoted and run through the appropriate escaping function.
Use parameterized queries
Use an ORM for data access instead of direct queries

It sounds simpe, but many apps perform hundreds/thousands of queries and if theres even a single bug then you're in trouble.

' OR 1='1 -- returns all rows
' AND 0='1 -- returns no rows

You can use this to quickly hone in on SQL injection

SELECT foo, bar, baz FROM some_table WHERE foo='1' UNION SELECT 1, 2, 3; --';

### Blind SQL injection

Blind is when your data is inserted into a query but you cant directly see the results.

You could use something like this to pull an admin password bit by bit. We can't see the result but we can see the side effect of how long it takes.

### Detecting database

Being able to detect the database is really important.

- /_! comment here _/ -- this looks like a normal comment to most DBs but MySQL will include the contents of the comment inline if it has an exclamation point
- WAITFOR DELAY will work on MSSQL and fail elsewhere
- UTL_INADDR.get_host_address('google.com') will do a DNS request on Oracle.

## Cheat sheet

' OR 1='1 -- returns all rows
' AND 0='1 -- returns no rows

In input fields, you can also just put an ' at the end and you'll sometimes get results. Like: `admin '`

https://www.netsparker.com/blog/web-security/sql-injection-cheat-sheet/
