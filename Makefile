pathHeaders = ./headers/
pathSources = ./sources/

BINMANAGER_H = $(pathHeaders)binmanager.h
BINMANAGER_C = $(pathSources)binmanager.c

COMMANDS_H = $(pathHeaders)commands.h
COMMANDS_C = $(pathSources)commands.c

CSVMANAGER_H = $(pathHeaders)csvmanager.h
CSVMANAGER_C = $(pathSources)csvmanager.c

LINKEDLIST_H = $(pathHeaders)linkedlist.h
LINKEDLIST_C = $(pathSources)linkedlist.c

REGISTERS_H = $(pathHeaders)registers.h
REGISTERS_C = $(pathSources)registers.c

all:
	gcc -o main $(pathSources)*.c

run: main
	./main