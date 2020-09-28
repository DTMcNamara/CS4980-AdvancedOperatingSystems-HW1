//
// Created by Dtmcn on 9/27/2020.
//

#include <stdio.h>
#include "alloc.h"
int main(){
    p_init();

    printf("Allocating...\n");
    unsigned int first = p_allocate(16);
    unsigned int second = p_allocate(256);
    unsigned int third = p_allocate(128);
    unsigned int fourth = p_allocate(16);
    unsigned int fifth = p_allocate(16);

    printf("printing...\n");
    printf("%d\n", first);
    printf("%d\n", second);
    printf("%d\n", third);
    printf("%d\n", fourth);
    printf("%d\n", fifth);

    printf("Writing...\n");
    p_write(first, 26);
    p_write(second, 99);
    p_write(third, 3);
    p_write(fourth, 420);
    p_write(fifth, 69);

    printf("Reading...\n "
           "First: %d\n"
           "Second: %d\n"
           "Third: %d\n"
           "Fourth: %d\n"
           "Fifth: %d\n",
           p_read(first),
           p_read(second),
           p_read(third),
           p_read(fourth),
           p_read(fifth));

    printf("Fragmentation: %d\n", p_fragmentation());
    printf("Overhead: %d\n", p_overhead());

    return 0;
}
