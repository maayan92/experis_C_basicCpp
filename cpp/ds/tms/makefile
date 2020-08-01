TARGET= tokenizerTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= manipulator.hpp tolower.hpp toupper.hpp manipulatorHandler.hpp tokenizer.hpp
OBJS= manipulatorHandler.o manipulator.o tokenizer.o tolower.o toupper.o tokenizerTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

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

tokenizerTest.o: tokenizerTest.cpp
	$(CC) $(CFLAGS) -c tokenizerTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)