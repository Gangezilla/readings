# Packages and Crates

Crates are binaries or libraries. There's a bunch in here about crates, but we 

## Modules

Modules let us organise a crate into groups for readability and easy reuse. Modules also control the privacy of items.

We define a module by starting with the `mod` keyword and then specify the name of the module with curly brackets `mod front_of_house {`.

## Paths for referring to an item in the module tree

Paths can be:

- absolute starting from the crate root by using a crate name or literal `crate`
- relative, starting from the current module and uses `self`, `super` or an identifier in the current module.

Both are followed by one or more identifiers separated by double colons. Both are valid, for example:

```rust
mod front_of_house {
    mod hosting {
        fn add_to_waitlist() {}
    }
}

pub fn eat_at_restaurant() {
    // absolute
    crate::front_of_house::hosting::add_to_waitlist();

    // relative
    front_of_house::hosting::add_to_waitlist();
}
```

The above won't compile cos `hosting` is private. Modules are useful in this way so that we can fence off implementation details. If we want to fix this, we can pop `pub` in front of `mod hosting` and `fn add_to_waitlist`.

You can also bring a module into scope by using the `use` keyword:

```rust
mod front_of_house {
    pub mod hosting {
        pub fn add_to_waitlist() {}
    }
}

use crate::front_of_house::hosting;

pub fn eat_at_restaurant() {
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();
}
```

You can provide a new name with the `as` keyword like so `use std::io::Result as IoResult;`

We can combine `use` statements like this

```rust
use std::cmp::Ordering;
use std::io;

use std::{cmp::Ordering, io};
```

You can also pull everything from a package in using the "glob" operator

`use std::collections::*;`

You can also split big modules into multiple files.