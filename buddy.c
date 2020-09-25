#include <stdbool.h>
#include "alloc.h"
#include "math.h"

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
        usageTreeLinear[index] = 0b00000010;
    }
}

void can_merge(unsigned int index){
    if(usageTreeLinear[sibling(index)] == 0b00000000){
        usageTreeLinear[parent(index)] = 0b00000000;
        can_merge(parent(index));
    }else{
        usageTreeLinear[index]=0b00000000;
        return;
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
    int min =  1 << SMALLEST_BLOCK;
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
    int max = MEMSIZE;
    int min = 2^SMALLEST_BLOCK;
    int layer =0;
    for(int i = start_ptr; i != 1; i = i/2){
        layer++;
    }
    int layer_start_index = 2^layer;
    usageTreeLinear[layer_start_index] = 0b00000000;
    can_merge(layer_start_index);
    return;
}

unsigned int b_read(unsigned int index) {
    return memory[index];
}

void b_write(unsigned int index, unsigned int value) {
    memory[index] = value;
}
