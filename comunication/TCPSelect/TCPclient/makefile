# makefile sample

TARGET= TCPclientMain.out 
CC= gcc -I../../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../../include
OBJS= TCPclient.o TCPclientMain.o  

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
TCPclient.o: TCPclient.c $(INC)
	$(CC) $(CFLAGS) -c TCPclient.c

TCPclientMain.o: TCPclientMain.c
	$(CC) $(CFLAGS) -c TCPclientMain.c

clean:
	rm -f $(TARGET) $(OBJS)
