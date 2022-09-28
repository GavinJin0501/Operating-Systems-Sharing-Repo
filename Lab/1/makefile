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

parallel_compilation: clean ${SRC}/parallel_compilation.c
	${CC} -o ${BIN}/parallel_compilation ${SRC}/parallel_compilation.c
	@echo =====================================
	@${BIN}/parallel_compilation concurrent-compilation
	@echo =====================================

spy: ${SRC}/spy.c
	${CC} -o ${BIN}/spy ${SRC}/spy.c
	${BIN}/spy

clean:
	rm -f ${BIN}/* ${OBJ}/*

