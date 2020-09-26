#include <stdio.h>
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
    if(usageTreeLinear[parent(index)] != 0b00000010){
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

void fill_children(unsigned int index, unsigned char opcode) {
    if (index < NUM_BLOCKS) {
        usageTreeLinear[left_child(index)] = opcode;
        usageTreeLinear[right_child(index)] = opcode;
        fill_children(left_child(index), opcode);
        fill_children(right_child(index), opcode);
    }
    return;
}

void b_init() {
    for(int i = 1; i < NUM_BLOCKS*2; i++){
        usageTreeLinear[i] = 0b00000000;
    }
    usageTreeLinear[0] = 0b00000010;
}

extern unsigned int b_allocate(unsigned int mem_size) {
    int max = MEMSIZE;
    int min =  1 << SMALLEST_BLOCK;
    // if mem_size is less than min then too bad, its 16
    if(mem_size < min){
        mem_size = min;
    }

    //2^layer = start index of possible blocks && the number of blocks of that size
    int layer = 0;
    int block_size = 0;
    //Finds the needed layer of the tree
    if(MEMSIZE < mem_size){
        return NULL_PTR;
    }
    for(int i = max; (mem_size < i/2) && (min < i/2); i = i/2){
        layer++;
        block_size = i;
    }
    int layer_start_index = 1 << layer;
    layer += 1;
    int layer_end_index = 1 << layer;
    for (int i = layer_start_index; i < layer_end_index; i++){
        //open, un-split block of needed size
        if(usageTreeLinear[i] == 0b00000000 && usageTreeLinear[parent(i)] != 0b00000001){
            split_parent(i);
            usageTreeLinear[i] = 0b00000001;
            //printing usagetree at i
            fill_children(i, 0b00000001);

            for(int i = 1; i < NUM_BLOCKS*2; i++){
                printf("index %d: %d\n", i, usageTreeLinear[i]);
            }
            int zerod_start = i- layer_start_index;
            int block_range = MEMSIZE / (1 << layer);
            printf("MEMSIZE: %d\nlayer: %d\nblock_range: %d\ni: %d\nlayer_start_index: %d\n",
                   MEMSIZE, layer, block_range,i,layer_start_index);

            return block_range * zerod_start;
        }
    }
}


void b_free(unsigned int index){
    printf("hey mom i made it");
    fflush(stdout);
    int max = MEMSIZE;
    int min = 1 << SMALLEST_BLOCK;
    int layer =0;
    if(index == 0){
        layer = 0;
        index = 1;
    }else{
        for(unsigned int i = index; i < MEMSIZE; i = i*2){
            printf("%d\n", i);
            layer++;
        }
    }
    int layer_start_index = 1 << layer;
    printf("%d\n",layer);
    fill_children(index,0b00000000);
    usageTreeLinear[layer_start_index] = 0b00000000;
    can_merge(layer_start_index);
    printf("**");fflush(stdout);
    for(int i = 1; i < NUM_BLOCKS*2; i++){
        printf("index %d: %d\n", i, usageTreeLinear[i]);
    }
}

unsigned int b_read(unsigned int index) {
    return memory[index];
}

void b_write(unsigned int index, unsigned int value) {
    memory[index] = value;
}