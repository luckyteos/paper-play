all: main

main: main.c utilities.c
	gcc -Wall main.c utilities.c -o main

main.o: main.c
	gcc -c main.c

utilities.o: utilities.c
	gcc -c utilities.c

clean:
	rm main.o main