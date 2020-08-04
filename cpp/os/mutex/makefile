TARGET= threadMain.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../
INC= mutex.hpp ../uncopyable.hpp
OBJS= mutex.o mutexMain.o 

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

mutex.o: mutex.cpp $(INC)
	$(CC) $(CFLAGS) -c mutex.cpp

mutexMain.o: mutexMain.cpp
	$(CC) $(CFLAGS) -c mutexMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)