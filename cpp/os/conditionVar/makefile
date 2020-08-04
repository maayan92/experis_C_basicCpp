TARGET= main.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../mutex -I../
INC= conditionVariable.hpp mutexLocker.hpp ../uncopyable.hpp ../mutex/mutex.hpp
OBJS= conditionVariable.o mutex.o main.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

conditionVariable.o: conditionVariable.cpp $(INC)
	$(CC) $(CFLAGS) -c conditionVariable.cpp

mutex.o: ../mutex/mutex.cpp
	$(CC) $(CFLAGS) -c ../mutex/mutex.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)