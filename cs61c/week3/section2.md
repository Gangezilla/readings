# C Memory Management

1. arg - stack, str - stack, arr - static, \*str - heap, val - code, C - code
2. Memory leak if extra_large is true. This is because we've already set some memory on ptr on the first line, and then we're reassigning ptr to a new block of memory without freeing the first chunk. The first chunk therefore just sits there taking up space. If you wanted to rewrite this, you'd probably do something like this I think

```c
int* ptr;
if (extra_large) {
  ptr = malloc(10 * sizeof(int))
} else {
  ptr = malloc(4 * sizeof(int))
}
return ptr;
```

3.

```c
free_ll(struct ss_node** list) {
  if (*list) {
    free_ll(&((*list)->next));
    free(*list);
  }

  *list = NULL;
}
```

```c
prepend(struct ll_node** list, int value) {
  struct ll_node* item = (struct ll_node*) malloc(sizeof(struct ll_node));
  item->value = value;
  item->next = *list;
  *list = item;

}
```

# 2 MIPS Intro

1a) Getting a pointer to the 3rd array member. Adding the 3rd array member and the first array member together, and then saving this sum to the 3rd array member.
