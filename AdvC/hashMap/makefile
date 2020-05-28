# makefile sample

TARGET= hashMapUnitTest.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror 
INC= ../../include
OBJS= hashMap.o hashMapUnitTest.o ../DLList/GDLList.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm
		
hashMap.o: hashMap.c $(INC)
	$(CC) $(CFLAGS) -c hashMap.c

hashMapUnitTest.o: hashMapUnitTest.c
	$(CC) $(CFLAGS) -c hashMapUnitTest.c

clean:
	rm -f $(TARGET) $(OBJS)
