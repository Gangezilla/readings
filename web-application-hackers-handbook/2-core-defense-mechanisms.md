
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

In terms of attack surface, the session management mechanism is highly dependent on the security of its tokens, with most attacks seeking to compromise other users' tokens. This would allow an attacker to masquerade as another user and use the app as if they'd logged in as that user. Vulnerabilities arise from defects in how tokens are generated which can  enable an attacker to guess the tokens that have been issued, and also in how a token is handled which could lead to intercepting someone elses token.
