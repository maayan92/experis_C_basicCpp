# chatProject makefile

INC_MAKE= ./makeObj/

all: serverManager.out clientManager.out chatRead.out chatWrite.out

serverManager.out:
	make -f $(INC_MAKE)makeServer.mk

clientManager.out:
	make -f $(INC_MAKE)makeClient.mk

chatRead.out:
	make -f $(INC_MAKE)makeChatRead.mk

chatWrite.out:
	make -f $(INC_MAKE)makeChatWrite.mk

clean:
	rm $(INC_MAKE)*.o *.out
