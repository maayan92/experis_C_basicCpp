TARGET= threadMain.out
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../
INC= runnable.hpp thread.hpp ../uncopyable.hpp
OBJS= thread.o threadMain.o 

$(TARGET): $(OBJS)  
	$(CC) -o $(TARGET) $(OBJS) -lpthread

thread.o: thread.cpp $(INC)
	$(CC) $(CFLAGS) -c thread.cpp

threadMain.o: threadMain.cpp
	$(CC) $(CFLAGS) -c threadMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)