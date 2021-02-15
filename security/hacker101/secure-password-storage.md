# Secure Password Storage

Lots of apps get this wrong in subtle ways.

You should use BCrypt when you want to store passwords on the server. It solves lots of problems but isn't always practical to use for some reasons.

Our goals:

- Impervious to rainbow tables (huge table of pre-hashed passwords that you can compare to extracted hashes)
- Computationally expensive, so brute-forcing is impractical and difficult
- Unique per user so that cracking one hash can't give you the pw of multiple users

Don't use MD5 for your passwords. They're fast, so good for ensuring file validity, but passwords are also easy to crack.

Salting is the process of adding a random value to the start/end of a password to make rainbow tables useless. You need to have unique salt values.