# C Arrays, Strings & Pointers

## Recap

- Memory is just a whole bunch of bytes, it's where all your data lives.

## Address vs Value

- An address is the number you give each cell to say where it lives. The value is what's stored in this cell.

## Pointer

- A pointer is a variable that contains an address. It's just another number, but it gets interpreted as a location. It's just another variable, which gets interpreted as the value of another cell. A pointer sits in memory too, but it's value is a memory address.
- The memory doesn't understand that it's an address, it's all just a bunch of bits under the hood. The context will tell you what to do with this. At the C language level you make this distinction

## Syntax

- `int *x;` - tells compiler that variable x is address of an int
- `x = &y;` - tells compiler to assign _address of y_ to x. `&` is called the address operator.
- `z = *x;` - tells the compiler to assign value at address in x to z. `*` called the _dereference operator_.

## Creating and Using Pointers

```c
int *p, x;
x = 3;
p = &x;
printf("p points to %d\n" *p);
```

- - is used to declare the type of the pointer, is also used as an operator to dereference the pointer. Depending on the context you can tell which is which.

## Pointers and Parameter Passing

- C passes parameters "by value", ie: by copying the values. This means you get a copy of a value. Lots of functions use pointers to change a variable, but like, why wouldn't you just make the variable be the result of the function? I guess they're contrived examples but still...

```c
void add_one(int *p) {
  *p = *p + 1;
}

int y = 3;
add_one(&y);
```

- Here, p itself isn't changing, but the value p points to is being changed.

## Types of Pointers

- Pointers are used to point to any kind of data (int, char, struct...)
- `void *` is a type that can point to anything, but because the compiler lets you treat it as anything, it won't check for mistakes for you. You have to be really careful with it.

## More C Poitner Dangers

- When you declare a pointer, all you're declaring is that you need some space to hold a cell that'll hold the address of something else. When you declare a pointer, you havent necessarily given it a value.
- When you declare a pointer, there's nothing in it. It's probably just garbage.
- Be clean and put type declarations on everything.
- Use the compiler to find your warnings.

## Pointers in C

- Why use pointers? If we want to pass a large struct or array, it's easier/faster to pass a pointer than pass the whole thing. If you want to modify an object, not just pass its value.
- They're the biggest source in bugs in C
- Low level system code still needs low-level access via pointers. For a lot of applications, performance isn't super critical. For those applications use something like Python or Java.

## C Arrays

- Declaration `int ar[2];` declares a 2 element integer array: just a block of memory.
- `int ar[] = {795, 634};` inits a 2 element array and then puts the values in there.

## C Strings

- Strings in C are just an array of characters. `char string[] = "ABC";`
- You find the length of a string by reading to the end of it.

## Array Name / Pointer Duality

- Declaring an array name is basically the same as a pointer. Array variable is a "pointer" to the first element.
- So, array varaibles are almost identical to pointers.
- This means that `ar` is an array varaible, but looks like a pointer. Can use pointer arithmetic to conveniently access arrays.
- You declare a pointer to a pointer with `**`. You just add a star for every time you increase the pointer. Pretty lolz.

## C Arrays are very Primitive

- An array in C doesn't know its own length, and its bounds aren't checked. This means we can very easily go off to the end. We can resolve this by assing the array, as well as the length of the array.
- Segmentation faults + bus errors are really hard to find, but are super bad.

## Use Defined Constants

- For an array, it's good to set the size of it so you'll always know exactly how big it is. When all your arrays use this magic number, you can update this in one spot instead of repeatedly.

## Pointing to different size objects

- Different types take up different amounts of space. Modern machines are byte addressable, so you can access each of those bytes. A C pointer is an abstraction of that memory address.
- Depending on the type of the pointer, the amount of data you get back varies.
- The original motivation for using a byte as a standard, was that that is the amount you need to hold a Western character.
- `sizeof(type)` will return to you the number of bytes that an object takes in your particular machine. In the olden days, a byte could be 5,6,7,9 bits long in different kinds of computers.
- We have 8 bit bytes thanks to IBM. They chose 8 bit bytes so they could have 7-bit ASCII and their own encoding. It was so popular that everyone copied it to become IBM compatible. It's just convenient that it's power of two wtf.

## Pointer Arithmetic

-
