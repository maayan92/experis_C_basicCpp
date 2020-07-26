TARGET= main.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= operator.h add.h mul.h number.h exprTree.h
OBJS= number.o add.o mul.o operator.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

operator.o: operator.cpp $(INC)
	$(CC) $(CFLAGS) -c operator.cpp

exprTree.o: exprTree.cpp 
	$(CC) $(CFLAGS) -c exprTree.cpp

number.o: number.cpp
	$(CC) $(CFLAGS) -c number.cpp

add.o: add.cpp
	$(CC) $(CFLAGS) -c add.cpp

mul.o: mul.cpp
	$(CC) $(CFLAGS) -c mul.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)