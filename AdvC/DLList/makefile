# makefile sample

TARGET= GDLListUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= GDLList.o GDLListUnitTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
GDLList.o: GDLList.c $(INC)
	$(CC) $(CFLAGS) -c GDLList.c

GDLListUnitTest.o: GDLListUnitTest.c
	$(CC) $(CFLAGS) -c GDLListUnitTest.c

	
clean:
	rm -f $(TARGET) $(OBJS)
