# Access control vulnerabilities and privilege escalation

Access control, or authorization, is the application of constraints on who or what can perform actions or access resources. It depends on:

- Authentication identified the user and confirms that they are who they say they are.
- Session management identifies which subsequent HTTP requests are being made by that same user.
- Access control determines whether the user is allowed to carry out the action that they're attempting to perform.

Broken access controls are a commonly encountered and often critical security vulnerability. From a user perspective, access controls can be divided into the following categories:

- Vertical access controls are mechanisms that restrict access to sensitive functionality that's not available to other types of users. This means that different types of users have access to different application functions, like, an admin who can delete an account.
- Horizontal access controls are mechanisms that restrict access to resources to the users who are specifically allowed to access them.
- Context-dependent access controls restrict access to functionality and resources based on the state of the application or the users interaction with it. They might prevent a user performing actions in the wrong order for example.

## Broken access controls

### Vertical privilege escalation

If a user can gain access to functionality that they're not permitted to access then this is vertical privilege escalation. For example if a non-admin user can gain access to an admin page where they can delete user accounts, this is vertical privilege escalation.

### Unprotected functionality

Vertical privilege escalation arises where an app doesn't enforce any protection over sensitive functionality. For example, admin functions might be linked from an admin's welcome page but not from a user's page, meaning if an admin knows the URL they can get here. Sometimes you can use something like a `robots.txt` to find out what an admin URL would look like.

Sometimes sensitive functionality is not robustly protected but is concealed instead. An app that hosts admin functions at a certain URL might leak it to users in the JS for instance.

### Parameter based access control methods

Some apps determine the user's access rights or role at login and then store this info in a user-controllable location such as a hidden field, cookie or preset query string parameter. The app then makes access control decisions based on the submitted value.

### Broken access control resulting from platform misconfiguration

Some apps enforce access controls at the platform layer by restricting access to specific URLs and HTTP methods based on the user's role. Like, an app might configure rules like `DENY: POST, /admin/deleteUser, managers` which denies access to the POST method on that URL for users in the managers group.
Some app frameworks support various non-standard HTTP headers that can be used to override the URL in the original request. If the app uses rigourous front end controls to restrict access based on URL, but the app allows the URL to be overridden via a request header, it might be possible to bypass the access controls.
