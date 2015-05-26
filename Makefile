main: main.o stage.o shuttle.o myobject.o bomb.o enemy.o
	g++ -o main main.o stage.o shuttle.o myobject.o bomb.o enemy.o -g \
	-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio \
	#&& rm main.o shuttle.o myobject.o

main.o: main.cpp config.h
	g++ -c main.cpp -g 

stage.o: stage.cpp stage.h 
	g++ -c stage.cpp -g 

shuttle.o: shuttle.cpp shuttle.h 
	g++ -c shuttle.cpp -g 

myobject.o: myobject.cpp myobject.h
	g++ -c myobject.cpp -g 

bomb.o: bomb.cpp bomb.h
	g++ -c bomb.cpp -g 

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp -g

clean:
	rm -rf *.o main

run:
	./main