CC=gcc -Wall
BIN=bin
SRC=src


all: exercise

exercise:
	@read -p "which exercise? > " NAME; \
	${CC} -o ${BIN}/exercise$$NAME ${SRC}/exercise$$NAME.c; \
	echo Start exercise$$NAME...; \
	${BIN}/exercise$$NAME; \

clean:
	rm -f ${BIN}/* 

