`ssh leviathan0@leviathan.labs.overthewire.org -p 2223`


0: leviathan0 / leviathan0
Solved by going into the puzzle directory, grepping through `bookmarks.html` for `leviathan1`.

1: leviathan1 / rioGegei8m
Went into folder, ran gdb on the `check` program... and we didn't have to do any of that. ran `ltrace` on it and we can see the password is `sex`. Using this changes our user to leviathan2 and we can go to `etc/passwd` to find `ougahZi8Ta`


https://www.hacker101.com/videos