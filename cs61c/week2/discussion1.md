# C Basics

## 2

1: Returns sum of the first N elements in an array.
2: Returns -1 times the zerioes in first n elements.
3: Does nothing...

## 3

1:

```c
void swap(int *x, int *y) {
  int temporary = *x;
  *x = *y;
  *y = temp;
}
```

2:

```c
void increment_something(int *x) {
  (*x)++;
}
```

3:

```c
int number_of_bytes_in_string(char* string) {
  int count = 0;
  while(*str++) {
    count++;
  }
  return count;
}
```
