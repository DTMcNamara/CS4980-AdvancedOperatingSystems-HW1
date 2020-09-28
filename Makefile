OPTIONS=-DMEMSIZE=1024 -DPAGESIZE=128 -DNUMPAGES=8 -DSMALLEST_BLOCK=4 -DNUM_BLOCKS=128


#all: page_linear buddy_example list_simple_mem
all: list_page_linear list_buddy_example list_simple_mem

list_simple_mem: simple_mem.o driver_list.o
	gcc $(OPTIONS) -g simple_mem.o driver_list.o -o list_simple_mem

simple_mem.o: simple_mem.c
	gcc $(OPTIONS) -g -c simple_mem.c -o simple_mem.o

driver_list.o: driver_list.c
	gcc $(OPTIONS) -g -c driver_list.c -o driver_list.o

list_page_linear: linear.o page.o
	gcc $(OPTIONS) -g page.o linear.o -o list_page_linear

page.o: page.c
	gcc $(OPTIONS) -g -c page.c -o page.o

linear.o: linear.c
	gcc $(OPTIONS) -g -c linear.c -o linear.o

list_buddy_example: buddy.o buddy_example.o
	gcc $(OPTIONS) -g buddy.o buddy_example.o -o list_buddy_example

buddy.o: buddy.c
	gcc $(OPTIONS) -g -c buddy.c -o buddy.o

buddy_example.o: buddy_example.c
	gcc $(OPTIONS) -g -c buddy_example.c -o buddy_example.o
