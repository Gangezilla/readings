# Session Fixation

Mostly antiquated, but still pops up in legacy PHP apps.

This is when an attacker can use a known session ID to impersonate someone else. 

Two problems:
Session IDs in the query string are easy to leak to other users and using these as the sole source of identification.

Mostly gone away

Sessions are commonly used for consistent auth, but also used to store lots of other bits and pieces.

Getting rid of visible session IDs is critical. When a user logs in, they get a brand new session with a brand new ID, you can also wipe out old sessions.

