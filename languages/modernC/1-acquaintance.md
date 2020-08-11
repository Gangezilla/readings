## Buckle up :grimacing:

- This chapter focuses mostly on unsigned integers
- Pointers in steps
- Focus on arrays over pointers instead.

- Bind type modifiers and qualifiers to the left `char* name;`
- Use array notation for pointer parameters
- We use function notation for function pointer parameters.

## Control Flow

### Conditional Execution

---

- C has if statements as you know and love:

```c
if (i > 25) {
  j = i - 25;
}
```

- Here, `i > 25` is known as the _controlling expression_, and the part in the brackets is the _dependent block_
- You can also combine it with an `else` statement too.
- You can combine `if`s and `for`s too.
- In C, the value 0 represents logical false. It, and NULL are the only false values. Everything else is logical true.
- `!=` and `==` let us test for equality and inequality respectively.
- Don't compare directly to 0, false, or true. Use the equality and inequality operators because it makes your code clearer and easier to understand.

### **Iterations**

- The `for` statement lets us iterate over a domain.
- You've also got `do` and `while` statements. A while loop is as we know and love, but a `do while` loop looks like this:

```c
  do {
    blah blah
  } while (condition);
```

- This means if the condition is false, a while loop won't run its block at all, and a do loop will run it once. This is because the condition gets checked afterwards.
- You can also break out of a loop with `break`, and you can use `continue` to start the loop again, skipping everything else that comes afterwards.
- You've also got `else if` and `switch` statements as well.

### Expressing computations

- The type `size_t` represents values in the range [0, SIZE_MAX]. SIZE_MAX is quite large, and varies based on the platform. On a 64 bit system its a very very large number.
- Symbols and combinations like `+` and `!=` are called operators, and the things that they're applied to are called operands.
- Unsigned arithmetic is always well defined, that is, regardless of the values we feed into an operation, our computation will always have a valid result as long as it's withing the range [0, SIZE_MAX].
- Unsigned / and % are well defined only if the second operand is 0.
- In the case of overflow, unsigned arithmetic wraps around. This means that for `size_t` values, `SIZE_MAX + 1` is equal to 0, and `0 - 1` is equal to SIZE_MAX.

### Operators that modify objects

- You can do assignment, `a = 42`. We tend to call the one on the left the object, and the one on the right the value.
- You've also got your classic `-=`, `+=` and so on.
- Avoid side effects when performing calculations, and never modify more than one object in a statement.

### Boolean context

- Several operators yield a value 0 or 1, depending on whether some condition is verified. They can be grouped as either comparisons or logical evaluation.
- Comparison operators are `==`, `!=`, `<` and `>`
- Logical operators operate on values that are already supposed to represent a false or true value.
- Because false and true are both just integers, you can use them as indices as well.
- The operators `&&` and `||` have short-circuit evaluation too, so the second operation won't run if the first one is true.

### Evaluation Order

- `&&`, `||` and `?:` evaluate their first operand first.

## Basic Values and Data

- We use various numbering systems, like, you know base 2, 10 and 16. But an interesting one is base 12, which we use for time and clocks etc. Neat.
- C programs primarily reason about values and not their representation. That means that to make truly portable code we need to be conscious of the number systems in use by different architectures.

### The abstract state machine

- A C program can be seen as a sort of machine that manipulates values; variables at a point in time and also intermediate values.
- Not all operations and their resulting values are observable from within your program. They are observable only if they're stored in addressable memory, or written to an output device.
- The C compiler is allowed to shortcut and of the steps during a process called _optimisation_ only if it ensures the realisation of the end results. For example, a variable that is only used once to print a value out, may remove that variable altogether and hardcode it into the print statement, such as:

```c
double x = 5.0;
printf("x is %g\n", x);
// becomes
printf("x is 5.0");
```

- That is, it does the computations at compile time, and the excutable will just print a fixed string. All the code, and even the variable definitions get removed.
- For an optimisation to be valid, it is only important that a C compiler produces an executable that reproduces the _observable states_. This whole mechanism of change is called the abstract state machine. C's mechanism allows different platforms to realise the abstract state machine of a given program differently according to it's needs. We'll learn more about said abstract state machine later on.

