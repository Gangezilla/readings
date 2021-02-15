# The Web in Depth

## Requests

- Method: GET/POST/DELETE...
- Host
- Accept: Indicates what MIME types are accepted
- Cookie: Passes cookie data to the server
- Referer: Page leading to this request
- Authorization: Used for basic auth pages (mainly). Takes the form "Basic <base64'd username:password>

## Cookies

Key value pairs, stored on the client for a fixed period of time. Each cookie has a domain pattern that it applies to and they're passed with each request the client makes to matching hosts.

It's bad if Cookie A goes to server B and viceversa.

Cookies added for .example.com can be ready by any subdomain of example.com. A cookie added for a subdomain can only be read in that subdomain and its subdomains. A subdomain can set cookies for its own subdomains and parents, but it cant set cookies for sibling domains. So `test.example.com` can set on `example.com` and `foo.test.example.com` but not `test2.example.com`. Important to keep this hierarchy in mind as you're scoping cookies. This is messed up often.

Set-cookie
There's two important flags to know for cookies.

- Secure: Will only work on HTTPS pages.
- HTTPOnly: The cookie cannot be read by JS, can only be sent up with web requests. Usually you could use document.cookie to read and manipulate. But with HTTPOnly you can't do this.

## HTML

HTML should be parsed according to the relevant spec, generally HTML5 now. It's not just parsed by a browser tho, it's parsed by a firewall too. If there's any discrepancy this will often lead to a vuln you can exploit.

Canonical example is injecting `<script/xss...>` and it gets parsed.

Browsers are built to handle the web, and they have lots of legacy parsing. HTML5 has specifics on how that legacy parsing should happen. 

- A `<script>` tag on its own will automatically be closed at the end of the page. This can be used in a URL where you can't get a slash in there.
- A tag missing its closing angle bracket will automatically be closed. Having an open angle tag inside of another tag is valid and will throw off old firewalls. An old trick was to wrap script tags in another tag to get your script parsed.

## Content Sniffing

Sending HTML to the browser and it'll fill in the blanks. 

### MIME sniffing

Used to get a lot of browsers. The browser often looks at whats on the page instead of just the Content-Type header. If it has enough markers, the browser will treat it like HTML. In IE6/7, image and text files containing HTML tags would execute as HTML. In enterprises, IE6/7 bugs are still huge.

Imagine you have a site with image upload, an attacker could upload an image with just enough HTML, link it to people and then execute that code on their browser. This is one of the reasons many companies use separate domains to host images and stuff.

### Encoding Sniffing

Lots of pages with all sorts of content on them. The browser will have a character it doesnt understand and try to sniff it out. If you don't specify an encoding, the browser will automatically sniff and apply them.

A good example is putting UTF-7 text into XSS payloads. This will go straight through HTML encoding as there aren't any unsafe characters, but there are unsafe UTF-7 characters. IE7/8 will see this in a page and automatically switch to UTF-7 and switch the parsing over, enabling the attack to succeed. This is good to get through firewalls cos they won't look for UTF-7. Same with if it expects UTF-8 and you sent it UTF-32, it'll go straight through the filters and be automatically determined by the browser.

The rule is that you should always specify what encoding and know what the browser should parse so the server and client don't have discrepancies.

## Same-Origin Policy

Backbone of the web. Underpins browser security now.

SOP is what domains you can contact via AJAX requests, access to the DOM across separate frames/windows. It's really what prevents you from wrecking the web. Anytime it's circumvented bad things happen.

### Origin matching

- Much stricter than cookies.
- The protocols must match, you can never cross HTTP/HTTPS boundary.
- Port numbers must match
- Domain names must be an exact match, no wildcarding or subdomain walking

### SOP Loosening

It's possible for devs to loosen the grip of SOP by changing document.domain, posting messages between windows and using CORS. You can always call postMessage into an IFrame. When you do see message handling, its often wrong. Used a lot to break Chrome extensions, they use `window.postMessage`. 

There's usually no good reason to loosen SOP. There's a design problem if you do.

## CORS

Cross origin resource sharing lets you make requests across domains. CORS is still new and enables some risky situations. You can even pass cookies between domains. CORS is fairly well designed but very much new territory. Look into it.

## Cross-Site Request Forgery (CSRF)

Simple and you find them everywhere. 1/6 apps fall prey to CSRF.

It's when an attacker can get a victim to go to a page and then submit data to the target site as the victim. It's common and brutal.

When the server gets a request, how does it know that it came from the real site? You have the referer header but they're unreliable.

We need to give the server a way to know where requests originate from. The traditional way to do this is to use CSRF tokens. Basically generate a random token and tie it to the user's session. When the server gets a POST request, it should check that the CSRF token is present and matches what's in the users session. This all hinges on POST requests being the only things that change state. But, apps change state with GET requests ALL the time which is super bad. If they do this with GET requests, they're automatically broken even if they're checking.

## Review

Just open up Burp and log into a few pages and you'll see some that are scoped to weird places. 
SOP is strict but complex enough to be a source of headaches for devs and attackers.
If you don't see a CSRF token on a form, it should be an alert. 