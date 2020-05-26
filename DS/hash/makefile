# makefile sample

TARGET= hashUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror 
INC= ../../include
OBJS= hash.o hashUnitTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm
		
hash.o: hash.c $(INC)
	$(CC) $(CFLAGS) -c hash.c

hashUnitTest.o: hashUnitTest.c
	$(CC) $(CFLAGS) -c hashUnitTest.c

clean:
	rm -f $(TARGET) $(OBJS)
