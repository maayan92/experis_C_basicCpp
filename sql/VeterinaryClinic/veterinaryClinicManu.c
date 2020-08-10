#include <stdio.h>
#include <mysql/mysql.h>

#define LENGTH 200

enum{
    OWNERS_LIST = 1,
    PETS_LIST,
    ADD_OWNER,
    ADD_PET,
    DELETE_OWNER,
    DELETE_PET,
    FIND_OWNER,
    FIND_PET,
    UPDATE_OWNER,
    UPDATE_PET,
    OWNERS_THEIR_PETS,
    EXIT
};

typedef enum { false, true } bool;

static void PrintError(MYSQL* a_mysql, const char* a_failedFunc) {
    fprintf(stderr, "%s, errno: %d Msg: %s\n", a_failedFunc, mysql_errno(a_mysql), mysql_error(a_mysql));
    mysql_close(a_mysql);
    printf("\n");
}

static MYSQL* ConnectToDB(const char* a_dbName) {
    MYSQL* mySqlInit, *mySqlConnect;

    mySqlInit = mysql_init(NULL);
	if (NULL == mySqlInit) {
        PrintError(mySqlInit, "mysql_init");
     	return NULL;
  	}
	mySqlConnect = mysql_real_connect(mySqlInit, "localhost", "maayan", "123456", a_dbName, 0, NULL, 0);
	if(NULL == mySqlConnect) {
        PrintError(mySqlInit, "mysql_real_connect");
     	return NULL;
  	}

    return mySqlInit;
}

static bool SetQuery(MYSQL* a_mysql, const char* a_query) {
    int retvali = mysql_query(a_mysql, a_query);
    if(0 != retvali) {
        PrintError(a_mysql, "mysql_query");
        return false;
    }
    return true;
}

static MYSQL_RES* GetQueryResult(MYSQL* a_mysql) {
    MYSQL_RES* result = mysql_store_result(a_mysql);
	if(NULL == result && (mysql_errno(a_mysql) != 0)) {
        PrintError(a_mysql, "mysql_store_result");
        return NULL;
    }
    return result;
}

static void PrintResult(MYSQL_RES *a_result) {
	MYSQL_FIELD *field;
	MYSQL_ROW row;
    unsigned int numberOfColumns = mysql_num_fields(a_result);
    my_ulonglong numberOfRows = mysql_num_rows(a_result);

    for (int i = 0; i < numberOfColumns; ++i) {
        field = mysql_fetch_field(a_result);
        printf("\033[1;31m| %-10s", field->name);
    }
    printf("\033[0m\n");
    for (int i = 0; i < numberOfRows; ++i) {
        row = mysql_fetch_row(a_result);
        for (int j = 0; j < numberOfColumns; ++j) {
            printf("| %-10s", row[j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int action, ownerId, petId;
    char name[LENGTH], query[LENGTH];
    bool queryResult;
    MYSQL_RES* result;
    MYSQL* mySql = ConnectToDB("veterinaryClinic");
    if(!mySql) {
        return 1;
    }
    
    do {
        printf("choose action:\n");
        printf("1 - to get owner's list \n2 - to get pet's list with owner's name\n");
        printf("3 - to add owner \n4 - to add pet \n5 - to delete owner\n");
        printf("6 - to delete pet \n7 - to find owner \n8 - to find pet\n");
        printf("9 - to update owner \n10 - to update pet\n");
        printf("11 - to get list of owners and their pets ordered by number of pets\n");
        scanf("%d", &action);
        getchar();
        printf("\n");

        switch(action) {
            case OWNERS_LIST:
                queryResult = SetQuery(mySql, "select * from owners;");
                break;

            case PETS_LIST:
                queryResult = SetQuery(mySql, "select pets.petId, pets.petName, owners.ownerName \
                                                    from pets join owners on (pets.ownerId = owners.ownerId);");
                break;
            
            case ADD_OWNER:
                printf("insert owner's id:");
                scanf("%d", &ownerId);
                printf("insert owner's name:");
                scanf("%s", name);
                
                sprintf(query, "insert owners(ownerId, ownerName) values(%d, '%s');", ownerId, name); 
                queryResult = SetQuery(mySql, query);
                break;

            case ADD_PET:
                printf("insert pet's id:");
                scanf("%d", &petId);
                printf("insert pet's name:");
                scanf("%s", name);
                printf("insert owner's id:");
                scanf("%d", &ownerId);

                sprintf(query, "insert pets(petId, petName, ownerId) values(%d, '%s', %d);", petId, name, ownerId); 
                queryResult = SetQuery(mySql, query);
                break;
            
            case DELETE_OWNER:
                printf("insert owner's id:");
                scanf("%d", &ownerId);

                sprintf(query, "delete from owners where ownerId = %d);", ownerId); 
                queryResult = SetQuery(mySql, query);
                break;

            case DELETE_PET:
                printf("insert pet's id:");
                scanf("%d", &petId);

                sprintf(query, "delete from pets where petId = %d);", petId); 
                queryResult = SetQuery(mySql, query);
                break;
            
            case FIND_OWNER:
                printf("insert owner's id:");
                scanf("%d", &ownerId);

                sprintf(query, "select * from owners where ownerId = %d;", ownerId);
                queryResult = SetQuery(mySql, query);
                break;

            case FIND_PET:
                printf("insert pet's id:");
                scanf("%d", &petId);

                sprintf(query, "select * from pets where petId = %d;", petId);
                queryResult = SetQuery(mySql, query);
                break;
            
            case UPDATE_OWNER:
                printf("insert owner's id:");
                scanf("%d", &ownerId);
                printf("new values: \ninsert owner's name:");
                scanf("%s", name);

                sprintf(query, "update owners set ownerName = '%s' where ownerId = %d;",name, ownerId); 
                queryResult = SetQuery(mySql, query);
                break;

            case UPDATE_PET:
                printf("insert pet's id:");
                scanf("%d", &petId);
                printf("new values: \ninsert pet's name:");
                scanf("%s", name);
                printf("insert owner's id:");
                scanf("%d", &ownerId);

                sprintf(query, "update pets set petName = '%s', ownerId = %d where petId = %d;",name, ownerId, petId); 
                queryResult = SetQuery(mySql, query);
                break;

            case OWNERS_THEIR_PETS:
                queryResult = SetQuery(mySql, "select owners.*, JSON_ARRAYAGG(pets.petName) as `owner's pets` \
                                                    from owners join pets on pets.ownerId=owners.ownerId \
                                                    group by owners.ownerId \
                                                    order by count(pets.ownerId);");
                break;

            default:
                action = EXIT;
                break;
        }
        if(action != EXIT && queryResult) { 
            result = GetQueryResult(mySql);
            if(result) { 
                PrintResult(result);
            }
            mysql_free_result(result);
        }
    } while(action != EXIT);
    mysql_close(mySql);
}