# hashSet makefile

TARGET= genHashMapUnitTesting.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -I../include
OBJS= genHashMapUnitTesting.o genHashMap.o genDLList.o -lm

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genHashMapUnitTesting.o: genHashMapUnitTesting.c ../include/genHashMap.h
	$(CC) $(CFLAGS) -c genHashMapUnitTesting.c
    	
genHashMap.o: genHashMap.c ../include/genHashMap.h ../include/genHashMap.h ../include/genDLList.h ../include/genDLListIter.h ../include/ADTerror.h
	$(CC) $(CFLAGS) -c genHashMap.c
    	
genDLList.o: ../genDLList/genDLList.c ../include/genDLList.h ../include/genDLListIter.h ../include/ADTerror.h
	$(CC) $(CFLAGS) -c ../genDLList/genDLList.c
	
clean:
	rm -f $(TARGET) $(OBJS)
