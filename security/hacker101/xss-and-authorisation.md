# XSS and Authorisation

## XSS Review

Easily the most common bug.
- Reflexted XSS: user input goes to the server then back down to the client in an unsafe way, permitting injection of arbitrary content.
- Stored XSS: Input from a user is stored on the server and returned later without proper escaping.
- DOM XSS: Input from a user is inserted into the page's DOM without proper handling, enabling insertion of arbitrary nodes.

The first step is figuring out that you can use XSS.

A few steps:

- Figure out where the data goes: If I put in some data, does it go to a file? DB? Try to get a feel for the flow of your data through the app.
- Figure out special handling: Do URLs get turned into links? Is the data being encoded before it goes into the field? 
- Figure out how special characters are handled: Insert '<>:;" and see if any of them get through without encoding, if they do make a note of that. If your URLs get turned into links what happens if they get turned into special chars.

Once you've gone thru you'll know if it's vulnerable or not. If you can throw in a " you'll probs have an XSS vuln. Sometimes special chars will only go through when not a tag. 

If its reflected and triggered via a post, then CSRF mitigations wont matter.

Example
When you're doing step 3, if you notice an angle tag gets through without being encoded. A simple script tag will often get you an exploit. If you can get any special chars in you'll probs win.

In level1's posts, you may have noticed that URLS were automatically turned into links. Double quotes get passed through, even tho angle brackets won't. Here we could use a DOM event to gain simple execution. Not having spaces is a giveaway here. 

If you see your input being reflected in a script tag, there's a tonne of ways this can go wrong.

In the case of strings in scripts, try to avoid this. Escape quotes and slashes and replace angle brackets. Design around this in other ways. 

## Dom-based XSS

The data may or may not ever touch the server, so it needs to be 100% prevented on browser. It looks similar to a rXSS attack.

DOM XSS can happen in a heap of ways. Easiest way to mitigate this is to not put user-controlled data on the page.

## Forced Browsing/Improper auth

For example, you have an admin panel but part of that panel isn't admin only. Things like auto-incrementing IDs are great for this.

Auth-z vs auth-n bugs

If you have IDs, you can increment or decrement to see things you might not be able to.

One of the things I do is perform everything with highest permission and then do lowest and see what succeeds. If a lower privilege user can do stuff they shouldn't, then this is defs a bug. Do this by replaying requests in Burp.

## Wrap up

XSS has three types, reflected stored and DOM
rXSS and sXSS are very close for exploting and mitgating.
never out user input directly in the page.

forced browsing and improper auth are basically the same thing, differences in how the bugs are found.

## XSS Cheat sheet

- "><h1>test</h1>
- '+alert(1)+'
- "onmouseover="alert(1)
- http://"onmouseover="alert(1)