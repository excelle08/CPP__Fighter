main: main.o shuttle.o myobject.o bomb.o
	g++ -o main main.o shuttle.o myobject.o bomb.o \
	-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio \
	&& rm main.o shuttle.o myobject.o

main.o: main.cpp config.h
	g++ -c main.cpp 

shuttle.o: shuttle.cpp shuttle.h
	g++ -c shuttle.cpp

myobject.o: myobject.cpp myobject.h
	g++ -c myobject.cpp

bomb.o: bomb.cpp bomb.h
	g++ -c bomb.cpp

clean:
	rm main

run:
	./main