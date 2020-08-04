TARGET= main.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../ -I../semaphore -I../mutex
INC= cyclicQueueMT.hpp ../uncopyable.hpp ../mutex/mutex.hpp ../semaphore/semaphore.hpp
OBJS= main.o semaphore.o mutex.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

semaphore.o: ../semaphore/semaphore.cpp $(INC)
	$(CC) $(CFLAGS) -c ../semaphore/semaphore.cpp

mutex.o: ../mutes/mutex.cpp $(INC)
	$(CC) $(CFLAGS) -c ../mutes/mutex.cpp

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)