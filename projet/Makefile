projet: projet.o demo.o
	gcc -o projet projet.o demo.o

projet.o : projet.c
	gcc -c projet.c
 
demo.o : demo.c
	gcc -c demo.c

clean: rm projet *.o

all: projet clean

