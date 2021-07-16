OBJS	= auxArrayFunctions.o BinaryNode.o BinarySearchTree.o main.o
SOURCE	= auxArrayFunctions.cpp BinaryNode.cpp BinarySearchTree.cpp main.cpp
HEADER	= auxArrayFunctions.h BinaryNode.h BinarySearchTree.h
OUT	= hw2
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

auxArrayFunctions.o: auxArrayFunctions.cpp
	$(CC) $(FLAGS) auxArrayFunctions.cpp -std=c++11 -lcppunit

BinaryNode.o: BinaryNode.cpp
	$(CC) $(FLAGS) BinaryNode.cpp -std=c++11 -lcppunit

BinarySearchTree.o: BinarySearchTree.cpp
	$(CC) $(FLAGS) BinarySearchTree.cpp -std=c++11 -lcppunit

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11 -lcppunit


clean:
	rm -f $(OBJS) $(OUT)