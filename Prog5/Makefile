prog5: List.h List.o PQueue.h PQueue.o Graph.h Graph.o prog5.o Dictionary.h Dictionary.o
	cc -o prog5 prog5.o List.o PQueue.o Graph.o Dictionary.o

%.o: %.c
	cc -c -o $@ $< -g

clean:
	rm prog5 *.o 