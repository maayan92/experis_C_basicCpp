# makefile sample

TARGET= heapUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= heap.o heapUnitTest.o ../vector/vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heap.o: heap.c $(INC)
	$(CC) $(CFLAGS) -c heap.c

heapUnitTest.o: heapUnitTest.c
	$(CC) $(CFLAGS) -c heapUnitTest.c
		
clean:
	rm -f $(TARGET) $(OBJS)
