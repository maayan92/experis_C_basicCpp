
TARGET= String_tMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -std=c++11
INC= String_t.h 
OBJS=  String_t.o String_tMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

String_t.o: String_t.cpp $(INC)
	$(CC) $(CFLAGS) -c String_t.cpp

String_tMain.o: String_tMain.cpp $(INC)
	$(CC) $(CFLAGS) -c String_tMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
