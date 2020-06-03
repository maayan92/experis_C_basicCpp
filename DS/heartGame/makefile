# makefile sample

TARGET= heartGameMain.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall -Werror 
INC= ../../include
OBJS= heartGame.o player.o round.o deck.o ui.o heartGameMain.o log.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heartGame.o: heartGame.c $(INC)
	$(CC) $(CFLAGS) -c heartGame.c

heartGameMain.o: heartGameMain.c
	$(CC) $(CFLAGS) -c heartGameMain.c

	
player.o: player.c
	$(CC) $(CFLAGS) -c player.c

round.o: round.c 
	$(CC) $(CFLAGS) -c round.c

deck.o: deck.c
	$(CC) $(CFLAGS) -c deck.c

ui.o: ui.c
	$(CC) $(CFLAGS) -c ui.c

log.o: log.c
	$(CC) $(CFLAGS) -c log.c
	
clean:
	rm -f $(TARGET) $(OBJS)
