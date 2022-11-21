CC=gcc -Wall
BIN=bin
SRC=src
LIBRARIES=-lpthread

upper: clean ${SRC}/upper.c
	${CC} -o ${BIN}/upper ${SRC}/upper.c
	@${BIN}/upper lower1.txt

multi-upper: clean ${SRC}/multi-upper.c
	${CC} -o ${BIN}/multi-upper ${SRC}/multi-upper.c ${LIBRARIES}
	@${BIN}/multi-upper lower1.txt lower2.txt

clean:
	rm -f ${BIN}/* ./*.*.UPPER.*