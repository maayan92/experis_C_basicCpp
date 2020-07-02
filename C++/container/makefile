
TARGET= containerMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./
OBJS= container.h array.h containerMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

containerMain.o: containerMain.cpp
	$(CC) $(CFLAGS) -c containerMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
