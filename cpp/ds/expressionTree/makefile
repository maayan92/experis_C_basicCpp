TARGET= main.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= operator.h add.h number.h exprTree.h
OBJS= number.o add.o mul.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

number.o: number.cpp $(INC)
	$(CC) $(CFLAGS) -c number.cpp

add.o: add.cpp $(INC)
	$(CC) $(CFLAGS) -c add.cpp

mul.o: mul.cpp $(INC)
	$(CC) $(CFLAGS) -c mul.cpp

main.o: main.cpp $(INC)
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)