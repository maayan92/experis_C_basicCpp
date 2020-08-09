#comment
TARGET=CppSQL
COMMAND=g++
FLAGS= -g3 -ansi -pedantic  -Wall -Werror -std=c++03 
MYSQLCFLAGS = `mysql_config --cxxflags` 
MYSQLLIBS = -L/usr/lib/x86_64-linux-gnu  -lmysqlcppconn -lpthread -lz -lm -lrt -latomic -ldl 
all: $(TARGET).cpp
	@echo Compilimg $(TARGET)
	@echo $(COMMAND) $(TARGET).cpp -o $(TARGET) $(MYSQLCFLAGS) $(FLAGS) $(MYSQLLIBS)
	@echo Compiling ...  
	$(COMMAND) $(TARGET).cpp -o $(TARGET) $(MYSQLCFLAGS) $(FLAGS) $(MYSQLLIBS)  
clean:
	rm $(TARGET) 

