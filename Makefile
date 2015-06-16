main: main.o stage.o shuttle.o myobject.o bomb.o enemy.o super.o
	g++ -o main main.o stage.o shuttle.o myobject.o bomb.o enemy.o super.o -O3 \
	-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -std=c++11\
	#&& rm main.o shuttle.o myobject.o

main.o: main.cpp config.h
	g++ -c main.cpp -O3

stage.o: stage.cpp stage.h 
	g++ -c stage.cpp -O3

shuttle.o: shuttle.cpp shuttle.h 
	g++ -c shuttle.cpp -O3

myobject.o: myobject.cpp myobject.h
	g++ -c myobject.cpp -O3

bomb.o: bomb.cpp bomb.h
	g++ -c bomb.cpp -O3

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp -O3

super.o: super.cpp super.h
	g++ -c super.cpp -O3

clean:
	rm -rf *.o main

run:
	./main