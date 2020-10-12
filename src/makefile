CC = gcc
CFLAGS = -Wall

main: main.c meteo.o helpers.o interfaces.o
	$(CC) $(CFLAGS) main.c meteo.o helpers.o interfaces.o -o main

meteo.o: meteo.c helpers.c
	$(CC) $(CFLAGS) -c meteo.c helpers.c

interfaces.o: interfaces.c meteo.c helpers.c
	$(CC) $(CFLAGS) -c interfaces.c meteo.c helpers.c

helpers.o: helpers.c
	$(CC) $(CFLAGS) -c helpers.c


default: main

.PHONY: clean
clean:
	rm -rf *.o