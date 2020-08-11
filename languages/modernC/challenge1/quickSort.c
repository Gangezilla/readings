/*
  Quick Sort is a "divide and conquer" algo.
  It works by picking an element as a pivot, and partitioning the given array around said pivot.
  This particular implementation:
  - takes the last element as a pivot
  - places the pivot element at its correct position in a sorted array
  - places all smaller elements to left of pivot
  - places all greater elements to right of pivot.

  clang ./quickSort.c ./utils.c -o ./quickSort
*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partition (int array[], int startIndex, int endIndex) {
  int pivot = array[endIndex];
  int i = (startIndex - 1);

  for (int j = startIndex; j <= endIndex; j++) {
    if(array[j] < pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[endIndex]);
  return (i + 1);
}

void quickSort(int array[], int startIndex, int endIndex) {
  if (startIndex < endIndex) {
    int partitioningIndex = partition(array, startIndex, endIndex);

    quickSort(array, startIndex, partitioningIndex - 1);
    quickSort(array, partitioningIndex + 1, endIndex);
  }
}

int main() {
  int array[] = {1000, 2, 3, 7, 50};
  int arraySize = sizeof(array) / sizeof(array[0]);
  quickSort(array, 0, arraySize - 1);
  printf("Sorted ");
  printArray(array, arraySize);
  return 0;
}
