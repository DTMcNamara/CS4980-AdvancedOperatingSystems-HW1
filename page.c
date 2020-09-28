/*************************************************
 *
 * Name: Dylan McNamara and Addison Armstrong
 * Class Name: page.c
 * Class Description: This class is a C representation of a page system.
 *  We use a simple array of pages to store and allocate memory for the
 *  system.
 *************************************************/


// Including all the other needed files
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "alloc.h"

// Creating and initializing the global variables
unsigned int pages = NUMPAGES;
unsigned int fragmentation;
unsigned int memory[MEMSIZE];
bool usage[NUMPAGES];

/**
 *  Creating and clearing the
 */
void p_init(){
    for (unsigned int i = 0; i < MEMSIZE; i++) {
        usage[i] = false;
    }
}

/**
 * Method to correctly allocate the memory needed for the given size
 * @param size
 * @return
 */
unsigned int p_allocate(unsigned int size){\
    // If the memsize is less than the given size, return NULL_PTR because it cannot be allocated
    if(MEMSIZE < size){
        return NULL_PTR;
    }

    // Initializing all the needed variables for testing
    bool check = true;
    int t = (size-PAGESIZE);
    int counter = 1;
    // if the given size is bigger than the PAGESIZE, then find how many it will need to allocate correctly
    while(0 < t){
        counter++;
        t -= PAGESIZE;
    }

    // For loop to allocate on the next empty page
    for(int i =1;i<pages;i++){
        // If the page is currently not in-use, then allocate it
        if(usage[i-1]==false){
            // For loop for how many pages are needed to be allocated for the given size
            for(int j = 0; j <= counter; j++){
                // If the current page is used, then set the check to false
                if(usage[i+j-1]!=false){
                    check = false;
                }
                // If check is true, then...
                if(check == true){
                    // Loop through all the pages needed, connecting them with the pointer variable \f
                    //  and setting them to be true within the usage array
                    for(int k = 0; k < counter; k++){
                        memory[(PAGESIZE * (k+1))-1] = '\f';
                        usage[i+k-1] = true;
                    }

                    // Set the last spot in the page to be NULL to signify the end of the allocation
                    memory[(PAGESIZE * (counter))-1] = '\0';
                    memory[(PAGESIZE * i)+size] = NULL_PTR;

                    // Add the needed fragmentation created by this allocation
                    fragmentation += ((PAGESIZE * i)-size);

                    // Return where the allocation began
                    return (PAGESIZE * (i-1));
                }
            }
        }
    }
    // Else, return the NULL_PTR to signify it cannot be allocated
    return NULL_PTR;
}

/**
 * Method that frees the allocation from where the start_ptr is in usage and memory
 * @param start_ptr
 */
void p_free(unsigned int start_ptr){
    // If the memory at the start_ptr ends with the ending character,\f, then free the
    //  current page, then recursively call the next page
    if(memory[start_ptr+PAGESIZE-1] == '\f'){
        usage[start_ptr/PAGESIZE] = false;
        p_free(start_ptr+PAGESIZE);
    // Else, free the current page and erase the \f pointer. Take the allocation away
    //  from fragmentation too
    }else{
        unsigned int test = start_ptr;
        unsigned int test_mem = memory[test];
        while( test_mem != '\0'){
            test++;
            test_mem = memory[test];
        }
        fragmentation -= (PAGESIZE - test);
        usage[start_ptr/PAGESIZE] = false;
    }
}

/**
 * Method that reads the value from the given index within the memory
 * @param index
 * @return
 */
unsigned int p_read(unsigned int index){
    return memory[index];
}

/**
 * Method that sets the given value at the given index within the memory
 * @param index
 * @param value
 */
void p_write(unsigned int index, unsigned int value){
    memory[index] = value;
}

/**
 * Method that returns the size of the usage array for the overhead
 * @return
 */
unsigned int p_overhead(){
    return sizeof(usage);
}

/**
 * Method that returns the global fragmentation variable
 * @return
 */
unsigned int p_fragmentation(){
    return fragmentation;
}