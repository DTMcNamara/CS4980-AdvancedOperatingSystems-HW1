//
// Created by Dtmcn on 9/27/2020.
//

#include <stdio.h>
#include "alloc.h"
int main(){
    p_init();

    printf("Allocating...\n");
    unsigned int first = p_allocate(16);
    unsigned int second = p_allocate(128);
    unsigned int third = p_allocate(290);
    unsigned int fourth = p_allocate(16);
    unsigned int fifth = p_allocate(16);

    printf("Printing...\n"
           "First: %d\n"
           "Second: %d\n"
           "Third: %d\n"
           "Fourth: %d\n"
           "Fifth: %d\n",
           first,
           second,
           third,
           fourth,
           fifth);

    printf("Writing...\n");
    p_write(first, 26);
    p_write(second, 99);
    p_write(third, 3);
    p_write(fourth, 420);
    p_write(fifth, 69);

    printf("Reading...\n"
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

    printf("Freeing First...\n");
    p_free(first);
    printf("Re-Allocating First...");
    first = p_allocate(24);
    printf("Printing First: %d\n", first);

    printf("Freeing Second...\n");
    p_free(second);
    printf("Re-Allocating Second...");
    second = p_allocate(145);
    printf("Printing Second: %d\n", second);

    return 0;
}
