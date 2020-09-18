#ifndef ALLOC_H
#define ALLOC_H

#include <limits.h>
#define NULL_PTR    UINT_MAX

void s_init();
unsigned int s_allocate(unsigned int size);
void s_free(unsigned int start_ptr);
unsigned int s_read(unsigned int base, unsigned int offset);
void s_write(unsigned int base, unsigned int offset, unsigned int value);

unsigned int s_overhead();
unsigned int s_fragmentation();

void b_init();
unsigned int b_allocate(unsigned int size);
void b_free(unsigned int start_ptr);
unsigned int b_read(unsigned int base, unsigned int offset);
void b_write(unsigned int base, unsigned int offset, unsigned int value);

unsigned int b_overhead();
unsigned int b_fragmentation();

#endif