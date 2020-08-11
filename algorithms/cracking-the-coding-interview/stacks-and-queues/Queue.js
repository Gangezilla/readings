const LinkedList = require("./LinkedList");

const Queue = function() {
  let front = null;
  let back = null;
};

Queue.prototype.add = function(value) {
  const node = new LinkedList(value);
  if (this.front === null) {
    this.front = node;
    this.back = node;
  } else {
    const previousBack = this.back;
    this.back = node;
    previousBack.next = this.back;
  }
};

Queue.prototype.remove = function() {
  const removed = this.front;
  if (this.front === this.back) {
    this.front = null;
    this.back = null;
  } else {
    this.front = this.front.next;
  }

  return removed;
};

Queue.prototype.peek = function() {
  return this.front;
};

Queue.prototype.isEmpty = function() {
  return this.front === null;
};
