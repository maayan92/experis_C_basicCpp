# makefile sample

TARGET= GDLListUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= GDLList.o GDLListUnitTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heartGame.o: GDLList.c GDLList.h $(INC)
	$(CC) $(CFLAGS) -c GDLList.c

heartGameMain.o: GDLListUnitTest.c
	$(CC) $(CFLAGS) -c GDLListUnitTest.c

	
clean:
	rm -f $(TARGET) $(OBJS)
