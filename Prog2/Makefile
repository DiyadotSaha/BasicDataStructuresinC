#------------------------------------------------------------------------------
#  Makefile for prog2 
# 
#  make             makes simulator
#  make clean       removes object files
#  make check       runs valgrind to check for memory errors
#
#  simulator.c		this is where the simulator is implemented

#  Heap.h				given. you just need to include this in the corresp .c file
#  Heap.c				this is where you implement the functions Queueed in Heap.h
#  PriorityQueue.h		given. you just need to include this in the corresp .c file
#  PriorityQueue.c		where you implement the signatures given in PriorityQueue.h
#  Queue.h				given. you just need to include this in the corresp .c file
#  Queue.c				where you implement the signatures given in Queue.h
#------------------------------------------------------------------------------

simulator:	simulator.o Queue.o PriorityQueue.o 
	cc -o prog2 simulator.o Queue.o PriorityQueue.o

simulator.o: Queue.h Heap.h PriorityQueue.h simulator.c 
	cc -c simulator.c

Queue.o: Queue.h Queue.c
	cc -c Queue.c




PriorityQueue.o: Heap.h PriorityQueue.h Heap.c PriorityQueue.c
	cc -c PriorityQueue.c

%.o: %.c
	cc -c -o $@ $< -std=c99

clean:
	rm -f simulator simulator.o Queue.o Heap.o PriorityQueue.o prog2

check: 
	valgrind --leak-check=full ./prog2