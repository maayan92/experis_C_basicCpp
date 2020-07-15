
TARGET= compilerMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= analyzer.h tokenizer.h compiler.h
OBJS= tokenizer.o analyzer.o compiler.o compilerMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

compiler.o: compiler.cpp $(INC)
	$(CC) $(CFLAGS) -c compiler.cpp
	
tokenizer.o: tokenizer.cpp 
	$(CC) $(CFLAGS) -c tokenizer.cpp
	
analyzer.o: analyzer.cpp 
	$(CC) $(CFLAGS) -c analyzer.cpp
	
compilerMain.o: compilerMain.cpp 
	$(CC) $(CFLAGS) -c compilerMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
