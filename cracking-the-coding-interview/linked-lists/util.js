const LinkedList = function(value) {
  this.value = value;
  this.next = null;
};

const printList = head => {
  const values = [];
  while (head !== null) {
    values.push(head.value);
    head = head.next;
  }
  console.log(values);
};

module.exports = {
  LinkedList,
  printList
};
