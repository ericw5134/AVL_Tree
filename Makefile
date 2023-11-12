all: PQdemo

PQdemo: PQdemo.o  
	g++ -Wall -o PQdemo PQdemo.o

PQdemo.o: PQdemo.cpp BinaryHeap.h AvlTree.h PQ.h dsexceptions.h
	g++ -Wall -o PQdemo.o -c PQdemo.cpp

clean:
	rm -f PQdemo *.o 
