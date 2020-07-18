
TARGET= hashMapMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= keyValue.h key.h bucket.h hashMap.h
OBJS= hashMapMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hashMapMain.o: hashMapMain.cpp $(INC)
	$(CC) $(CFLAGS) -c hashMapMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
