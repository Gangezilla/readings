# Burp 101

Burp Proxy is a man in the middle proxy that can intercept requests and see everything going over the wire. We use Firefox because it has proxy setings built in, most other browsers require system wide.

- Target: Gives you a tree view of all the sites you've visited. You can use target site map to set domains as in and out of scope. When you're testing things, you generally know what's in and out of scope and this is really helpful.
- Proxy: View requests in flight in intercept. Intercept tab has one of the more fun tools, lets you see all requests. You can manipulate these requests as well. You can go and change stuff in the options to say youre not interested in certai files. 
  - Match and Replace: Lets you automatically replace header value. There's also an option to unhide hidden form fields.
- Spider: Useful to find a number of sites you might have missed.
- Intruder: Automated tests
- Repeater: Used to repeat existing requests and test them for various bugs. Lets you execute HTTP requests and see what their responses are. In this tab you've got an editable request field. You can select a page from the history and click "send to repeater" and you can play around with this particular. When this guy is testing a site, he spends most of his time in the proxy and repeater. Find an interesting request, and play around. It'll also automatically encode key characters instead of you having to do this yourself.
- Sequencer: Tokens, find flaws
- Decoder lets you encode and decode text. This is really cool, lets you paste stuff in, decode it and encode it etc.
- Comparer: Lets you compare two blocks of data

- Intruder lets you do a large number of attacks. You can send a request over to Intruder, and then you have attack types:
  - Sniper: Generates a payload and 
  - Battering ram: Puts each payload in all positions at once.
  - Pitchfork: Takes a payload set and iterates over them at once.
  - You can do an attack to iterate through a whole bunch of IDs, and then scroll down for grep and you can pull specific information out.
  - Send a login request to intruder, use a payload request of runtime file which contains a list of common user names.
  - Intruder is really cool.

- Scanner
  - Active: You can send requests over to this and it can look for vulnerabilities, like finding bad SSL certs, SQLI and stuff.
  - Passive: Happens while you're doing stuff automatically. Automatic tests for SQLI and other stuff.
  - In the options menu you can switch certain things on or off

