CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

runtest: testme
	./testme &> results.out
	gcov testme.c -b -f >> result.out
	cat testme.c.gcov >> result.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme