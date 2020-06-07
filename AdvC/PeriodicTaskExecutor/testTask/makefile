# makefile sample

TARGET= taskUnitTest.out 
CC= gcc -I../../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror -std=gnu99
INC= ../../../include 
OBJS= taskUnitTest.o ../task.o ../time.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

taskUnitTest.o: taskUnitTest.c
	$(CC) $(CFLAGS) -c taskUnitTest.c
	
clean:
	rm -f $(TARGET) $(OBJS)
