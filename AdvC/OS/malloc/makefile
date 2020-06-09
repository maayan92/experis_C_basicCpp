# makefile sample

TARGET= mallocUnitTest.out 
CC= gcc -I../../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../../include
OBJS= malloc.o mallocUnitTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
malloc.o: malloc.c $(INC)
	$(CC) $(CFLAGS) -c malloc.c

mallocUnitTest.o: mallocUnitTest.c
	$(CC) $(CFLAGS) -c mallocUnitTest.c
		
clean:
	rm -f $(TARGET) $(OBJS)
