#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void) {
  cout << "Running 'SELECT * FROM employees.employees LIMIT 10'" << endl;
  try {
    sql::Driver *driver;
    driver = get_driver_instance();

    sql::Connection* con;
    con = driver->connect("localhost", "maayan", "123456"); // tcp: // 127.0.0.1:3306
    cout << "con->isValid: " << con->isValid() << endl;
    cout << "con->getClientInfo: " << con->getClientInfo() << endl;

    con->setSchema("employees");
    sql::Statement* stmt;
    stmt = con->createStatement();
    sql::ResultSet* res;
    res = stmt->executeQuery("SELECT * FROM employees.employees LIMIT 10;");
    cout << "res->rowsCount: " << res->rowsCount() << endl;
    int numOfCol = res->getMetaData()->getColumnCount();
    cout << "number of columns: " << numOfCol << endl;
    while(res->next()) {
      cout << "*";
      cout << res->getRow();
      for (int i = 1; i <= numOfCol; ++i) {
        cout << " : " << res->getString(i);
      }
      cout << "*" << endl;
    }
    delete res;
    delete stmt;
    delete con; // delete driver
  }
  catch (sql::SQLException &e) {
		cout << "***** Error: " << e.what();
		cout << "MySQL code: " << e.getErrorCode();
		cout << "SQLState: " << e.getSQLState() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
