# Arrays, slices and maps

## Array internals and fundamentals

Arrays form the base data structures for slices and maps.

### Internals

An array in Go is a fixed-length data type that contains a contiguous block of elements of the same type. The type information for the array provides the distance in memory you have to move to find each element. Since each element is of the same type and follows each other sequentially, moving through the array is consistent and fast.

### Declaring and initalising

`var array [5]int`
After declaration, neither the data type or length can be changed. If you need more elements you need to create a new array and copy the values from one array to the other. When an array is initalized, all of it's elements are set to 0.
`array := [5]int(10, 20, 30, 40, 50)`
Can also be done as
`array := [...](10, 20, 30);` which will identify the length of the array based on the number of elements.

### Working with arrays.

- Access an individual element `array[2] = 35`
- An array is a value in Go, so you can use it in an assignment operation if the types match `array1 = array2`
- They can also be composed to create multidimensional arrays. In this example we init indexes 1 and 3 `array := [4][2]int(1: (20, 21), 3: (40, 41))`. You'd then access these like `array[0][0]`
- If you wanted to pass an array between functions, you should probably do it with a pointer so you don't have to allocate lots of memory on the stack.

```go
  var array [1e6] int
  // pass the address of the array to the function foo
  foo(&array)
  // foo accepts a pointer to an array
  func foo(array *[1e6]int) {}
```

## Slice internals and fundamentals

A slice is a data structure that provides a way for you to work and manage collections of data. Slices are built around the concept of dynamic arrays that can grow and shrink as you see fit. They're flexible in terms of growth because they have their own built-in function called `append` which can grow a slice quickly and efficiently.

### Internals

Slices are tiny objects that abstract and manipulate an underlying array. They're three field data structures that contain the metadata Go needs to manipulate the underlying array. The three fields are:

- a pointer to the underlying array
- the length or the number of elements the slice has access to
- the capacity or the number of elements the slice has available for growth.

### Creating and initialising

There are several ways to create and initalise slices in Go. Knowing the capacity you need ahead of time will usually determine how you go about creating your slice.

- You can make a slice with the built in `make` function: `slice := make([]string, 5)`. When you specify the length, the capacity of the slice is the same.
- YOu can adjust the length and capacity separately: `slice := make([]int, 3, 5)`. When you specify the length and capacity separately, you can create a slice with available capacity in the underlying array that you don't initially have access to. The slice here has access to three elements, but the underlying array has 5 elements. The two elements not associated with the length of the slice can be incorporated so the slice can use those elements as well. New slices can also be created to share this same underlying array and use any existing capacity.
- An idiomatic way of creating a slice is to use a slice literal. `slice := []string("Red", "Green")`. The initial length and capacity is based on the number of elements we initialise.
- Declaring an array and a slice are quite similar. The only difference is with the array you put the desired length in between the square brackets. Anyway, here they both are so you don't get confused:
  - array: `array := [3]int(10, 20, 30)`
  - slice: `slice := []int(10, 20, 30)`
- The most common way to create a slice is by making a nil slice `var slice []int`.

### Working with slices
