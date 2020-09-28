/*************************************************
 *
 * Name: Dylan McNamara and Addison Armstrong
 * Class Name: buddy.c
 * Class Description: This class is a C representation of a buddy system.
 *  We use the simple binary tree, flatten it into an array, and use it
 *  counterparts to create memory storage for the system. The array is
 *  the Breadth First of the Binary Tree that is wished to be created.
 *  Root is the largest memory capacity set in MakeFile, then splits down
 *  the tree until the lowest split capacity in MakeFile.
 *
 *  We use 3 different binary labels for each node within the tree.
 *  0b00000010 = split, not used
 *  0b00000001 = used
 *  0b00000000 = not used or split
 *  Split is when the node is currently split between it's own children.
 *  Used is when the node is currently holding memory.
 *
 *  Go to buddy_example.c to visualize what our program creates.
 *************************************************/




// Including all the other needed files
#include <stdio.h>
#include "alloc.h"
#include <stdlib.h>

/**
 * Creating the flattened tree described earlier
 */
unsigned char usageTreeLinear[NUM_BLOCKS];

/**
 * Creating the memory array
 */
unsigned int memory[MEMSIZE];

/**
 * Creating the fragmentation global variable
 */
unsigned int fragmentation = 0;

/**
 * Method to get the parent of the passed index
 * @param index
 * @return
 */
unsigned int parent(unsigned int index){
    return (index/2);
}

/**
 * Method to get the left child of the passed index
 * @param index
 * @return
 */
unsigned int left_child(unsigned int index){
    return (index * 2);
}

/**
 * Method to get the right child of the passed index
 * @param index
 * @return
 */
unsigned int right_child(unsigned int index){
    return ((index * 2) + 1);
}

/**
 * Method to get the other sibling of the passed index
 * @param index
 * @return
 */
unsigned int sibling(unsigned int index){
    if(index % 2 == 0){
        return (index + 1);
    }else{
        return (index - 1);
    }
}

/**
 * Recursive Method to split the passed index. Will recursively call until
 *  all parents are split that are in the linear regression.
 * @param index
 */
void split_parent(unsigned int index){
    if(usageTreeLinear[parent(index)] != 0b00000010){
        split_parent(parent(index));
        usageTreeLinear[index] = 0b00000010;
    }
}

/**
 * Recursive Method to merge the passed index. Will recursively call until
 *  all free nodes are merged into its parent, or un-split.
 * @param index
 */
void can_merge(unsigned int index){
    if(usageTreeLinear[sibling(index)] == 0b00000000){
        usageTreeLinear[parent(index)] = 0b00000000;
        can_merge(parent(index));
    }else{
        usageTreeLinear[index]=0b00000000;
        return;
    }
}

/**
 * Recursive Method to fill the passed index with the passed opcode. Will
 *  call recursively until all children are filled with the opcode from the
 *  index to down the tree.
 * @param index
 * @param opcode
 */
void fill_children(unsigned int index, unsigned char opcode) {
    if (index < NUM_BLOCKS) {
        usageTreeLinear[left_child(index)] = opcode;
        usageTreeLinear[right_child(index)] = opcode;
        fill_children(left_child(index), opcode);
        fill_children(right_child(index), opcode);
    }
    return;
}

/**
 * Method to help the fragmentation find the correct place of fragmentation
 * @return
 */
unsigned int b_fragmentation_helper(unsigned int index){
    unsigned int test = memory[index], counter = 1;
    while(test != NULL_PTR){
        index++;
        test = memory[index];
        counter++;
    }
    return counter;

}

/**
 * Method to fill the every node, but the root, with free, or not split not used.
 *  The root will be set as split to signify that it is the root.
 */
void b_init() {
    for(int i = 1; i < NUM_BLOCKS*2; i++){
        usageTreeLinear[i] = 0b00000000;
    }
    usageTreeLinear[0] = 0b00000010;
}
/**
 * Method will allocate the passed in memory size into the binary tree. Properly placing
 *  the space needed within the tree wherever it is available.
 * @param mem_size
 * @return
 */
