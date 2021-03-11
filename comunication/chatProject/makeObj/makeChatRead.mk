# chatProject chatRead makefile

TARGET= chatRead.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall
INC_MAKE= ./makeObj/
CHAT= ./client/groupChat/
OBJS= $(INC_MAKE)chatRead.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(INC_MAKE)chatRead.o: $(CHAT)chatRead.c
	$(CC) $(CFLAGS) -c $(CHAT)chatRead.c -o $(INC_MAKE)chatRead.o

clean:
	rm -f $(TARGET) $(OBJS)
