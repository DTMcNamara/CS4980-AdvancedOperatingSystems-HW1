//
// Created by Dtmcn on 9/27/2020.
//
#include <stdbool.h>
#include "alloc.h"
#define PAGES (MEMSIZE/PAGESIZE)

unsigned int fragmentation;
unsigned int memory[MEM_SIZE];
bool usage[PAGES];

void p_init(){
    for (unsigned int i = 0; i < MEMSIZE; i++) {
        usage[i] = false;
    }
}

unsigned int p_allocate(unsigned int size){
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
    for(int i =0;i<pages;i++){
        if(usage[i]==false){
            for(int j = 0; j =< counter; j++){
                if(usage[i+j]!=false){
                    check = false;
                }
                if(check == true){
                    for(int k = 0; k =< counter; k++){
                        memory[(PAGESIZE * (k+1))-1] = '\f';
                    }
                    memory[(PAGESIZE * (counter))-1] = '\0';
                    fragmentation += ((PAGESIZE * i)-size) ;
                    memory[(PAGESIZE * i)+size] = NULL_PTR;
                    return (PAGESIZE * i);
                }
            }
        }
    }
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