#include <stdbool.h>
#include "alloc.h"
#include "math.h"

#define BLOCK_SIZES (MEMSIZE)/2^(SMALLEST_BLOCK)
#define NUM_LISTS N-SMALLEST_BLOCK+1

bool usage[NUM_LISTS][BLOCK_SIZES];
int mem_list[NUM_LISTS][BLOCK_SIZES];
unsigned int memory[MEMSIZE];

void b_init() {
    for (int i = 0; i < NUM_LISTS; i++) {
        for (int j = 0; j < BLOCK_SIZES; j++) {
            usage[i][j] = false;
            mem_list[i][j] = MEMSIZE+1;
        }
    }
    //set up first block of full size(MEMSIZE)
    mem_list[0][0]=0;
}

unsigned int b_allocate(unsigned int mem_size) {

    //if mem doesnt fit, return null_ptr
    if (MEMSIZE < mem_size) { return NULL_PTR; }
    else {
        //check each list
        for (int i = 0; i < NUM_LISTS) {
            //how big is the current block?
            int current_block = MEMSIZE / (2 ^ i);
            //check each block in list
            for (int j = 0; j < BLOCK_SIZES) {
                //check if all mem spanned in a row
                if (MEMSIZE / (current_block * (j)) == 1) {
                    break;
                }

            }
        }

    }
}

void block_split(int mem_list, int level, int current_size) {

}

void b_free(unsigned int start_ptr) {

}

unsigned int b_read(unsigned int base, unsigned int offset) {

}

void b_write(unsigned int base, unsigned int offset, unsigned int value) {

}
