# Go and web applications

## Using Go for web applications

### Scalable web applications and Go

Web apps should be scalable, meaning you can quickly and easily increase capacity to take on a bigger volume of requests. It can be:

- Vertical: by increasing the amount of CPUs or capacity in a single machine
- Horizontal: Increasing the number of machines to expand capacity.

Go vertically easily because of it's support for concurrent programming. It can also scale horizontally by layering a proxy above a number of instances of a Go web app.

### Modular web applications and Go

Web apps should be built with components that work interchangeably, allowing you to add/remove/modify features easily and giving you flexibility.

Go's interface mechanism and dynamic typing makes it v modular.

### Maintainable web applications and Go

Clean and simple syntax, flexible package system, good dev tooling. You've also got `godoc` and `gotest` built in for easy documentation and testing.

### High performing web apps and Go.

One of Go's design goals is to approach the performance of C, and the results are quite compoetitive.

## How web applications work
In a purist sense, a web app is a prorgam that responds to an HTTP request by a client, and sends HTML back in a HTTP response.

For our purposes, a web app:

- Must return HTML to a calling client that renders HTML and displays to a user.
- The data must be transported to the client through HTTP.

## A quick introduction to HTTP

HTTP is the app-level communications protocl that powers the web.

HTTP is a stateless, text-based, request-response protocol that uses the client-server computing model.

*Request-response* is a basic way two computers talk to each other. The first sends a request, and the second computer responds to that request. 
A *client-server* computing model is one where the requester (client) always initiates the conversation with the responder (server).
HTTP is a stateless protocol, meaning that each request returns a response and that's all the protocol remembers. 

## Parts of a web app

### Handler

A handler receives and processes the HTTP request sent from the client. It'll also generate HTML and bundle data into the HTTP response.

In an MVC pattern the handler is the controller and also the model. Ideally, the controller would be thin with only routing and HTTP message unpacking and packing logic. The models contain the application logic and data.

Sometimes you get functions or "service objects" to manipulate models, freeing them from becoming too bloated.

