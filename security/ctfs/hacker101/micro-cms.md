1: Can use XSS to get a flag when you create a new page beecause your input is reflected onto the page.
2: When you're editing you can put a `'` at the end of the ID because it uses the literal ID and not a hash.
3: You can enumerate through to different IDs when you edit to get a flag. Worth noting that if you notice something like enumerable IDs to play around with this in different places too.