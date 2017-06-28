#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//A helper function to help get the target bit
uint16_t get_bit(uint16_t reg, uint16_t n){
	reg = reg>>n;
	return reg&1;
}


/*On each call to lfsr_calculate, you will shift the contents of the register 1 bit to the right.
This shift is neither a logical shift or an arithmetic shift. On the left side, you will shift in a single bit equal to the Exclusive Or (XOR) of the bits originally in position 1, 3, 4, and 6.
The curved head-light shaped object is an XOR, which takes two inputs (a, b) and outputs a^b.
*/


void lfsr_calculate(uint16_t *reg) {
	//get the candidate bit
	uint16_t pos1 = get_bit(*reg,0);
	uint16_t pos3 = get_bit(*reg,2);
	uint16_t pos4 = get_bit(*reg,3);
	uint16_t pos6 = get_bit(*reg,5);
	
	uint16_t candidate = ((pos1^pos3)^pos4)^pos6;
	candidate = candidate&1;
	*reg = (*reg)>>1;
	candidate = candidate << 15;
	*reg += candidate;
}

/* Ignore below. */
int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
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
