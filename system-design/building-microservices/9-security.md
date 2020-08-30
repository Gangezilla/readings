# Security

## Authentication and Authorization

Authentication is the process by which we confirm a party is who they say they are, and the person being authenticated is called the **principle*. Authorization is the mechanism by which we map from a principal to the action we allow them to do. When a principal is authenticated we are often given info about them that helps us decide what we should let them do. With distributed apps, we don't want people to log in to every system.

## Common Single Sign-On Implementations

When a principal tries to access a resouce, they're directed to authenticate with an *identity provider*, which could be user/password or something else. Once the identity provider is satisfied that the principal is authenticated, it gives info to the *service provider*, allowing it to decide whether to grant access.

### SSO Gateway

With microservices, you'll use a gateway as a proxy which sits between your services and the outside world. THis acts as a centralized place for behaviour around performing the auth handshake and redirecting.

