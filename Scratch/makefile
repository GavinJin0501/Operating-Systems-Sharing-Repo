CC=gcc -Wall
BIN=bin
SRC=src

shared_memory_demo: clean ${SRC}/shared_memory_demo.c
	${CC} -o ${BIN}/shared_memory_demo ${SRC}/shared_memory_demo.c -lrt
	@echo ==========Below are output==========
	@${BIN}/shared_memory_demo

semaphore_demo: clean ${SRC}/semaphore_demo.c
	${CC} -o ${BIN}/semaphore_demo ${SRC}/semaphore_demo.c -lpthread
	@echo ==========Below are output==========
	@${BIN}/semaphore_demo

clean:
	rm -f ${BIN}/*