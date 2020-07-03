
TARGET= containerMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./
INC= container.h array.h dList.h
OBJS= containerMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

containerMain.o: containerMain.cpp $(INC)
	$(CC) $(CFLAGS) -c containerMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
