
TARGET= memPageMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./
OBJS= memManager_t.o memPage_t.o memPool_t.o memPageMain.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
memManager_t.o: memManager_t.cpp memManager_t.h
	$(CC) $(CFLAGS) -c memManager_t.cpp
	
memPage_t.o: memPage_t.cpp memPage_t.h
	$(CC) $(CFLAGS) -c memPage_t.cpp
	
memPool_t.o: memPool_t.cpp memPool_t.h
	$(CC) $(CFLAGS) -c memPool_t.cpp
	
memPageMain.o: memPageMain.cpp
	$(CC) $(CFLAGS) -c memPageMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
