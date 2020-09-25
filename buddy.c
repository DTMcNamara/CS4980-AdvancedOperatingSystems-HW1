#include <stdbool.h>
#include "alloc.h"

unsigned char usageTreeLinear[NUM_BLOCKS];

unsigned int memory[MEMSIZE];

unsigned int parent(unsigned int index){
    return (index/2);
}

unsigned int left_child(unsigned int index){
    return (index * 2);
}

unsigned int right_child(unsigned int index){
    return ((index * 2) + 1);
}

unsigned int sibling(unsigned int index){
    if(index % 2 == 0){
        return (index + 1);
    }else{
        return (index - 1);
    }
}

/*
 *  0b00000010 = split, not used
 *  0b00000001 = used, not split
 *  0b00000000 = not used or split
 */

void split_parent(unsigned int index){
    if(usageTreeLinear[parent(index)] == 0b00000010){
        return;
    }else{
        split_parent(parent(index));
    }
}

void b_init() {
    for(int i = 1; i < NUM_BLOCKS*2; i++){
        usageTreeLinear[i] = 0b00000000;
    }
    usageTreeLinear[0] = 0b00000011;
}

extern unsigned int b_allocate(unsigned int mem_size) {
    int max = MEMSIZE;
    int min = 2^SMALLEST_BLOCK;
    //2^layer = start index of possible blocks && the number of blocks of that size
    int layer = 0;
    int block_size = 0;
    //Finds the needed layer of the tree
    if(MEMSIZE < mem_size){
        return NULL_PTR;
    }
    for(int i = max; (min && mem_size) < i/2; i = i/2){
        layer++;
        block_size = i;
    }
    int layer_start_index = 2^layer;
    int layer_end_index = 2^(layer+1);
    for (int i = layer_start_index; i < layer_end_index; i++){
        //open, un-split block of needed size
        if(usageTreeLinear[i] == 0b00000000){
            split_parent(i);
            return memory[block_size * (layer_end_index - layer_start_index)];
        }
    }
}


void b_free(unsigned int start_ptr) {

}

unsigned int b_read(unsigned int base, unsigned int offset) {

}

void b_write(unsigned int base, unsigned int offset, unsigned int value) {

}
