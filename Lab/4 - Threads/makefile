CC=gcc -Wall
BIN=bin
SRC=src
LIBRARIES=-lpthread

all: clean

exercise1: ${SRC}/exercise1.c
	${CC} -o ${BIN}/exercise1 ${SRC}/exercise1.c ${LIBRARIES}
	@${BIN}/exercise1

example1: ${SRC}/example1.c
	${CC} -o ${BIN}/example1 ${SRC}/example1.c ${LIBRARIES}
	@${BIN}/example1

example1_1: ${SRC}/example1_1.c
	${CC} -o ${BIN}/example1_1 ${SRC}/example1_1.c ${LIBRARIES}
	@${BIN}/example1_1

example2: ${SRC}/example2.c
	${CC} -o ${BIN}/example2 ${SRC}/example2.c ${LIBRARIES}
	@${BIN}/example2

example3: ${SRC}/example3.c
	${CC} -o ${BIN}/example3 ${SRC}/example3.c ${LIBRARIES}
	@${BIN}/example3

clean:
	rm -f ${BIN}/* /dev/shm/*