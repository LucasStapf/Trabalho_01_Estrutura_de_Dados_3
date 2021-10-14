pathHeaders = ./headers/
pathSources = ./sources/
pathObjects = ./objects/

BINMANAGER_H = $(pathHeaders)binmanager.h
BINMANAGER_C = $(pathSources)binmanager.c
BINMANAGER_O = $(pathObjects)binmanager.o

COMMANDS_H = $(pathHeaders)commands.h
COMMANDS_C = $(pathSources)commands.c
COMMANDS_O = $(pathObjects)commands.o

CSVMANAGER_H = $(pathHeaders)csvmanager.h
CSVMANAGER_C = $(pathSources)csvmanager.c
CSVMANAGER_O = $(pathObjects)csvmanager.o

LINKEDLIST_H = $(pathHeaders)linkedlist.h
LINKEDLIST_C = $(pathSources)linkedlist.c
LINKEDLIST_O = $(pathObjects)linkedlist.o

REGISTERS_H = $(pathHeaders)registers.h
REGISTERS_C = $(pathSources)registers.c
REGISTERS_O = $(pathObjects)registers.o

MAIN_C = $(pathSources)main.c
MAIN_O = $(pathObjects)main.o

$(BINMANAGER_O): $(BINMANAGER_C) $(BINMANAGER_H)
	gcc -o $(BINMANAGER_O) -c $(BINMANAGER_C)

$(COMMANDS_O): $(COMMANDS_C) $(COMMANDS_H)
	gcc -o $(COMMANDS_O) -c $(COMMANDS_C)

$(CSVMANAGER_O): $(CSVMANAGER_C) $(CSVMANAGER_H)
	gcc -o $(CSVMANAGER_O) -c $(CSVMANAGER_C)

$(LINKEDLIST_O): $(LINKEDLIST_C) $(LINKEDLIST_H)
	gcc -o $(LINKEDLIST_O) -c $(LINKEDLIST_C)

$(REGISTERS_O): $(REGISTERS_C) $(REGISTERS_H)
	gcc -o $(REGISTERS_O) -c $(REGISTERS_C)

$(MAIN_O): $(MAIN_C)
	gcc -o $(MAIN_O) -c $(MAIN_C)

main: $(MAIN_O) $(BINMANAGER_O) $(COMMANDS_O) $(CSVMANAGER_O) $(LINKEDLIST_O) $(REGISTERS_O)
	gcc -o main $(MAIN_O) $(BINMANAGER_O) $(COMMANDS_O) $(CSVMANAGER_O) $(LINKEDLIST_O) $(REGISTERS_O)

all: main

run: main
	./main

clean:
	rm $(pathObjects)*.o