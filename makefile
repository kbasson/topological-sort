topologicalSort: topologicalSort.o helpers.o
	clang -Wall -pedantic -std=c99 topologicalSort.o helpers.o -o topologicalSort

topologicalSort.o: topologicalSort.c topologicalSort.h
	clang -Wall -pedantic -std=c99 -c topologicalSort.c -o topologicalSort.o

helpers.o: helpers.c topologicalSort.h
	clang -Wall -pedantic -std=c99 -c helpers.c -o helpers.o

clean:
	rm *.o
