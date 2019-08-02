CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -c testme.c -g $(CFLAGS)

randomtestresults: testme
	gcc -o testme testme.o $(CFLAGS)
	./testme > randomtestresults.out
	gcov testme.c -b -f >> randomtestresults.out

all: testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out 
	rm -f testme