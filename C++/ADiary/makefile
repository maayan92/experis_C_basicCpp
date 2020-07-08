
TARGET= ADiaryMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ -I../TException -I../String
INC= ADiary.h meeting.h ../TException/TException.h
OBJS= ../String/String_t.cpp ADiaryMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

ADiaryMain.o: ADiaryMain.cpp $(INC)
	$(CC) $(CFLAGS) -c ADiaryMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
