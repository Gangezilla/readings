# Promises

A `Promise` is a proxy for a value that's not necessarily known when the promise is created. It allows you to associate handlers with an aysnc action's eventual success value or failure reason. This lets async methods return values like a synchronous method would. The async method returns a promise to supply the value at some point in the future. A promise is either:

- pending: initial state, neither fulfilled nor rejected
- fulfilled: meaning it completed successfully
- rejected: meaning it failed

## Creating a Promise

A `Promise` object is created using the `new` keyword. Your promise has to have `resolve` and `reject` functions. If you wanted to provide a function with promise functionality, it just needs to return a promise.

```js
function myAsyncFunction(url) {
  return new Promise((resolve, reject) => {
    console.log("do something");
  });
}
```

So I can write a function like this

```js
const x = () => {
  return new Promise((resolve, reject) => {
    resolve("Success!");
  });
};
```

and then call it like this

```js
x().then(result => console.log(result));
```

and I'll get my success message.

## Promises in Node.js

Promises are basically an advancement of callbacks in Node. While developing an app, you may encounter that you're using lots of nested callback functions. A Promise in Node represents an action that will either be completed or rejected. Promises notify whether the request is fulfilled or rejected. Callbacks can be registered with the `.then()` to handle fulfillment and rejection.

```js
dboper.insertDocument(db, { name: "Test" }, "test").then(result => {
  console.log("Inserted document", result.ops);
});
```

You can also do a big promise chain with lots of `.then()` and `.catch()` too. Whatever you return from one `.then()` will be the arg for the next one.

```js
...
  .then((documents) => {
    return documents.result
  })
  .then((reuslt) => {
    return result
  })
...
```
