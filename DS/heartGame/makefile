# makefile sample

TARGET= heartGameMain.out 
CC= gcc -I../../include
CFLAGS= -ansi -g -pedantic -Wall
OBJS= heartGame.o player.o round.o deck.o ui.o heartGameMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
		
heartGame.o: heartGame.c heartGame.h 
	$(CC) $(CFLAGS) -c heartGame.c

heartGameMain.o: heartGameMain.c
	$(CC) $(CFLAGS) -c heartGameMain.c

	
player.o: player.c player.h 
	$(CC) $(CFLAGS) -c player.c

round.o: round.c round.h
	$(CC) $(CFLAGS) -c round.c

deck.o: deck.c deck.h card.h
	$(CC) $(CFLAGS) -c deck.c

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c
	
clean:
	rm -f $(TARGET) $(OBJS)
