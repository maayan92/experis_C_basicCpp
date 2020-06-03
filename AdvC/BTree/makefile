# makefile sample

TARGET= GBinaryTreeUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= GBinaryTree.o GBinaryTreeUnitTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
GBinaryTree.o: GBinaryTree.c $(INC)
	$(CC) $(CFLAGS) -c GBinaryTree.c

GBinaryTreeUnitTest.o: GBinaryTreeUnitTest.c
	$(CC) $(CFLAGS) -c GBinaryTreeUnitTest.c





clean:
	rm -f $(TARGET) $(OBJS)
