# Pointers & Arrays

- A pointer is a variable that contains the address of a variable. They're used in C heaps because they're sometimes the only way to express a computation and because they lead to more compact code.
- Pointers can create awful code, but with discipline can be used to achieve clarity and simplicity.

## Pointers and Addresses

- A typical machine has an array of consecutively numbered or addressed memory cells that may be manipulated indivudally or in groups.
- The unary operator, `&` gives the address of an object. So the statement `p = &c;` assigns the address of c to the variable p, and p now points to c.
- The operator `*` is the dereferencing operator, and when its applied to a pointer it accesses the object the pointer points to.
- So we use `&` to define a pointer, and `*` to get the value from a pointer.
- The declaration of a pointer, `int *ip` is intended as a mnemonic to help you remember that `*ip` is pointer to an int.
- Since pointers are variables, they can be used without dereferencing. Like, if iq is another pointer to int, `iq = ip`, copies the contents of ip into iq making iq point to whatever ip pointed to.

## Pointers and Function Arguments

- Since C passes arguments to a function by value, there's no direct way for the the called function to alter a variable in the calling function.
- For example, if you're writing a function to swap the values of two variables, doing this without pointers wouldn't work as you'd only be swapping copies. Thus, you'd need pointers for this to work.
- Pointer argumnets enable a function to access and change objects in the function that called it.

## Pointers and Arrays

- In C, there is a strong relationship between pointers and arrays. They're so similar they should be discussed together. Generally any operation that you'd achieve with array subscripts can be done with pointers. It'll be faster, but might look more complicated.
- The declaration `int a[10];` defines an array, a, of size 10. That is, a block of 10 consecutive objects.
- If a pointer points to a[0], then `pa + 1` points to the next element. So yeah, you can add to a pointer and then it'll just point to whatever the next object in memory is now.

## Address Arithmetic

- Address arithmetic is a method of calculating the adress of an object with the help of arithmetic operations on pointers. For example, if we had a pointer `p`, we can do `p++` to get the next element in memory.
- C has two routines for memory allocation. The first is `alloc(n)`, which returns a pointer p to n-consecutive character positions, which can be used by the caller of `alloc` to store characters. It's sibling function is called `afree(p)` which is used to free up the memory. They're rudimentary tho, cos the memory handled by them is managed by a stack, so it has to be released LIFO style. You'd usually use `malloc` and `free` FYI.
- The easiest way to implement a rudimentary storage allocator is to have `alloc` hand out pieces of a large character array, which is private. We'd need to know how much of this large memory array has been used, and we'd have a pointer that points to the next free element. With that pointer, we'd check if there's some free space left that's enough. If there is, we return a pointer to that block of memory, otherwise we return zero.
- If pointers `p` and `q` point to members of the same array, then relations like `==`, `!=` etc work properly.

## Character Pointers and Functions

- A string constant, such as "Hello" is an array of characters. In the internal representation, the array is terminated with the null character `\0` so that programs can find the end. This means the length in storage is one more than the number of characters between the double quotes.
- When a character string like this appears in a program, access to it is through a character pointer.
- Writing `char amessage[] = "string string"` gives you an array of characters, whereas writing `char *pmessage = "string string"` will give you a pointer to that string in memory.
- C doesn't have any built in string manipulation functions, because to C they're all just chunks of memory.
- This means you'll need to write your own string manipulation functions.

### Exercise 5-3:

```c
char *strcat(char *string, char *stringToBeJoined, size_t size) {
  char *newPointer; // initialise a new pointer
  newPointer = string; // set the new pointer to the string pointer.
  while (*newPointer != '\0') {
    newPointer++;
  } // this loop finds the last memory block and sets our pointer to it

  while(size > 0 && *stringToBeJoined != '\0') { // we then go through our string we're cat'ing on making sure the size is valid and we havent reached the end
    *newPointer++ = *stringToBeJoined++; // we iterate our pointer, and the string and we set the new string in memory.
    size--;
  }
}

```
