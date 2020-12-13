#PROG=main
#CC=gcc 
#CFLAGS=-Wall -Wfatal-errors -lm
#LIBS=-lm

#all: $(PROG)
main: citiesReader.o graphe.o  acm.o analyzer.o  main.o
	gcc -o main main.o citiesReader.o graphe.o acm.o analyzer.o -lm
citiesReader.o: citiesReader.c citiesReader.h
	gcc -c citiesReader.c -o citiesReader.o
graphe.o: graphe.c graphe.h citiesReader.h
	gcc -c graphe.c -o graphe.o
acm.o: acm.c acm.h graphe.h citiesReader.h analyzer.h 
	gcc -c acm.c -o acm.o
analyzer.o: analyzer.c analyzer.h
	gcc -c analyzer.c -o analyzer.o
main.o: main.c graphe.h acm.h citiesReader.h 
	gcc -c main.c -o main.o
.PHONY: clean distclean
clean:
	@rm *.o
distclean: clean
	@rm main
