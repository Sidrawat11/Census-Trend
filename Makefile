
earnings:earnings.o maxHeap.o utilities.o BST.o HashTable.o
	g++  earnings.o maxHeap.o utilities.o BST.o HashTable.o -o earnings

earnings.o: earnings.cpp defns.h
	g++ -c earnings.cpp

maxHeap.o: maxHeap.cpp maxHeap.h
	g++ -c maxHeap.cpp

utilities.o: utilities.cpp utilities.h
	g++ -c utilities.cpp

BST.o: BST.cpp BST.h
	g++ -c BST.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp

clean:
	rm *.o earnings
	

