
TARGET= graphMain.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I./ 
INC= graph.h vertex.h path.h
OBJS= vertex.o graph.o path.o graphMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

graph.o: graph.cpp $(INC)
	$(CC) $(CFLAGS) -c graph.cpp
	
vertex.o: vertex.cpp $(INC)
	$(CC) $(CFLAGS) -c vertex.cpp

path.o: path.cpp $(INC)
	$(CC) $(CFLAGS) -c path.cpp
		
graphMain.o: graphMain.cpp $(INC)
	$(CC) $(CFLAGS) -c graphMain.cpp

clean:
	rm -f $(TARGET) $(OBJS)
