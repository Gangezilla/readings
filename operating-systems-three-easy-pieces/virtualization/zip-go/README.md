# Zip and Unzip

Here we're going to build a zip and unzip tool.

If we had a string like `aaaaaaaaaabbbb` we'd want it to turn into `10a4b` and put this into a binary file. 

However, the exact format of the compressed file is quite important; here, you will write out a 4-byte integer in binary format followed by the single character in ASCII. Thus, a compressed file will consist of some number of 5-byte entries, each of which is comprised of a 4-byte integer (the run length) and the single character.

So I guess the above would look like
`00001010a00000100b`