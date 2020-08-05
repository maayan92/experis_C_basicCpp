TARGET= main.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./
INC= bitSet.hpp
OBJS= main.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)