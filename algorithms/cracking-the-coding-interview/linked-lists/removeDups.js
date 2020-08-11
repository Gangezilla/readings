const { LinkedList, printList } = require("./util");

const checkDups = (head, node) => {
  let currentNode = head;
  while (currentNode !== node) {
    if (currentNode.value === node.value) {
      return true;
    }
    currentNode = currentNode.next;
  }
  return false;
};

const removeDups = head => {
  let node = head;
  while (node !== null) {
    if (node.next !== null && checkDups(head, node.next)) {
      node.next = node.next.next;
    } else {
      node = node.next;
    }
  }
  return head;
};

(function() {
  const a = new LinkedList("a");
  const b = new LinkedList("b");
  const c = new LinkedList("c");
  const c2 = new LinkedList("c");
  const d = new LinkedList("d");
  const e = new LinkedList("e");

  a.next = b;
  b.next = c;
  c.next = c2;
  c2.next = d;
  d.next = e;

  // printList(a);
  removeDups(a);
  printList(a);
})();
