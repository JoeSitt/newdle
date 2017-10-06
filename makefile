run : main.o Manager.o Event.o TimeSlot.o Executive.o Valid.o Task.o
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -Wall -g -std=c++11 main.o Event.o Manager.o TimeSlot.o Executive.o Valid.o Task.o -o run -lboost_serialization
 
main.o : main.cpp Manager.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 main.cpp

Executive.o: Executive.cpp Executive.h Manager.h Valid.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Executive.cpp

Valid.o: Valid.cpp Valid.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Valid.cpp

Manager.o : Manager.cpp Manager.h Event.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Manager.cpp

Event.o : Event.cpp Event.h TimeSlot.h Task.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Event.cpp

TimeSlot.o : TimeSlot.cpp TimeSlot.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 TimeSlot.cpp

Task.o : Task.cpp Task.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Task.cpp

clean :
	\rm *.o *~ run
