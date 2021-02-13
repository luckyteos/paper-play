all: main

main:	main.c
	gcc -g -o main main.c

main.o: main.c
	gcc -c main.c

clean:
	rm main.o main