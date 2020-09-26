OPTIONS=-DMEMSIZE=1024 -DPAGESIZE=512 -DSMALLEST_BLOCK=4 -DNUM_BLOCKS=64


# all: page_linear buddy_example list_simple_mem
all: list_simple_mem list_buddy_example

list_simple_mem: simple_mem.o driver_list.o
	gcc $(OPTIONS) -g simple_mem.o driver_list.o -o list_simple_mem

simple_mem.o: simple_mem.c
	gcc $(OPTIONS) -g -c simple_mem.c -o simple_mem.o

driver_list.o: driver_list.c
	gcc $(OPTIONS) -g -c driver_list.c -o driver_list.o

# page_linear: linear.o page.o
# 	gcc linear.o page.o -o linear

# page.o: page.c
# 	gcc $(OPTIONS) -g -c page.c -o page.o

# linear.o: linear.c
# 	gcc $(OPTIONS) -g -c linear.c -o linear.o

list_buddy_example: buddy.o buddy_example.o
	gcc $(OPTIONS) -g buddy.o buddy_example.o -o list_buddy_example

buddy.o: buddy.c
	gcc $(OPTIONS) -g -c buddy.c -o buddy.o

buddy_example: buddy_example.c
	gcc $(OPTIONS) -g -c buddy_example.c -o buddy_example.o
