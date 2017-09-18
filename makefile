all : calendar clean

calendar : main.o Event.o Executive.o FileHandler.o TimeSlot.o Valid.o
	g++ -Wall -g -std=c++11 main.o Event.o Executive.o FileHandler.o TimeSlot.o Valid.o -o calendar

main.o : main.cpp Executive.h
	g++ -Wall -c -g -std=c++11 main.cpp

Event.o : Event.cpp Event.h TimeSlot.h
	g++ -Wall -c -g -std=c++11 Event.cpp

Executive.o : Executive.h Executive.cpp Event.h Valid.h FileHandler.h
	g++ -Wall -c -g -std=c++11 Executive.cpp

FileHandler.o : FileHandler.cpp FileHandler.h Event.h rapidxml-1.13/rapidxml.hpp
	g++ -Wall -c -g -std=c++11 FileHandler.cpp

TimeSlot.o : TimeSlot.cpp TimeSlot.h
	g++ -Wall -c -g -std=c++11 TimeSlot.cpp

Valid.o : Valid.cpp Valid.h
	g++ -Wall -c -g -std=c++11 Valid.cpp

clean :
	\rm *.o *~ calendar
