all:
	gcc -c labzero.c -Wall -Wextra
	gcc -o lab0 labzero.o -lm