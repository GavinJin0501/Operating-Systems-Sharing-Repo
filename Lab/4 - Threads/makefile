CC=gcc -Wall
BIN=bin
SRC=src
LIBRARIES=-lpthread

all: clean

exercise1: ${SRC}/exercise1.c
	${CC} -o ${BIN}/exercise1 ${SRC}/exercise1.c ${LIBRARIES}
	@${BIN}/exercise1

exercise2: ${SRC}/exercise2.c
	${CC} -o ${BIN}/exercise2 ${SRC}/exercise2.c ${LIBRARIES}
	@${BIN}/exercise2

exercise3: ${SRC}/exercise3.c
	${CC} -o ${BIN}/exercise3 ${SRC}/exercise3.c ${LIBRARIES}
	@${BIN}/exercise3

clean:
	rm -f ${BIN}/* /dev/shm/*