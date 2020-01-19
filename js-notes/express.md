# Express

## Middleware

Middleware functions are functions that have access to the request object (`req`) and response object (`res`), as well as the next middleware function which is usually called `next`.

Middleware can:

- Execute any code.
- Make changes to the request and response cycle.
- End the request-response-cycle
- Call the next middleware function in the stack

If the current middleware function doesn't end the request-response cycle, it must call `next()` to pass control to the next middleware function, otherwise the request will be left hanging. There's several kinds of middleware for Express.

### Application-level middleware

Bind application-level middleware to an instance of the `app` object by using the `app.use()` and `app.METHOD` where method is `get` or `post` or whatever.

This function gets executed every time the app receives a request.

```js
var app = express();

app.use(function(req, res, next) {
  console.log("Time: ", Date.now());
  next();
});
```

This function will be executed for any type of HTTP request on the `/user/:id` path.

```js
app.use("/user/:id", function(req, res, next) {
  console.log(("Request Type:": req.method));
  next();
});
```

This function will be hit every time theres a GET request on `user/:id`.

```js
app.get("/user/:id", function(req, res, next) {
  res.send("USER");
});
```

This function demonstrates a series of middleware functions that will be executed in order on any HTTP request to the `/user/:id` path

```js
app.use(
  "/user/:id",
  function(req, res, next) {
    console.log("blah blah");
    next();
  },
  function(req, res, next) {
    console.log("something else");
    next();
  }
);
```

You can skip the rest of the middleware functions from a router middleware stack by calling `next('route')`. This only works when middleware functions are loaded by using `app.METHOD`.

```js
app.get(
  "/user/:id",
  function(req, res, next) {
    if (req.params.id === "0") next("route");
    else next();
  },
  function(req, res, next) {
    res.send("something");
  }
);
```

Middleware can also be declared in an array for reusability.

```js
function logOriginalUrl(req, res, next) {
  console.log(req.originalUrl);
  next();
}

function logMethod(req, res, next) {
  console.log(req.method);
  next();
}

var logStuff = [logOriginalUrl, logMethod];
app.get("/user/:id", logStuff, function(req, res, next) {
  res.send("User Info");
});
```

### Router-level middleware

Router-level middleware works in the same way as application-level middleware, except it's bound to an instance of `express.Router()`, like `var router = express.Router()`

It works pretty similar to the previous ones, tbh, so a few examples:

```js
var app = express();
var router = express.Router();

// gets executed for every request.
router.use(function(req, res, next) {
  console.log(Date.now());
  next();
});
```

### Error-handling middleware

Error handling middleware ALWAYS takes four arguments. You must specify all four arguments to maintain the signature, otherwise it won't work. You define it like so:

```js
app.use(function(err, req, res, next) {
  console.error(err.stack);
  res.status(500).send("Uh oh!");
});
```

## Routing

Routing refers to how an app's endpoints respond to client requests. You define routing using methods of the Express `app` object that correspond to HTTP methods. This supports all the HTTP methods you know and love: GET, POST, PUT, DELETE etc. You can also use `app.all()` to have this be hit for every route.

### Route parameters

Route parameters are named URL segments that are used to capture the values specified at their position in the URL and they go to the `req.params` object.

```js
app.get("/users/:userId/books/:bookId", function(req, res) {
  res.send(req.params);
});
```

### express.Router

Use the `express.Router` class to create modular, mountable route handlers. A `Router` instance is a complete middleware and routing system. This example creates a router as a module, loads a middleware function, defines some routes and mounts the router module on a path in the main app.

```js
var express = require("express");
var router = express.Router();

router.use(function(req, res, next) {
  console.log(Date.now());
  next();
});

router.get("/", function(req, res) {
  res.send("Home page");
});

router.get("/about", function(req, res) {
  res.send("About");
});

module.exports = router;
```

If you put this in a file called `birds`, you'd be able to handle requests to `/birds` and `/birds/about` like so:

```js
var birds = require("./birds");

app.use("/birds", birds);
```
