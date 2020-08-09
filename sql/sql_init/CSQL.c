#include <stdio.h>
#include <mysql/mysql.h>
int main ()
{
	MYSQL * MySql, *Retval;
	int Retvali;
	char *str = "select * from employees.employees limit 20";
	MYSQL_RES *result;
	unsigned int numberOfColumns;
	my_ulonglong numberOfRows;
	MYSQL_FIELD *field;
	MYSQL_ROW row;

/// connect:

	puts("Starting program");
	MySql = mysql_init(NULL);
	if (NULL == MySql) {
      	fprintf(stderr, "error connecting to mysql errno: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql));
     	exit(1);
  	} else {
		puts("mysql_init Succedded");
	}
	Retval = mysql_real_connect(MySql, "localhost", "maayan", "123456", "myDB", 0, NULL, 0);
	if(NULL == Retval) {
		fprintf(stderr, "mysql_real_connect failed error: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql));
		mysql_close(MySql);
     	exit(1);
  	} else {
		puts("mysql_real_connect Succedded");
	}

/// query:

	Retvali = mysql_query(MySql, str);
	if(0 != Retvali) {
		fprintf(stderr, "mysql_query failed error: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql));
		mysql_close(MySql);
     	exit(1);
  	} else {
		puts("mysql_query Succedded");
	}

	result = mysql_store_result(MySql);
	if(NULL == result && (mysql_errno(MySql) != 0)) {
		fprintf(stderr, "mysql_store_result failed error: %d Msg: %s\n", mysql_errno(MySql), mysql_error(MySql));
		mysql_close(MySql);
     	exit(1);
	} else {
		puts("mysql_store_result Succedded");
	}
	if(NULL == result) {
		puts("Result is NULL\n");
	} else {
		numberOfColumns = mysql_num_fields(result);
		numberOfRows = mysql_num_rows(result);
		printf("Number of columns %d number of rows %lld\n", numberOfColumns, numberOfRows);

		printf(":"); 
		for (int i = 0; i < numberOfColumns; ++i) {
			field = mysql_fetch_field(result);
			printf(" %s :", field->name);
		}
		printf("\n");
		for (int i = 0; i < numberOfRows; ++i) {
			row = mysql_fetch_row(result);
			printf(":");
			for (int j = 0; j < numberOfColumns; ++j) {
				printf(" %s :", row[j]);
			}
			printf("\n");
		}
	}

	mysql_free_result(result);
  	mysql_close(MySql);
	puts("Press enter to terminate");
	getchar();
	return(0);
}