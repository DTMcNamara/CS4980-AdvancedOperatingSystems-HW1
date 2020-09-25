//
// Created by Dtmcn on 9/17/2020.
//
#include "alloc.h"
#include <stdio.h>

int main(){
    b_init();
    unsigned int first = b_allocate(64);
    unsigned int second = b_allocate(64);
    b_write(first, 20);
    //b_write(second, 11);
    unsigned int test1 = b_read(first);
    unsigned int test2 = b_read(second);
    printf("%d\n",first);
    printf("%d\n",second);
    return 0;
}
