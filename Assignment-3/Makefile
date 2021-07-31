OBJS	= Dictionary23Tree.o DictionaryAVLTree.o DictionaryBST.o DictionarySearchTree.o TriNode.o main.o
SOURCE	= Dictionary23Tree.cpp DictionaryAVLTree.cpp DictionaryBST.cpp DictionarySearchTree.cpp TriNode.cpp main.cpp
HEADER	= Dictionary23Tree.h DictionaryAVLTree.h DictionaryBST.h DictionarySearchTree.h TriNode.h
OUT	= hw3
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Dictionary23Tree.o: Dictionary23Tree.cpp
	$(CC) $(FLAGS) Dictionary23Tree.cpp -std=c++11 -lcppunit

DictionaryAVLTree.o: DictionaryAVLTree.cpp
	$(CC) $(FLAGS) DictionaryAVLTree.cpp -std=c++11 -lcppunit

DictionaryBST.o: DictionaryBST.cpp
	$(CC) $(FLAGS) DictionaryBST.cpp -std=c++11 -lcppunit

DictionarySearchTree.o: DictionarySearchTree.cpp
	$(CC) $(FLAGS) DictionarySearchTree.cpp -std=c++11 -lcppunit

TriNode.o: TriNode.cpp
	$(CC) $(FLAGS) TriNode.cpp -std=c++11 -lcppunit

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11 -lcppunit


clean:
	rm -f $(OBJS) $(OUT)