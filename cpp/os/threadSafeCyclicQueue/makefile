TARGET= main.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../ -I../semaphore
INC= cyclicQueueMT.hpp ../uncopyable.hpp
OBJS= main.o ../semaphore/semaphore.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)