CC=gcc -Wall
BIN=bin
SRC=src
OBJ=obj
PC=concurrent-compilation



all: clean parallel_compilation

parallel_compilation: clean ./parallel_compilation.c
	${CC} -o ./parallel_compilation ./parallel_compilation.c
	@echo =====================================
	@./parallel_compilation ./main.c ./titi.c ./tata.c ./toto.c
	@echo =====================================


clean:
	rm -f ./*.o

