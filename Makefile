
earnings:earnings.o maxHeap.o utilities.o
	g++  earnings.o maxHeap.o utilities.o -o earnings

earnings.o: earnings.cpp defns.h
	g++ -c earnings.cpp

maxHeap.o: maxHeap.cpp maxHeap.h
	g++ -c maxHeap.cpp

utilities.o: utilities.cpp utilities.h
	g++ -c utilities.cpp

clean:
	rm *.o earnings
	




