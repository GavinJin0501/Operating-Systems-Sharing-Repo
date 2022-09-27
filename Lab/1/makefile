CC=gcc -Wall
BIN=bin
SRC=src
OBJ=obj



all: exercise

exercise:
	@read -p "which exercise? > " NAME; \
	${CC} -o ${BIN}/exercise$$NAME ${SRC}/exercise$$NAME.c; \
	echo Start exercise$$NAME...; \
	${BIN}/exercise$$NAME; \

exercise3: ${SRC}/exercise3.c
	${CC} -o ${BIN}/exercise3 ${SRC}/exercise3.c
	${BIN}/exercise3 ./concurrent-compilation 

parallel_compilation: clean ${SRC}/parallel_compilation.c
	${CC} -o ${BIN}/parallel_compilation ${SRC}/parallel_compilation.c
	${BIN}/parallel_compilation concurrent-compilation

spy: ${SRC}/spy.c
	${CC} -o ${BIN}/spy ${SRC}/spy.c
	${BIN}/spy

clean:
	rm -f ${BIN}/* ${OBJ}/*

