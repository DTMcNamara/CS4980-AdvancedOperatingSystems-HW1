//
// Created by Dtmcn on 9/17/2020.
//
#include <stdio.h>
#include "alloc.h"

int main(){
    // Testing file, no need to comment.
    b_init();
    printf("Allocating 128 for first...\n");
    unsigned int first = b_allocate(128);
    printf("Allocating 12 for second...\n");
    unsigned int second = b_allocate(12);
    printf("Allocating 64 for third...\n");
    unsigned int third = b_allocate(64);
    printf("Allocating 64 for fourth...\n");
    unsigned int fourth = b_allocate(64);
    printf("Allocating 4 for fifth...\n");
    unsigned int five = b_allocate(4);

    printf("First: %d\n",first);
    printf("Second: %d\n",second);
    printf("Third: %d\n",third);
    printf("Fourth: %d\n",fourth);
    printf("Fifth: %d\n",five);

    printf("writing...\n");
    b_write(first, 20);
    b_write(second, 11);
    unsigned int test1 = b_read(first);
    unsigned int test2 = b_read(second);

    printf("reading...\n");
    printf("First: %d\n",test1);
    printf("Second: %d\n",test2);

    printf("Freeing fifth...\n");
    b_free(five);
    printf("Freeing second...\n");
    b_free(second);
    printf("Fragmentation: %d\n", b_fragmentation());

    printf("Overhead: %d\n", b_overhead());

    return 0;
}
