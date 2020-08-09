#comment
TARGET=CSQL
COMMAND=gcc
FLAGS= -g3 -ansi -pedantic  -Wall  -std=c99 
MYSQLCFLAGS = `mysql_config --cflags` 
MYSQLLIBS = `mysql_config --libs` 
all: $(TARGET).c
	@echo Compiling $(TARGET)
	@echo $(COMMAND) $(TARGET).c -o $(TARGET) $(MYSQLCFLAGS) $(FLAGS) $(MYSQLLIBS)
	@echo Compiling ...  
	$(COMMAND) $(TARGET).c -o $(TARGET) $(MYSQLCFLAGS) $(FLAGS) $(MYSQLLIBS)  
clean:
	rm $(TARGET) 


