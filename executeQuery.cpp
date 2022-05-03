#include <iostream>
#include <fstream>
#include<string>
#include<list>
#include <mysql-cppconn-8/jdbc/mysql_connection.h>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/exception.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>
using namespace std;

void listCountries(){
    try {
      sql::mysql::MySQL_Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::ResultSet  *res;
      driver = sql::mysql::get_driver_instance();
      con = driver->connect("tcp://127.0.0.1:3306", "adm", "*Benfica22*");
      stmt = con->createStatement();
      con->setSchema("ports");
      res=stmt->executeQuery("SELECT * FROM countries");
      while (res->next()) {
      // You can use either numeric offsets...
        cout << "ID = " << res->getInt(1);
        cout << ", Country = '" << res->getString("country") << "'";
        cout << ", Code = '" << res->getString("code") << "'" << endl;
      }
      delete res;
      delete stmt;
      delete con;
    } catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}
int main () {
    listCountries();
    return EXIT_SUCCESS;
}
