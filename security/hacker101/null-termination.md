# Null Termination

The null character is used to terminate C strings. That is, you have a series of characters ending with a null in memory. Most web apps use languages written in C, and this can sometimes shine through.

In PHP if we put a null byte after a file include, it may ignore the requirement of a PHP filetype letting us read any arbitrary file.

Its worth throwing null bytes into anything related to file handling, particularly when dealing with PHP. Most browsers will strip %00 from requests, but Burp lets you embed literal nulls as well as URL encoded %00 nulls.
