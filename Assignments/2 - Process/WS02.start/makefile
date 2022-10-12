CC=gcc -Wall
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: clean Q1 Q2 Q3

Q1: ${SRC}/trace.c
	${CC} -o ${OBJ}/trace.o $^ -I${INC}
	@echo "##################################################"
	@${OBJ}/trace.o
	@echo "##################################################"

Q2: ${SRC}/decoder.c
	${CC} -o ${OBJ}/decoder.o $^ -I${INC}
	@echo "##################################################"
	@${OBJ}/decoder.o
	@echo "##################################################"

Q3: ${SRC}/multi-converter.c ${SRC}/converters.c
	${CC} -o ${OBJ}/multi-converter.o $^ -I${INC}
	@echo "##################################################"
	@${OBJ}/multi-converter.o USD 256
	@${OBJ}/multi-converter.o CNY 100
	@echo "##################################################"
	
decoder: ${SRC}/decoder.c
	${CC} -Wall -o ${OBJ}/decoder.o ${SRC}/decoder.c -I${INC}
	@echo "##################################################"
	@${OBJ}/decoder.o
	@echo "##################################################"

converter: ${SRC}/converters.c
	${CC} -Wall -c -o ${OBJ}/converters.o ${SRC}/converters.c -I${INC}

multi-converter: converter ${SRC}/multi-converter.c
	${CC} -Wall -c -o ${OBJ}/multi-converter.o ${SRC}/multi-converter.c -I${INC}
	${CC} -Wall -o ${BIN}/multi-converter ${OBJ}/multi-converter.o ${OBJ}/converters.o
	@echo "##################################################"
	@${BIN}/multi-converter CNY "100.0"
	@echo "##################################################"
	@${BIN}/multi-converter USD "256.0"
	@echo "##################################################"

clean:
	rm -f ${LIB}/* ${OBJ}/* ${BIN}/*
