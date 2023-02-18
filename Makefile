studsys: func.o main.o
	gcc main.o func.o -o studsys
fun: func.c
	gcc -g -c func.c
main: main.c head.h
	gcc -g -c main.c
run:
	./studsys
clean:
	rm *.o studsys
