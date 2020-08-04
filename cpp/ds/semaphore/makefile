TARGET= threadSemaphore.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../
INC= semaphore.hpp ../uncopyable.hpp
OBJS= semaphore.o threadSemaphore.o 

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

semaphore.o: semaphore.cpp $(INC)
	$(CC) $(CFLAGS) -c semaphore.cpp

threadSemaphore.o: threadSemaphore.cpp
	$(CC) $(CFLAGS) -c threadSemaphore.cpp

clean:
	rm -f $(TARGET) $(OBJS)