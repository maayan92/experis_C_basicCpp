TARGET= main.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= manipulator.hpp tolower.hpp toupper.hpp manipulatorHandler.hpp tokenizer.hpp
OBJS= tms.o manipulatorHandler.o manipulator.o tokenizer.o tolower.o toupper.o main.o

$(TARGET): $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS)

tms.o: tms.cpp $(INC)
	$(CC) $(CFLAGS) -c tms.cpp

manipulatorHandler.o: manipulatorHandler.cpp $(INC)
	$(CC) $(CFLAGS) -c manipulatorHandler.cpp

manipulator.o: manipulator.cpp 
	$(CC) $(CFLAGS) -c manipulator.cpp

tokenizer.o: tokenizer.cpp 
	$(CC) $(CFLAGS) -c tokenizer.cpp

tolower.o: tolower.cpp
	$(CC) $(CFLAGS) -c tolower.cpp

toupper.o: toupper.cpp
	$(CC) $(CFLAGS) -c toupper.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

test.o: test.cpp $(INC)
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f $(TARGET) $(OBJS)