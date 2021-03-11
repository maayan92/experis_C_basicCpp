# chatProject server makefile

TARGET= serverManager.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -I./DS/include/ -I./protocol/ -I./server/serverSocket/ -I./server/serverManager/ -I./server/usersDB/ -I./server/groupsDB/ -I./server/groupsDB/ipPool/
INC_MAKE= ./makeObj/
PRTCL= ./protocol/
SRVR_USR_DB= ./server/usersDB/
SRVR_SOCK= ./server/serverSocket/
SRVR_MNGR= ./server/serverManager/
SRVR_GRP_DB= ./server/groupsDB/
SRVR_GRP_DB_IP_POOL= ./server/groupsDB/ipPool/
DS_INC= ./DS/include/
DS_HM= ./DS/genHashMap/
DS_DLL= ./DS/genDLList/
OBJS= $(INC_MAKE)serverManagerMain.o $(INC_MAKE)serverManager.o $(INC_MAKE)socketServerSelect.o $(INC_MAKE)usersDataBase.o $(INC_MAKE)groupsDB.o $(INC_MAKE)ipPool.o $(INC_MAKE)protocol.o $(INC_MAKE)genHashMap.o $(INC_MAKE)genDLList.o $(INC_MAKE)genDLListIterFunc.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

$(INC_MAKE)serverManagerMain.o: $(SRVR_MNGR)serverManagerMain.c $(SRVR_MNGR)serverManager.h
	$(CC) $(CFLAGS) -c $(SRVR_MNGR)serverManagerMain.c -o $(INC_MAKE)serverManagerMain.o

$(INC_MAKE)protocol.o: $(PRTCL)protocol.c $(PRTCL)protocol.h
	$(CC) $(CFLAGS) -c $(PRTCL)protocol.c -o $(INC_MAKE)protocol.o

$(INC_MAKE)socketServerSelect.o: $(SRVR_SOCK)socketServerSelect.c $(SRVR_SOCK)socketServerSelect.h $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(SRVR_SOCK)socketServerSelect.c -o $(INC_MAKE)socketServerSelect.o

$(INC_MAKE)serverManager.o: $(SRVR_MNGR)serverManager.c $(SRVR_SOCK)socketServerSelect.h $(PRTCL)protocol.h $(SRVR_USR_DB)usersDataBase.h $(SRVR_GRP_DB)groupsDB.h
	$(CC) $(CFLAGS) -c $(SRVR_MNGR)serverManager.c -o $(INC_MAKE)serverManager.o

$(INC_MAKE)usersDataBase.o: $(SRVR_USR_DB)usersDataBase.c $(SRVR_USR_DB)usersDataBase.h $(DS_INC)genHashMap.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(SRVR_USR_DB)usersDataBase.c -o $(INC_MAKE)usersDataBase.o

$(INC_MAKE)groupsDB.o: $(SRVR_GRP_DB)groupsDB.c $(SRVR_GRP_DB)groupsDB.h $(SRVR_GRP_DB_IP_POOL)ipPool.h $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)genHashMap.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(SRVR_GRP_DB)groupsDB.c -o $(INC_MAKE)groupsDB.o

$(INC_MAKE)ipPool.o: $(SRVR_GRP_DB_IP_POOL)ipPool.c $(SRVR_GRP_DB_IP_POOL)ipPool.h $(DS_INC)genDLList.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(SRVR_GRP_DB_IP_POOL)ipPool.c -o $(INC_MAKE)ipPool.o
    	
$(INC_MAKE)genHashMap.o: $(DS_HM)genHashMap.c $(DS_INC)genHashMap.h $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_HM)genHashMap.c -o $(INC_MAKE)genHashMap.o
    	
$(INC_MAKE)genDLList.o: $(DS_DLL)genDLList.c $(DS_INC)genDLList.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_DLL)genDLList.c -o $(INC_MAKE)genDLList.o
    	
$(INC_MAKE)genDLListIterFunc.o: $(DS_DLL)genDLListIterFunc.c $(DS_INC)genDLListIterFunc.h $(DS_INC)genDLListIter.h $(DS_INC)ADTerror.h
	$(CC) $(CFLAGS) -c $(DS_DLL)genDLListIterFunc.c -o $(INC_MAKE)genDLListIterFunc.o

clean:
	rm -f $(TARGET) $(OBJS)



