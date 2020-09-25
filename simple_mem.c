#include <stdbool.h>
#include "alloc.h"

/**
 * The memory array represents the actual memory which we will be managing.
 * The usage array is used to keep track of what memory locations are used. 
 * Initially, the entire memory is available (i.e., usage[i]=false for all 0 <= i < MEMORY_SIZE)
 * Then, element i in the memory is used if usage[i] is true.
 */
unsigned int memory[MEMSIZE];
bool usage[MEMSIZE];

void s_init() {
    // initialize the memory so that it is all available to used
    for (unsigned int i = 0; i < MEMSIZE; i++) {
        usage[i] = false;
    }
}

/**
 * Searches to find a contiguous piece of memory of location memsize and returns a pointer to it
 * (i.e, the index in the array from where there are  memsize elements not used)
 */
extern unsigned int s_allocate(unsigned int mem_size) {
    for (unsigned int start = 0; start < MEMSIZE; start++) {
        bool check = true;
        for (unsigned int i = 0; i < mem_size; i++) {
            if (usage[start + i] == true) {
                check = false;
            }
        }

        if (check) {
            for (unsigned int i = 0; i < mem_size; i++) usage[start + i] = true;
            return start;
        }
    }

    return NULL_PTR;
}

void s_free(unsigned int start_ptr) {
    if( start_ptr != NULL_PTR){
        //...
    }
}

unsigned int s_read(unsigned int base, unsigned int offset) {
    return memory[base + offset];
}

void s_write(unsigned int base, unsigned int offset, unsigned int value) {
    memory[base + offset] = value;
}

/**
 * The function s_overhead returns the number of bytes that are used
 *      to keep side information (e.g., what pages are allocated)
 */
unsigned int s_overhead(){

}

/**
 * Similarly, s_fragmentation returns the number of bytes lost due to internal fragmentation.
 *
 */
unsigned int s_fragmentation(){

}
