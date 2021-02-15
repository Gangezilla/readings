# Crypto Crash Course

## XOR

Bitwise operator that compares two bits and outputs a new one. XOR is critical to crypto as it's self reversing, meaning

D = A ^ B
A == D ^ B
B == D ^ A

This means we can produce a simple, perfect crypto scheme. Generate a key of N bits of true random data, XOR each of the bits of the key with N bits of plaintext and you get a perfectly encrypted ciphertext blob of N bits. Decryption is just XORing against the same keystream.

This is called a "one time pad". If you use a key once without repeating it, it's uncrackable.

Since we don't want to pass around massive keys to everyone we communicate with, how can we safely and quickly share keys with all relevant parties.

## Types of Ciphers

Ciphers are either symmetric (both sides share the same key), or asymettric (each side has a private key and they exchange public keys).

