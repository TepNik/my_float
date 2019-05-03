main.exe: main.o fraction.o
	g++ -o main.exe main.o fraction.o
main.o: main.cpp fraction.o
	g++ -c -o main.o main.cpp
fraction.o: fraction.h fraction.cpp
	g++ -c -o fraction.o fraction.cpp