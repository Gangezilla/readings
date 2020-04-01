#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void printArray(int array[], int size) {
  int i;
  printf("Array is: [");
  for (i = 0; i < size; i++) {
    if (i == size - 1) {
      printf("%d", array[i]);
    } else {
      printf("%d, ", array[i]);

    }
  }
  printf("]\n");
}
