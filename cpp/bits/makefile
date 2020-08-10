TARGET= main.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./
INC= bitSet.hpp lut.hpp bitwiseOperations.hpp
OBJS= lut.o main.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS)

lut.o: lut.cpp $(INC)
	$(CC) $(CFLAGS) -c lut.cpp

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)