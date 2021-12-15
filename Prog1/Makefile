manager: agendaManager.c List.c List.h
	cc -o prog1 -g agendaManager.c List.c

%.o: %.c
	cc -c -o $@ $< -std=c99

clean:
	rm prog1