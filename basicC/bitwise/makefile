# makefile sample

TARGET= bitwiseMain.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror
INC= ../../include
OBJS= bitWise.o bitwiseMain.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
bitWise.o: bitWise.c $(INC)
	$(CC) $(CFLAGS) -c bitWise.c

bitwiseMain.o: bitwiseMain.c
	$(CC) $(CFLAGS) -c bitwiseMain.c

clean:
	rm -f $(TARGET) $(OBJS)
