CC=gcc -Wall
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src


all: doublell newlibstack libfifo

${OBJ}/stack_array.o: ${INC}/stack.h ${SRC}/stack_array.c
	${CC} -c -o ${OBJ}/stack_array.o ${SRC}/stack_array.c -I${INC}

${OBJ}/stack_test.o: ${INC}/stack.h ${SRC}/stack_test.c
	${CC} -c -o ${OBJ}/stack_test.o ${SRC}/stack_test.c -I${INC}

${OBJ}/fifo_test.o: ${INC}/fifo.h ${SRC}/fifo_test.c
	${CC} -c -o ${OBJ}/fifo_test.o ${SRC}/fifo_test.c -I${INC}

${OBJ}/stack_list.o: ${INC}/stack.h ${SRC}/stack_list.c
	${CC} -c -o ${OBJ}/stack_list.o ${SRC}/stack_list.c -I${INC}

${OBJ}/fifo_list.o: ${INC}/fifo.h ${SRC}/fifo_list.c
	${CC} -c -o ${OBJ}/fifo_list.o ${SRC}/fifo_list.c -I${INC}

${BIN}/stack_test: ${OBJ}/stack_test.o ${OBJ}/stack_array.o
	${CC} -o ${BIN}/stack_test ${OBJ}/stack_test.o ${OBJ}/stack_array.o

runstack: ${BIN}/stack_test
	@echo "Testing Stack"
	@echo "============="
	${BIN}/stack_test
	@echo "============="

doublell: ${INC}/list.h ${SRC}/list_impl.c
	${CC} -c -o ${OBJ}/list_impl.o ${SRC}/list_impl.c -I${INC}

libstack: ${OBJ}/stack_array.o
	ar -crs ${LIB}/libstack.a ${OBJ}/stack_array.o

newlibstack: doublell ${OBJ}/stack_list.o
	ar -rsv ${LIB}/libstack.a ${OBJ}/stack_list.o ${OBJ}/list_impl.o

libfifo: doublell ${OBJ}/fifo_list.o
	ar -crs ${LIB}/libfifo.a ${OBJ}/fifo_list.o ${OBJ}/list_impl.o

testlibstack: ${SRC}/stack_test.c ${OBJ}/stack_test.o
	${CC} -o ${BIN}/stack_test ${OBJ}/stack_test.o ${LIB}/libstack.a

testlibfifo: ${SRC}/fifo_test.c ${OBJ}/fifo_test.o
	${CC} -o ${BIN}/fifo_test ${OBJ}/fifo_test.o  ${LIB}/libfifo.a

runtestlibstack: newlibstack testlibstack
	@echo "Start testing libstack..."
	@echo "========================="
	@${BIN}/stack_test
	@echo "========================="

runtestlibfifo: libfifo testlibfifo
	@echo "Start testing libfifio..."
	@echo "========================="
	@${BIN}/fifo_test
	@echo "========================="

# Utilities
clean:
	rm -f ${OBJ}/* ${BIN}/* ${LIB}/*
