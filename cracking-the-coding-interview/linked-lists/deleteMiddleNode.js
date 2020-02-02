const { LinkedList, printList } = require("./util");

const deleteMiddleNode = node => {
  const nextNode = node.next;
  node.value = nextNode.value;
  node.next = nextNode.next;
};

(function() {
  const a = new LinkedList("a");
  const b = new LinkedList("b");
  const c = new LinkedList("c");
  const d = new LinkedList("d");
  const e = new LinkedList("e");
  const f = new LinkedList("f");
  const g = new LinkedList("g");
  const h = new LinkedList("h");

  a.next = b;
  b.next = c;
  c.next = d;
  d.next = e;
  e.next = f;
  f.next = g;
  g.next = h;

  printList(a);
  console.log("before ^^^^^");
  deleteMiddleNode(c);
  console.log("after:");
  printList(a);
})();
