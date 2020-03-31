#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned get_bit(unsigned integer, unsigned bit) {
  int mask = 1 << bit;
  int maskedInteger = integer & mask;
  return maskedInteger >> bit;
}

void lfsr_calculate(uint16_t *reg) {
  int bit16 = get_bit(*reg, 0);
  int bit14 = get_bit(*reg, 2);
  int bit13 = get_bit(*reg, 3);
  int bit15 = get_bit(*reg, 5);
  int bit = (((bit14 ^ bit16) ^ bit13) ^ bit15);
  // we calculate what the value is that we need to set.
  *reg = *reg >> 1;
  // shift the numbers over, leaving a blank 0 in the left-most bit.
  int shift = bit << 15;
  // move our single bit all the way to the left-most bit
  *reg = shift | (*reg & ~(1 << 15));
}

int main() {
  int8_t *numbers = (int8_t *)malloc(sizeof(int8_t) * 65535);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 65535);
  uint16_t reg = 0x1;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 24) {
      printf("My number is: %u\n", reg);
    } else if (count == 24) {
      printf(" ... etc etc ... \n");
    }
    for (i = 0; i < 32; i++)
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);

  if (count == 65535) {
    printf("Congratulations! It works!\n");
  } else {
    printf("Did I miss something?\n");
  }

  free(numbers);

  return 0;
}