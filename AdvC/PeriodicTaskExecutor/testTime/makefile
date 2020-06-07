# makefile sample

TARGET= timeUnitTest.out 
CC= gcc 
CFLAGS= -ansi -g -pedantic -Wall -Werror -std=gnu99
INC= ../../../include
OBJS= timeUnitTest.o ../time.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
timeUnitTest.o: timeUnitTest.c
	$(CC) $(CFLAGS) -c timeUnitTest.c

clean:
	rm -f $(TARGET) $(OBJS)
