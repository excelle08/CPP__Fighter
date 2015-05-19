test: test.o
	g++ -o test test.o -framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio

test.o: test.cpp
	g++ -c test.cpp 

clean:
	rm -f test.o