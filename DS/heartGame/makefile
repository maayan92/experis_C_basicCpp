# makefile sample

TARGET= heartGameUnitTest.out 
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall
OBJS= heartGame.o player.o round.o deck.o ui.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heartGame.o: heartGame.c heartGame.h heartGameUnitTest.c
	$(CC) $(CFLAGS) -c heartGame.c
	
player.o: player.c player.h playerUnitTest.c
	$(CC) $(CFLAGS) -c player.c

round.o: round.c round.h roundUnitTest.c
	$(CC) $(CFLAGS) -c round.c

deck.o: deck.c deck.h card.h deckUnitTest.c
	$(CC) $(CFLAGS) -c deck.c

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c
	
clean:
	rm -f $(TARGET) $(OBJS)
