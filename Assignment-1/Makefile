OBJS	= main.o sorting.o
SOURCE	= main.cpp sorting.cpp
HEADER	= sorting.h
OUT	= hw1
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11

sorting.o: sorting.cpp
	$(CC) $(FLAGS) sorting.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
