const LinkedList = function(value) {
  this.value = value;
  this.next = null;
};

const printList = head => {
  while (head !== null) {
    console.log(head.value);
    head = head.next;
  }
}

module.exports = {
  LinkedList,
  printList,
}
