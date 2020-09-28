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

    printf("NUMPAGES: %d\nMEMSIZE: %d\nPAGESIZE: %d\n",NUMPAGES, MEMSIZE, PAGESIZE);
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


    bool check = true;
    int t = (size-PAGESIZE);
    int counter = 1;
    while(0 < t){
        counter++;
        t -= PAGESIZE;
    }
    for(int i =1;i<pages;i++){
        if(usage[i-1]==false){
            for(int j = 0; j <= counter; j++){
                if(usage[i+j-1]!=false){
                    check = false;
                }
                if(check == true){
                    for(int k = 0; k <= counter; k++){
                        memory[(PAGESIZE * (k+1))-1] = '\f';
                    }
                    memory[(PAGESIZE * (counter))-1] = '\0';
                    fragmentation += ((PAGESIZE * i)-size) ;
                    memory[(PAGESIZE * i)+size] = NULL_PTR;
                    usage[i-1] = true;
                    return (PAGESIZE * i);
                }
            }
        }
    }
    printf("Fragmentation within program: %d\n ", fragmentation);
    return NULL_PTR;
}

void p_free(unsigned int start_ptr){
    if(memory[start_ptr+PAGESIZE-1] == '\f'){
        usage[start_ptr/PAGESIZE] = false;
        p_free(start_ptr+PAGESIZE);
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

unsigned int p_read(unsigned int index){
    return memory[index];
}

void p_write(unsigned int index, unsigned int value){
    memory[index] = value;
}

unsigned int p_overhead(){
    return sizeof(usage);
}

unsigned int p_fragmentation(){
    return fragmentation;
}