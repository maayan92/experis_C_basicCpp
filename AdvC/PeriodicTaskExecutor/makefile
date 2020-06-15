# makefile sample

TARGET= executorUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror -std=gnu99 -fPIC
INC= ../../include
OBJS= executor.o executorUnitTest.o task.o time.o ../heap/heap.o ../vector/vector.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
executor.o: executor.c $(INC)
	$(CC) $(CFLAGS) -c executor.c

executorUnitTest.o: executorUnitTest.c
	$(CC) $(CFLAGS) -c executorUnitTest.c
	
task.o: task.c
	$(CC) $(CFLAGS) -c task.c

time.o: time.c
	$(CC) $(CFLAGS) -c time.c

clean:
	rm -f $(TARGET) $(OBJS)
