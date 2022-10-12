CC=gcc -Wall
BIN=bin
SRC=src
OBJ=obj
PC=concurrent-compilation



all: exercise

exercise:
	@read -p "which exercise? > " NAME; \
	${CC} -o ${BIN}/exercise$$NAME ${SRC}/exercise$$NAME.c; \
	echo Start exercise$$NAME...; \
	${BIN}/exercise$$NAME; \

parallel_compilation: clean ${PC}/parallel_compilation.c
	${CC} -o ${PC}/parallel_compilation ${PC}/parallel_compilation.c
	@echo =====================================
	@${PC}/parallel_compilation ${PC}/main.c ${PC}/titi.c ${PC}/tata.c ${PC}/toto.c
	@echo =====================================

spy: ${SRC}/spy.c
	${CC} -o ${BIN}/spy ${SRC}/spy.c
	${BIN}/spy

clean:
	rm -f ${BIN}/* ${OBJ}/*

