TARGET= main.out
CC= g++ 
MTX= ../../mutex/
CFLAGS= -ansi -pedantic -g -I../../ -I../ -I$(MTX)
INC= cyclicQueueMT.hpp ../../uncopyable.hpp $(MTX)mutex.hpp ../mutexLocker.hpp ../conditionVariable.hpp
OBJS= conditionVariable.o mutex.o main.o

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

conditionVariable.o: ../conditionVariable.cpp $(INC)
	$(CC) $(CFLAGS) -c ../conditionVariable.cpp

mutex.o: $(MTX)mutex.cpp
	$(CC) $(CFLAGS) -c $(MTX)mutex.cpp

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)