extern unsigned int b_allocate(unsigned int mem_size) {
    int max = MEMSIZE;
    int min =  1 << SMALLEST_BLOCK;
    int mem_size_temp = mem_size;
    // if mem_size is less than min then too bad, its 16
    if(mem_size < min){
        mem_size = min;
    }

    // 2^layer = start index of possible blocks && the number of blocks of that size
    int layer = 0;
    int block_size = 0;

    // Finds the needed layer of the tree
    if(MEMSIZE < mem_size){
        return NULL_PTR;
    }
    for(int i = max; (mem_size < i/2) && (min < i/2); i = i/2){
        layer++;
        block_size = i;
    }

    // Finding the layer that the allocate needs to happen at
    int layer_start_index = 1 << (layer-1);
    layer += 1;
    int layer_end_index = 1 << layer;

    // For loop to find the correct place to allocate.
    for (int i = layer_start_index; i < layer_end_index; i++){

        // open, un-split block of needed size
        if(usageTreeLinear[i] == 0b00000000 && usageTreeLinear[parent(i)] != 0b00000001){
            // First, split the parent, then set it to used.
            split_parent(i);
            usageTreeLinear[i] = 0b00000001;
            fill_children(i, 0b00000001);

            // Grabbing the zerod start and the block range at the current block
            int zerod_start = i- layer_start_index;
            int block_range = MEMSIZE / (1 << layer);

            // Commented out Print Statement for the tree.
            /*for(int j = 1; j < NUM_BLOCKS*2; j++){
                printf("index %d: %d\n", j, usageTreeLinear[j]);
            }
            printf("mem_size: %d\nMEMSIZE: %d\nlayer: %d\nblock_range: %d\ni: %d\nlayer_start_index: %d\n",
                   mem_size,MEMSIZE, layer, block_range,i,layer_start_index);
            */

            // if the mem_size is not the same as the block_range, then add fragmentation
            if(mem_size_temp != block_range){
                fragmentation += abs(((1 << (layer-2))-mem_size_temp));
            }

            // Writing a null character to the end of the block range so that fragmentation_helper can work.
            b_write((block_range * zerod_start) + mem_size_temp -1,NULL_PTR);
            printf("writing null: %d\n", (block_range * zerod_start) + mem_size_temp -1);

            // Return the place where the allocation is
            return block_range * zerod_start;
        }
    }


}

/**
 * Method to free up the tree wherever it is needed
 * @param index
 */
void b_free(unsigned int index){
    // Finding the correct layer where the index lays
    int layer = 0;
    if(index == 0){
        layer = 0;
        index = 1;
    }else {
        for (unsigned int i = index; i < MEMSIZE; i = i * 2) {
            layer++;
        }
    }
    // Creating the layer_start_index from layer
    int layer_start_index = 1 << layer;

    // fixing tree
    fill_children(index,0b00000000);
    usageTreeLinear[layer_start_index] = 0b00000000;
    can_merge(layer_start_index);

    // checking for fragmentation then taking away from fragmentation
    unsigned int counter = b_fragmentation_helper(index);
    fragmentation -= (counter);


    // Commented out printing of the tree
    /*
     for(int i = 1; i < NUM_BLOCKS*2; i++){
        printf("index %d: %d\n", i, usageTreeLinear[i]);
    }*/
}
/**
 * Method to read the stored value within the memory at index
 * @param index
 * @return
 */
unsigned int b_read(unsigned int index) {
    return memory[index];
}

/**
 * Method to write the value to the memory at index
 * @param index
 * @param value
 */
void b_write(unsigned int index, unsigned int value) {
    memory[index] = value;
}

/**
 * Returns the given overhead from program
 * @return
 */
unsigned int b_overhead(){
    return sizeof(usageTreeLinear);
}

/**
 * Method to return the fragmentation created by the system
 * @return
 */
unsigned int b_fragmentation(){
    return fragmentation;
}