# SQL: Queries, Constraints & Triggers

SQL was developed around 1974 - 1977 at IBM.

## Overview

- Data Manipulation Language (DML). Subset of SQL that allows users to pose queries, insert, delete + modify rows.
- Data Definition Language (DDL). Subset of SQL that supports creation, deletion and modification of definitions for tables and views. 
- Triggers and Advanced Integrity Constraints. SQL:1999 standard has triggers, which are actions exceuted by the DBMS whenever changes that meet a condition occur.
- Transation Management

## The form of a basic SQL query

- Every query must have a `SELECT` clause and a `FROM` clause.
- If we have the `DISTINCT` keyword, we get a set of rows. If two or more rows are identical, we only get one.
- If we don't have `DISTINCT`, we would get duplicate rows.
- `SELECT *` is useful for interactive querying, but bad for queries that are designed to be reused because it's unclear what gets returned.
- from-list in `FROM` is a lsit of table names
- select-list is a list of column names 
- `WHERE` is a boolean combination of conditions.
- `DISTINCT` keyword removes duplicates.

This chapter was covered in the SQL lectures, so check out those notes.

