# makefile sample

TARGET= listFunctionsUnitTest.out 
CC= gcc -I../../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../../include
OBJS= ../GDLList.o listFunctions.o listFunctionsUnitTest.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
GDLList.o: ../GDLList.c $(INC)
	$(CC) $(CFLAGS) -c ../GDLList.c

listFunctions.o: listFunctions.c
	$(CC) $(CFLAGS) -c listFunctions.c


listFunctionsUnitTest.o: listFunctionsUnitTest.c
	$(CC) $(CFLAGS) -c listFunctionsUnitTest.c





clean:
	rm -f $(TARGET) $(OBJS)
