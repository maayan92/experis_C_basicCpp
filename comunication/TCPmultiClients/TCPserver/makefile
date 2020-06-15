# makefile sample

TARGET= TCPserverMain.out 
CC= gcc -I../../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../../include
OBJS= TCPserver.o TCPserverMain.o ../GDLList.o ../listFunctions.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
TCPserver.o: TCPserver.c $(INC)
	$(CC) $(CFLAGS) -c TCPserver.c

TCPserverMain.o: TCPserverMain.c
	$(CC) $(CFLAGS) -c TCPserverMain.c

clean:
	rm -f $(TARGET) $(OBJS)
