# makefile sample

TARGET= vectorUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= vector.o vectorUnitTest.o sortVector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
vector.o: vector.c $(INC)
	$(CC) $(CFLAGS) -c vector.c

vectorUnitTest.o: vectorUnitTest.c
	$(CC) $(CFLAGS) -c vectorUnitTest.c

sortVector.o: sortVector.c $(INC)
	$(CC) $(CFLAGS) -c sortVector.c
	
clean:
	rm -f $(TARGET) $(OBJS)
