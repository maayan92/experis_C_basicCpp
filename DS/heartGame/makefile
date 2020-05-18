# makefile sample

TARGET= heartGameMain.out 
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= heartGame.o player.o round.o deck.o ui.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heartGame.o: heartGame.c heartGame.h heartGameMain.c
	$(CC) $(CFLAGS) -c heartGame.c
	
player.o: player.c player.h 
	$(CC) $(CFLAGS) -c player.c

round.o: round.c round.h
	$(CC) $(CFLAGS) -c round.c

deck.o: deck.c deck.h card.h
	$(CC) $(CFLAGS) -c deck.c

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c
	
ADTErrors.o:  ADTErrors.h
	$(CC) $(CFLAGS) -c -I../../include
	
clean:
	rm -f $(TARGET) $(OBJS)
