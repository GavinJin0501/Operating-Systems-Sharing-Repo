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

exercise4: ${SRC}/exercise4.c
	${CC} -o ${BIN}/exercise4 ${SRC}/exercise4.c ${LIBRARIES}
	@${BIN}/exercise4

exercise5: ${SRC}/exercise5.c
	${CC} -o ${BIN}/exercise5 ${SRC}/exercise5.c ${LIBRARIES}
	@${BIN}/exercise5


clean:
	rm -f ${BIN}/* /dev/shm/*