#### Values

- All values are numbers or translate to numbers. A value in C is an abstract entity that usually exists beyond your program.
- The data of a program execution consists of all the assembled values of all objects at a given moment. The _state_ of the program execution is determined by the executable, the current point of execution, the data and outside intervention (like IO).
- Therefore, an executable that runs with the same data from the same point of execution must give the same result. But because we want our programs to be portable, we want to depend on more than this, so we depends upon the program specification in the form of _types_.

#### Types

- A type is an additional property that C associates with values. All values have a type that is statically determined. This means that operations on a value are determined by its type. Therefore, a value's type determines the result of all operations.

#### Binary representation and the abstract state machine

- C cannot entirely impose limitations on operations. C only imposes limitations on operations where the results of an operation can be deduced from either the values of the operands, or some characteristic values that describe the particular platform.
- A type's binary representation determines the results of all operations, and a type's binary representation is observable.
- All computation is fixed through the values, types and their binary representations that are specified in the program. The program text describes an abstract state machine that regulates how the program switches from one state to the next. Therefore, programs execute as if following the abstract state machine.

#### Optimisation

- How a concrete executable follows the description of the abstract state machine is left to the discretion of the compiler. However, most modern C compilers produce code that doesn't follow the exact code prescription, they take shortcuts and only follow the code literally during observable states of the abstract state machine.
- The compiler decides which optimisations it can make based on type. For example, it may or may not decide to optimise doing multiple operations to a value if that operation could cause overflow. This slackness between program code and executable code is actually super valuable, and is one of the things that leads C to being very high performing.

#### Basic types

- Two different classes of numbers, each with two subclasses: signed and unsigned integers, real and complex floating-point numbers.
- Each of these contain several types, all differing according to their precision and this determines the valid range of values that can be stored in each one.
- Use unsigned numbers for small quantities that can't be negative.
- Use signed for small quantities that can be negative.
- Use `ptrdiff_t` for large differences that have a sign.
- Use `double` for floating point calculations
- Use `double complex` for complex calculations

OK, so there's a lot about numbers in here and I've skipped a lot of it sorry.

### Initialisers

- Initialisers are an important part of an object definition, they help us guarantee that a program execution is always in a defined state.
- Therefore, all varaibles should be initalised. The only exceptions to this are variable-length arrays because they don't allow for an initaliser.
- For scalar types (meaning they hold a single data item) like integers and floating points you'd do like `double a = 7.8;`. For other types, you must use `{}`. An array for example looks like `double A[] = {7.8, };` or `double B[3] = {1, 2, 3}`.
- For arrays that have an _incomplete type_ where no length is specified, the initialiser specifies the length to complete this. However, it's better to use a designated initaliser by specifying the number as it makes your code better.

There's a lot in here about bits and constants but it doesn't feel as relevant for me right now.

## Derived Data Types

- Here we talk about grouping objects into arrays, using pointers as opaque types, combining objects into structures, giving types new names with typedef
- Arrays and structures are called aggregate data types because they combine multiple instances of one or several other data types.
- The two other strategies to derive data types are more involved. You've got **pointers**, which refer to an object in memory. They're the most involved concept which gets discussed later. Here we only discuss them as an opaque data type only. You've also got **unions**, which overlay different base types in the same memory location. They require a deeper understanding of C's memory model, and aren't too useful so we discuss them way later.

### Arrays

- Arrays allow us to group objects of the same type into an encapsulating object. Arrays and pointers are closely related in C. Arrays look like pointers, and pointers refer to array objects. We chose arrays first because it's easier to describe them in a way that's consistent with C's assumptions about the abstract state machine.
- Firstly, arrays are **not** pointers.

#### Array operations

- An array in a condition evaluates to true. It's also important to note that we can't evaluate arrays like other objects. This is because there are array objects, but no array values.
- Arrays also can't be compared, or assigned to.
