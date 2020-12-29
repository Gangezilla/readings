# Object Oriented Rust

Rust lets you have structs but it enforces the idea of type safety. The gist of it is that you can't do type unsafe things.

Linked list, to do a node we're going to use a thing called Box to pop this on the heap memory. We only want one pointer to this heap memory so that Rust will free it by calling it's `drop` function. This way we don't have to worry about memory leaks or double frees. 

In the struct we can't borrow, because there's no good way for that ownership to survive for as long as we need it.

Rust when you access a struct member it deferences it as much as it needs to to get to the main thing.

We have a function called `take` that gives ownership of something to another variable, `.take()`. Under the hood this is doing some unsafe operations that we don't care too much about right now. After we've used this, the value that's left in the original variable is `None`

Rust has this `?` where if a line like this `let node = self.head.take()?;` is `None`, the `?` will return straight out of the function with `None`. This is very slick Rust error handling.

```rust
struct LinkedList {
    head: Option<Box<Node>>,
    size: usize,
}

struct Node {
    value: u32,
    next: Option<Box<Node>>,
}

impl Node {
    pub fn new(value: u32, next: Option<Box<Node>>) -> Node {
        Node {value: value, next: next}
    }
}

impl LinkedList {
    pub fn new() -> LinkedList {
        LinkedList {head: None, size: 0}
    }

    pub fn get_size(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.get_size() == 0
    }

    pub fn push(&mut self, value: u32) {
        let new_node: Box<Node> = Box::new(Node::new(value, self.head.take()))
        self.head = Some(new_node);
        self.size += 1;
    }

    pub fn pop(&mut self) -> Option<u32> {
        let node = self.head.take()?;
        self.head = node.next;
        self.size -= 1;
        Some(node.value)
    }
}

fn main() {
    let list: LinkedList = LinkedList::new();
}
```