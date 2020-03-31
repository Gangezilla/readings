/*
  So the gist of merge sort is that you take a list of unsorted elements and break it down into several sub-lists.
  Each sub-list will eventaully consist of a single element that you can then merge together into a sorted list.
  - Divide the unsorted list into N sublists, each containing 1 element.
  - Take adjacent pairs of two singleton lists and merge them to form a list of 2 elements. N will now convert into N/2 lists of size 2
  - Repeat until you've got a single sorted list

  clang ./mergeSort.c ./utils.c -o ./mergeSort
*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void merge(int array[], int leftIndex, int middle, int rightIndex) {
  int i, j, k;
  int leftLength = middle - leftIndex + 1;
  int rightLength = rightIndex - middle;
  int leftHalf[leftLength], rightHalf[rightLength];

  for (i = 0; i < leftLength; i++) {
    leftHalf[i] = array[leftIndex + i];
  }
  for(j = 0; j < rightLength; j++) {
    rightHalf[j] = array[middle + 1 + j];
  }

  // above here, we're copying the data from our arrays into our temporary arrays
  printf("leftHalf:\t");
  printArray(leftHalf, leftLength);
  printf("rightHalf:\t");
  printArray(rightHalf, rightLength);

  i = 0; // initial index of left subarray
  j = 0; // initial index of right subarray
  k = leftIndex; // initial index of merged subarray

  // merging temp arrays back into array[l..r]
  while (i < leftLength && j < rightLength) {
    if (leftHalf[i] <= rightHalf[j]) {
      array[k] = leftHalf[i];
      i++;
    } else {
      array[k] = rightHalf[j];
      j++;
    }
    k++;
  }

  // copy remaining elements of leftHalf and rightHalf, if any
  while (i < leftLength) {
    array[k] = leftHalf[i];
    i++;
    k++;
  }

  while (j < rightLength) {
    array[k] = rightHalf[j];
    j++;
    k++;
  }
}

// l is the left index, r is the right index of the subarray to be sorted.
void mergeSort(int array[], int leftIndex, int rightIndex) {
  if (leftIndex < rightIndex) {
    int middle = leftIndex + (rightIndex - leftIndex) / 2;

    mergeSort(array, leftIndex, middle);
    mergeSort(array, middle + 1, rightIndex);

    merge(array, leftIndex, middle, rightIndex);
  }
}

int main() {
  int array[] = {1000, 2, 3, 7, 50};
  int arraySize = sizeof(array) / sizeof(array[0]);
  printArray(array, arraySize);

  mergeSort(array, 0, arraySize - 1);
  printf("Sorted ");
  printArray(array, arraySize);
  // sizeof gives us the size of a thing in bytes.
  // so we determine the array size by figuring out how large the array is in bytes
  // and then divide it by the size of any element in the array in bytes.
  return 0;
}
