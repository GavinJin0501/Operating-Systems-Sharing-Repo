CC=gcc -Wall
BIN=bin
SRC=src
TXT=txt
LIBRARIES=-lpthread

upper: clean ${SRC}/upper.c
	${CC} -o ${BIN}/upper ${SRC}/upper.c
	@${BIN}/upper ${TXT}/lower1.txt

multi-upper: clean ${SRC}/multi-upper.c
	${CC} -o ${BIN}/multi-upper ${SRC}/multi-upper.c ${LIBRARIES}
	@${BIN}/multi-upper ${TXT}/lower1.txt ${TXT}/lower2.txt

multi-upper-fixed: clean ${SRC}/multi-upper-fixed.c
	${CC} -o ${BIN}/multi-upper-fixed ${SRC}/multi-upper-fixed.c ${LIBRARIES}
	@${BIN}/multi-upper-fixed ${TXT}/lower1.txt ${TXT}/lower2.txt ${TXT}/lower3.txt ${TXT}/lower4.txt ${TXT}/lower5.txt

clean:
	rm -f ${BIN}/* ${TXT}/*.*.UPPER.*