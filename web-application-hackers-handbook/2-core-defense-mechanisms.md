# Core Defense Mechanisms

The fundamental security problem of all user input being untrusted leads to web apps employing defense mechanisms like these:

- Handling user access to the application's data and functionality to prevent users from gaining unauthorized access.
- Handling user input to the app's functions to prevent malformed input from causing undesirable behaviour.
- Handling attackers to ensure that the application behaves appropriately when being directly targeted and taking suitable defensive and offensive measures to frustrate the attacker.
- Managing the application to enable admins to monitor its activities and functionality.

This means that these mechanisms also make up the vast majority of a typical application's attack surface.

## Handling User Access

A central security requirement that web apps need is to control a user's access to its data and functionality. Many web apps have different kinds of users, and they all have certain levels of access. Most web apps handle access using a trio of interrelated security mechanisms:

- Authentication
- Session management
- Access control

Because of their interdependencies, the overall security is only as strong as the weakest link in the chain.

### Authentication

The auth mechanism is logically the most basic dependency in an app's handling of user access. Authenticating a user involves establishing that the user is in fact who they claim to be. Most web apps use a classic username + password combo, and some others that need to be more secure might use additional credentials or other stuff. Despite their superficial simplicity, auth mechanisms suffer from a wide range of defects. Common problems enable an attacker to identify other users' usernames, guess their passwords or bypass the login function by exploiting defects in its logic. When you're attacking a web app, you should invest a significant amount of attention to the various auth-related functions it contains, as defects enable you to gain unauthorized access.

### Session Management

The next logical task is managing a user's session. After logging into the app, the user accesses various pages, making multiple HTTP requests from their browser. The app will also receive requests from different users, some whom are authenticated and some whome are anon. To enforce effective access control, the app needs a way to identify and process requests that originate from each user.
Virtually all web apps do this by creating a session for each user and issuing the user a token that identifies this session. The session is a series of data structures that keep track of the users interactions with the app. The token is a unique string that the app maps to the session. Whe n a user receives a token, the browser submits it back to the server in each HTTP request enabling the app to associate the request with that user.

In terms of attack surface, the session management mechanism is highly dependent on the security of its tokens, with most attacks seeking to compromise other users' tokens. This would allow an attacker to masquerade as another user and use the app as if they'd logged in as that user. Vulnerabilities arise from defects in how tokens are generated which can enable an attacker to guess the tokens that have been issued, and also in how a token is handled which could lead to intercepting someone elses token.

### Access Control

The final logical step is to make and enforce correct decisions about whether each indivudal request should be permitted or denied. If the above mechanisms are working correctly, the app knows the identity of the user from whom each request is received. The app then needs to decide if the user is authorized to perform the action or access the requested data. This mechanism is often a source of vulnerabilities as devs make flawed assumptions about how users will interact with the application and make oversights by omitting access control checks from some functions. Probing for these vulns can be tedious, but they're always a worthwhile investment.

## Handling User Input

### Varieties of Input

A typical web app process user-supplied data in a number of forms. In many cases, an app can impose stringent validation checks on a specific item of input but at other times the app must tolerate a wider range of input. For example, an address field might legit contain letters, numbers, spaces etc but you can still restrict it with say a character limit, and no HTML markup.

Sometimes you need to accept arbitrary input, so you can't just reject it because it looks suspicious. In addition, you've also got numerous items of data that start on the server, go to the client and make their way back to the server such as cookies etc. In cases like this, the app can perform very specific validation of the data received. Like, if you have a cookie, mke sure that a specific value is in place such as an ID or something. If this is modified, it's usually an indicator someone is probing the app so you reject the request, and log the incident for investigation.

## Approaches to Input Handling

Various approaches, but different approaches are often preferable for different situations and different types of input.

### "Reject Known Bad"

This approach usually has a blacklist containing literal strings or patterns that are known to be used. This is the least effective approach because a vulnerability can be exploited in a variety of ways, and a blacklist won't cover everything and also because exploitation techniques are constantly evolving.

These often fall victim to variations to regular attacks too. Like, `2=2--` instead of `or 1=1--`. Blacklist based filters are often vulnerable to NULL byte attacks too. Because of how strings are handled in managed and unmanaged execution contexts inserting a NULL byte anywhere before a blocked expression can cause some filters to stop processing the input and not identify the expression.

Note: Execution context is a language concept that's kinda like the environment including scope, call stack etc.

### "Accept Known Good"

This employs a whitelist containing strings or patterns that match only benign input. The validation mechanism allows data that matches the whitelist and blocks everything else. For example, before looking up a product code, an app might validate that it contains only alphanumeric characters and is exactly six characters long. Where this is feasible, it's considered the most effective way to handle input. It's pretty difficult to use all the time though. While this is good, it's not multi purpose.

### Sanitisation

This approach recognises the need to sometimes accept data that can't be guaranteed as safe. Instead of rejecting this input, the app sanitizes it in various ways to prevent it from having any adverse effects by removing potentially malicious characters, or escaping them. Apps based on data sanitization are often highly effective. The usual defense against cross-site scripting attacks it to HTML-ecnode dangerous chars before they're embedded into pages of the app.
