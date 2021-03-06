run : main.o Manager.o Event.o Executive.o Valid.o Task.o Time.o Session.o
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -Wall -g -std=c++11 main.o Event.o Manager.o Executive.o Valid.o Task.o Time.o Session.o -o run -lboost_serialization
 
main.o : main.cpp Executive.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 main.cpp

Executive.o: Executive.cpp Executive.h Manager.h Valid.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Executive.cpp

Valid.o: Valid.cpp Valid.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Valid.cpp

Manager.o : Manager.cpp Manager.h Event.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Manager.cpp

Event.o : Event.cpp Event.h Task.h Time.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Event.cpp

Task.o : Task.cpp Task.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Task.cpp

Time.o : Time.cpp Time.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Time.cpp

Session.o : Session.cpp Session.h Time.h
	g++ -Lboost_1_55_0/lib -Wl,-rpath=boost_1_55_0/lib -lboost_serialization -I boost_1_55_0 -Wall -c -g -std=c++11 Session.cpp

clean :
	\rm *.o *~ run
