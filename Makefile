CC=g++
CFLAGS_MAKE=-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -std=c++11 -O3  
CFLAGS_COMPLIE=-std=c++11 -g -O2
  
# 目标文件  
TARGET=main 
SRCS = main.cpp bomb.cpp enemy.cpp myobject.cpp shuttle.cpp stage.cpp super.cpp
INC = -I./
  
OBJS = $(SRCS:.cpp=.o)  
  
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS_MAKE) $(INC) -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAGS_COMPLIE) $(INC) -o $@ -c $<  


clean:
	rm -rf *.o main

run:
	./main