# Structured Query Language

SQL lets us declare the result we want to obtain in terms of a data processing pipeline that's executed against a known DB model and dataset. RDBMS and SQL force devs to think in terms of data structure.

- The current SQL standard is SQL'2016.
- When you use SQL properly it allows you to reduce both code size and development time for new features.
- You can use `\set` to set a variable for reuse. For example, `\set start '2017-02-01'` lets us use that as `:'start'`. This is called a decorated literal in PSQL, allowing us to set the data type of the literal value so the PSQL parser doesn't have to guess or infer from context.
- `to_char()` allows converting a number to its text representation allowing you to control the conversion.

## A word about SQL injection

PSQL implements a protocol level faciliy to send the static SQL query text separately from its dynamic arguments. An SQL injection when the database server is mistakenly led to consider a dynamic argument of a query as part of the query text. Sending those parts as separate entities over the protocol means the SQL injection is no longer possible.

It's advisable that you read the documentation of your current driver and understand how to send SQL query parameters separate from the main SQL query text, this is a reliable way to never have to worry about SQL injection problems ever again. Never build a query string by concatenating your query arguments directly into your query strings

## Back to discovering SQL

There's ways you can solve problems without writing any application code.

- SQL accepts comments written with either `--` or `/* comment */`
- `generate_series()` is a PSQL set returning function (which is a function that could return more than one row) that "generates a series of values from start to stop with a step size of step".
- `cast(calendar.entry as date)` transforms the generated calendar.entry which is the result of the `generate_series()` function call into the `date` data type.
- `COALESCE` returns the first of its arguments that is not null.

In this particular example, we replaced 60 lines of Python ode with a pretty simple SQL query.