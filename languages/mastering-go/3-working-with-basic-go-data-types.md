# Working with basic Go data types

## Go arrays

Arrays are created like `a := [4]int{1, 2, 3, 4}`
- Once you define an array in Go, you cant change it's size. If you need to add an lement to an existing array you'll need to create a bigger array.
- When the array is passed to a list, a copy is passed, so any changes are not applied. 

## Go Slices

Slices are implemented using arrays internally, meaning that Go uses an underlying array for each slice
- Slices are passed by reference, so they're quicker and can be mutated by a function.
- They're created like `slice := []int{1, 2, 3, 4}`. They're defined same as arrays, just without the element count.
- You can empty a slice by making it equal to `nil`, as the zero value for a slice is `nil`.
- `slice = append(slice, -5000)` lets you add something to the slice
- `slice[1:3]` will get you a set of continuous elements.
- Slices have capacity (current room that has been allocated for this slice and can be found with `cap()`) and length (length is the same as the length of an array with the same number of elements and is found with `len()`).
- If a slice runs out of room, Go doubles its current length to make room for more elements.
- You can sort slices with `sort.Slice()`

## Go maps

`mapx := make(map[string]int)`

## Go pointers

Use `*` to get the value of a pointer, this is called dereferencing the pointer. `&` gets the memory address of a non-pointer variable.