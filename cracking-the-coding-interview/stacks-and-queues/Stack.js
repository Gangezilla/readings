const LinkedList = require("./LinkedList.js");

// Stack using a linked list
const Stack = function() {
  this.top = null;
};

Stack.prototype.push = function(value) {
  const newEntry = new LinkedList(value);
  newEntry.next = this.top;
  this.top = newEntry;
};

Stack.prototype.pop = function() {
  const popped = this.top;
  if (this.top !== null) {
    this.top = popped.next;
  }
  return popped.value;
};

Stack.prototype.peek = function() {
  if (this.top !== null) {
    return this.top;
  } else {
    return null;
  }
};

Stack.prototype.isEmpty = function() {
  return this.top === null;
};

module.exports = Stack;
