
TARGET= containerMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../TException -I../String
INC= container.h array.h dList.h ../TException/TException.h
OBJS= ../String/String_t.cpp containerMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

containerMain.o: containerMain.cpp $(INC)
	$(CC) $(CFLAGS) -c containerMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
