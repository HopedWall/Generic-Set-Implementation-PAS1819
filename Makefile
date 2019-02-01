CCFLAGS = -Wall -pedantic

main.exe : voce.o main.o setexception.o
	g++ main.o voce.o setexception.o -o main.exe

voce.o : voce.cpp
	g++ $(CCFLAGS) -c voce.cpp -o voce.o

main.o : main.cpp
	g++ $(CCFLAGS) -c main.cpp -o main.o

setexception.o : setexception.cpp
	g++ $(CCFLAGS) -c setexception.cpp -o setexception.o

clean:
	rm *.o *.exe