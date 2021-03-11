# chatProject client makefile

TARGET= clientManager.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -I./DS/include/ -I./protocol/ -I./client/clientSocket/ -I./client/clientManager/ -I./client/openGroups/ -I./client/ui/ -D_POSIX_C_SOURCE
INC_MAKE= ./makeObj/
PRTCL= ./protocol/
CLNT_SOCK= ./client/clientSocket/
CLNT_MNGR= ./client/clientManager/
CLNT_GRP= ./client/openGroups/
CLNT_UI= ./client/ui/
DS_INC= ./DS/include/
DS_HM= ./DS/genHashMap/
DS_DLL= ./DS/genDLList/
OBJS= $(INC_MAKE)clientManagerMain.o $(INC_MAKE)clientManager.o $(INC_MAKE)socketClient.o $(INC_MAKE)clientGroups.o $(INC_MAKE)protocol.o $(INC_MAKE)ui.o $(INC_MAKE)genHashMap.o $(INC_MAKE)genDLList.o $(INC_MAKE)genDLListIterFunc.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

$(INC_MAKE)clientManagerMain.o: $(CLNT_MNGR)clientManagerMain.c $(CLNT_MNGR)clientManager.h
	$(CC) $(CFLAGS) -c $(CLNT_MNGR)clientManagerMain.c -o $(INC_MAKE)clientManagerMain.o

$(INC_MAKE)protocol.o: $(PRTCL)protocol.c $(PRTCL)protocol.h
	$(CC) $(CFLAGS) -c $(PRTCL)protocol.c -o $(INC_MAKE)protocol.o

$(INC_MAKE)socketClient.o: $(CLNT_SOCK)socketClient.c $(CLNT_SOCK)socketClient.h
	$(CC) $(CFLAGS) -c $(CLNT_SOCK)socketClient.c -o $(INC_MAKE)socketClient.o

$(INC_MAKE)clientManager.o: $(CLNT_MNGR)clientManager.c $(CLNT_SOCK)socketClient.h $(PRTCL)protocol.h  $(CLNT_UI)ui.h
	$(CC) $(CFLAGS) -c $(CLNT_MNGR)clientManager.c -o $(INC_MAKE)clientManager.o
    	
$(INC_MAKE)clientGroups.o: $(CLNT_GRP)clientGroups.c $(CLNT_GRP)clientGroups.h $(DS_INC)genHashMap.h $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(CLNT_GRP)clientGroups.c -o $(INC_MAKE)clientGroups.o

$(INC_MAKE)ui.o: $(CLNT_UI)ui.c $(CLNT_UI)ui.h
	$(CC) $(CFLAGS) -c $(CLNT_UI)ui.c -o $(INC_MAKE)ui.o
    	
$(INC_MAKE)genHashMap.o: $(DS_HM)genHashMap.c $(DS_INC)genHashMap.h $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_HM)genHashMap.c -o $(INC_MAKE)genHashMap.o
    	
$(INC_MAKE)genDLList.o: $(DS_DLL)genDLList.c $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_DLL)genDLList.c -o $(INC_MAKE)genDLList.o
    	
$(INC_MAKE)genDLListIterFunc.o: $(DS_DLL)genDLListIterFunc.c $(DS_INC)genDLListIterFunc.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_DLL)genDLListIterFunc.c -o $(INC_MAKE)genDLListIterFunc.o

clean:
	rm -f $(TARGET) $(OBJS)
