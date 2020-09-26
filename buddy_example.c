//
// Created by Dtmcn on 9/17/2020.
//
#include <stdio.h>
#include "alloc.h"

int main(){
    b_init();
    unsigned int first = b_allocate(64);
    unsigned int second = b_allocate(128);
    unsigned int third = b_allocate(64);
    unsigned int fourth = b_allocate(64);
    unsigned int five = b_allocate(4);

    printf("%d\n",first);
    /*printf("%d\n",second);
    printf("%d\n",third);
    printf("%d\n",fourth);
    printf("%d\n",five);

    printf("writing...\n");
    b_write(first, 20);
    b_write(second, 11);
    unsigned int test1 = b_read(first);
    unsigned int test2 = b_read(second);

    printf("reading...\n");
    printf("%d\n",test1);
    printf("%d\n",test2);*/

    printf("Hey dad i made it");
    fflush(stdout);
    b_free(first);

    return 0;
}
