#include <stdio.h>
#include "alloc.h"


#define OFFSET_VALUE    0
#define OFFSET_PREV     1
#define OFFSET_NEXT     2


/**
 * Traverse our doubly linked list
 * 
 * Starting from the first element that is given by first_ptr, follow the sequence of next pointers
 * 
 */
void traverse(unsigned int first_ptr) { 
    unsigned int iter = first_ptr;
    while (iter != NULL_PTR) {
        printf("%d ", s_read(iter, OFFSET_VALUE));
        iter = s_read(iter, OFFSET_NEXT);
    }
    printf("\n");
}

int main() {
    s_init();


    // allocate 3 nodes and manually setup the prev and next pointers
    unsigned int n0 = s_allocate(3);
    s_write(n0, OFFSET_VALUE, 15);
    s_write(n0, OFFSET_PREV, NULL_PTR);
    printf("n0 %d\n", n0);


    unsigned int n1 = s_allocate(3);
    unsigned int n2 = s_allocate(3);

    s_write(n1, OFFSET_VALUE, 13);
    s_write(n1, OFFSET_PREV, n0);
    s_write(n1, OFFSET_NEXT, n2);
    s_write(n0, OFFSET_NEXT, n1);

    s_write(n2, OFFSET_VALUE, 7);
    s_write(n2, OFFSET_NEXT, NULL_PTR);
    s_write(n2, OFFSET_PREV, n1);
    printf("n1 %d\n", n1);

    // traverse the list we constructed
    traverse(n0);


    return 0;
}