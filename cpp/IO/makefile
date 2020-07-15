
TARGET= virtIOMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../TException -I../String 
INC= ../TException/TException.h ./virtIO.h ./asciiIO.h ./binIO.h
OBJS=  virtIO.o virtIOMain.o ../String/String_t.o

$(TARGET): $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS)

virtIO.o: virtIO.cpp $(INC)
	$(CC) $(CFLAGS) -c virtIO.cpp

	
virtIOMain.o: virtIOMain.cpp
	$(CC) $(CFLAGS) -c virtIOMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
