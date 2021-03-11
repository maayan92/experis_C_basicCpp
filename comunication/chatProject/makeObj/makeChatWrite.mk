# chatProject chatWrite makefile

TARGET= chatWrite.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall
INC_MAKE= ./makeObj/
CHAT= ./client/groupChat/
OBJS= $(INC_MAKE)chatWrite.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(INC_MAKE)chatWrite.o: $(CHAT)chatWrite.c
	$(CC) $(CFLAGS) -c $(CHAT)chatWrite.c -o $(INC_MAKE)chatWrite.o

clean:
	rm -f $(TARGET) $(OBJS)
