pathSources = ./sources/

all:
	gcc -o main $(pathSources)*.c

run:
	./main