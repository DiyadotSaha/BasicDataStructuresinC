prog3: prog3.o List.h List.o Dictionary.h Dictionary.o HashTable.h HashTable.o
	cc -o prog3 prog3.o List.o Dictionary.o HashTable.o

%.o: %.c
	cc -c -o $@ $<

clean:
	rm *.o prog3