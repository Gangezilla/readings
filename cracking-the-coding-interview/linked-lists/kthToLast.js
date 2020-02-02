const { LinkedList, printList } = require("./util");

const getLinkedListLength = head => {
  let count = 0;
  while (head !== null) {
    head = head.next;
    count++;
  }
  return count;
};

const returnKthToLast = (head, kth) => {
  const length = getLinkedListLength(head);
  const indexToRemove = length - kth - 1;
  let i = 0;
  while (i <= indexToRemove) {
    if (i === indexToRemove) {
      console.log(head.value);
      break;
    }
    head = head.next;
    i++;
  }
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

  returnKthToLast(a, 2);
})();
