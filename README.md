# cpp-mysql-cppconn
c++ with mysql cppconn

## install deb dependencies for ubuntu 20.04
https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-community-client-plugins_8.0.29-1ubuntu20.04_amd64.deb

https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn9_8.0.29-1ubuntu20.04_amd64.deb

https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn8-2_8.0.29-1ubuntu20.04_amd64.deb

https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.29-1ubuntu20.04_amd64.deb


## includes 
* #include <mysql-cppconn-8/jdbc/mysql_connection.h>
* #include <mysql-cppconn-8/jdbc/mysql_driver.h>
* #include <mysql-cppconn-8/jdbc/cppconn/exception.h>
* #include <mysql-cppconn-8/jdbc/cppconn/statement.h>
* #include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>

## link option
Linker option:  /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so
