CC=gcc -Wall
BIN=bin
SRC=src
LIBRARIES=-lrt -lpthread


exercise1: clean ${SRC}/exercise1.c
	${CC} -o ${BIN}/exercise1 ${SRC}/exercise1.c -lrt
	@${BIN}/exercise1

exercise2: clean ${SRC}/exercise2.c
	${CC} -o ${BIN}/exercise2 ${SRC}/exercise2.c ${LIBRARIES}
	@${BIN}/exercise2


exercise3: clean ${SRC}/exercise3.c
	${CC} -o ${BIN}/exercise3 ${SRC}/exercise3.c ${LIBRARIES}
	@${BIN}/exercise3

exercise4: clean ${SRC}/exercise4.c
	${CC} -o ${BIN}/exercise4 ${SRC}/exercise4.c ${LIBRARIES}
	@${BIN}/exercise4
 
clean:
	rm -f ${BIN}/* /dev/shm/*