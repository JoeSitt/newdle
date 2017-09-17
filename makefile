p1 : main.o Executive.o Valid.o
	g++ -Wall -g -std=c++11 main.o Executive.o Valid.o -o p1

main.o : main.cpp Executive.h
	g++ -Wall -c -g -std=c++11 main.cpp

Executive.o : Executive.h Executive.cpp Valid.h
	g++ -Wall -c -g -std=c++11 Executive.cpp

Valid.o: Valid.h Valid.cpp
	g++ -Wall -c -g -std=c++11 Valid.cpp

clean:
	\rm *.o *~ p1
