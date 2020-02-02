const Stack = require("./Stack");

// the gist would be to overwrite the add implementation to keep track of the min
// then add a new method to return the min.

const StackMin = function() {
  this.stack = new Stack();
  this.currentMin = null;
};

StackMin.prototype.push = function(value) {
  if (this.currentMin === null || this.currentMin > value) {
    this.currentMin = value;
  }
  this.stack.push(value);
};

StackMin.prototype.min = function() {
  return this.currentMin;
};

// everything else is the same, cbb to rewrite it here...

(function() {
  const s = new StackMin();
  s.push(9);
  s.push(8);
  s.push(7);
  s.push(6);
  s.push(2);

  console.log(s.min(), "minimum");
})();
