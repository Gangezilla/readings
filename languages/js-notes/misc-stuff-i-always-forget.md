# Misc stuff I always forget

- Two programming paradigms for JS are OOP and functional programming. OOP has prototypal inheritance, whereas functional programming has first class functions, closures etc.

## Closures

Closures are important because they control what is and isn't in scope in a particular function along with which variables are shared between sibling functions in the same containing scope.

A closure is the combination of a function bundled together with references to its surrounding state. It gives you access to an outer function's scope from an inner function. Closures are created every time a function is created.

To use a closure, define a function inside another function and expose it. The inner function will have access to the variables in the outer function scope, even after the outer function has returned.

## Scope

A scope is the current context of execution. The context in which values and expressions are visible, or can be referenced. A function serves as a closure in JS, and thus creates a scope so that a variable defined exclusively within the function cannot be accessed outside of that function, or within other functions.

## Inheritance and the prototype chain

Every object in JS (like `Array`, or `String`). If we construct an object with `new`, we can add a method to it by going `OBJECT.prototype.FUNCTION`. `prototype` is an attribute of all functions and points to a map where attributes can be assigned that should be able to be accessed from all objects created with that function as the constructor.

Every object has a prototype including the prototype object. This 'chain' goes all the way back until it reaches an object with no prototype, which is usually `Object`'s prototype. When an attribute is called on an object, the object is first checked for that attribute and if it doesn't exist, each link in its prototype chain is traversed until found or the end is reached.

## When you type a URL into the browser, what happens?

You type in a URL, the browser checks the cache for a DNS record to find the corresponding IP address of the website, and if the URL is not in the cache then the DNS server initiates a DNS query to find the IP of the server that hosts the URL. The browser initiates a TCP connection with the server using the TCP/IP three-way handshake. After this, the browser sends an HTTP request to the webserver, which will be a GET request most likely. The server will then handle this request and send a response back to you, and that response will be a HTTP response. Your browser will then display and render the HTML content.
