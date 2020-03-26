#Makefile for the assignment

asn2:main.cpp

	g++ -o asn2 main.cpp 

clean:
	rm -f asn2 *.out *.o core
