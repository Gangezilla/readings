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

- You can access an index of a slice as you'd expect: `slice[1] = 25`.
- There's also a bunch of stuff in here about reusing slices but it sounds hella dangerous...

### Growing Slices

One of the advantages of using a slice over an array is that you can grow the capacity of your slice as needed, which is done using `append`. `append` will always increase the length but not necessarily the capacity. If you call `append` and there's capacity, then the array will have the new element added into it. If there's no capacity, a new array is made and all of the old values get copied into it. Under the hood, append always doubles the existing capacity when the number of elements is under 1000, and when it's over 1000 it grows by 25%.

### Iterating over slices

You can iterate over slices just like you would an array:
`for index, value := range slice {}`.
BTW, it's important to know that the `value` given to you by the range function is a copy, so you won't be able to mutate that if you were intending to.

You can also use a regular for loop like this: `for index := 2; index < len(slice); index++ {}`

### Passing slices between functions

This is easy because a slice is small, so it's cheap to copy and pass between functions. A slice only requires 24 bytes of memory for the pointer, length and capacity.

## Map internals and fundamentals

A map is a data structure that provides you with an unordered collection of key/value pairs. The strength of a map is its ability to retrieve data quickly based on the key.

### Internals

Maps are collections, and you can iterate over them just like with arrays and slices. It's important to note that thewy're unordered collections, so don't rely on their order. This is because a map is implemented using a hash table. The map's hash table contains a collection of buckets. When you're storing, removing or looking up something, it all starts with selecting a bucket. You do this by passing the key to the map's hash function so that Go can generate an index that's evenly distributed. We want this because the better the distribution, the quicker we can find a key/value pair.

### Using a map

- A map is created like so: `dict := make(map[string]int)` or you can make one with 2 key value pairs like so: `dict := map[string]string("red": "red", "orange": "orange")`
- It's pretty easy to assign a key/value pair to a map too: `colors["red"] = "#FF0000"`
- If you need to check if a key exists on a map, you can go like `value, exists := colors["Blue"]` and then `if exists ...`. You could also do like `value := colors["Blue"]` and then check `if value != ''`. Go will always return a value from a map, even if they key doesn't exist. Err, so I guess make sure you never want a value to be an empty string...
- You can also iterate over a map similarly to slice/array, `for key, value := range colors {}`. You wouldn't get the index/value back but instead you get the key and the value.
- You can delete a key by going `delete(dict, "Coral")`
- If you pass a map between two functions, it's passed by value not reference. So functions can mutate a map.
