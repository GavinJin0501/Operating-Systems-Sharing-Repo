CC=gcc -Wall
BIN=bin
SRC=src
LIBRARIES=-lpthread

all: clean

exercise1: ${SRC}/exercise1.c
	${CC} -o ${BIN}/exercise1 ${SRC}/exercise1.c ${LIBRARIES}
	@${BIN}/exercise1

clean:
	rm -f ${BIN}/* /dev/shm/*