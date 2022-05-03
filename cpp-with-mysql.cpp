// Linker option:  /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so
#include <iostream>
#include <fstream>
#include<string>
#include<list>
#include <mysql-cppconn-8/jdbc/mysql_connection.h>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/exception.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
using namespace std;
class Port {
  private:
    string port;
    string region;
    string countryCode;
    string country;
  public:
    void setPort(string p)
      { port=p;}
    string getPort()
      { return port;}
    void setRegion(string r)
      { region=r;}
    string getRegion()
      { return region;}
    void setCountryCode(string cc)
      { countryCode=cc;}
    string getCountryCode()
      { return countryCode;}
    void setCountry(string c)
      { country=c;}
    string getCountry()
      { return country;}
    void getDetails(){
        cout<<"Port: "<<port<<endl;
        cout<<"Region: "<<region<<endl;
        cout<<"Country Code: "<<countryCode<<endl;
        cout<<"Country: "<<country<<endl;
    }
 };
void CreateDatabase(list<Port>& ports){
    try {
      sql::mysql::MySQL_Driver *driver;
      sql::Connection *con;
      sql::Statement *stmt;
      sql::PreparedStatement  *prep_stmt;
      driver = sql::mysql::get_driver_instance();
      con = driver->connect("tcp://127.0.0.1:3306", "adm", "*Benfica22*");
      stmt = con->createStatement();
      stmt->executeUpdate("DROP DATABASE IF EXISTS ports");
      stmt->executeUpdate("CREATE DATABASE ports");
      con->setSchema("ports");
      stmt->executeUpdate("create table countries(id int auto_increment,country varchar(60) not null,code varchar(2),primary key(id))");
      stmt->executeUpdate("create table regions(id int auto_increment,region varchar(60) not null,country_id int,primary key(id),foreign key(country_id) references countries(id))");
      stmt->executeUpdate("create table ports(id int auto_increment,port varchar(60) not null,region_id int,primary key(id),foreign key(region_id) references regions(id))");
      stmt->executeUpdate("create table tmp(port varchar(60),region varchar(60),code varchar(2),country varchar(60))");
      for(Port p : ports){
        prep_stmt = con->prepareStatement("INSERT INTO tmp(port, region,code,country) VALUES(?,?,?,?)");
        prep_stmt->setString(1,p.getPort());
        prep_stmt->setString(2,p.getRegion());
        prep_stmt->setString(3,p.getCountryCode());
        prep_stmt->setString(4,p.getCountry());
        prep_stmt->execute();
      }
      stmt->executeUpdate("insert into countries(country,code) select distinct country,code from tmp order by country");
      stmt->executeUpdate("insert into regions(region,country_id) select distinct region,id from tmp t inner join countries c on t.country=c.country order by id,region");
      stmt->executeUpdate("insert into ports(port,region_id) select distinct port,id from tmp t inner join regions r on t.region=r.region order by id,port");
      stmt->executeUpdate("drop table tmp");
      delete stmt;
      delete prep_stmt;
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
    list<Port> ports;
    Port port;
    string line,file="ports.csv";
    ifstream myfile (file);
    if (myfile.is_open())
    {
        cout<<"Reading from file "<<file<<"..."<<endl;
        while (myfile)
        {
            getline (myfile,line,';');
            port.setPort(line);
            getline (myfile,line,';');
            port.setRegion(line);
            getline (myfile,line,';');
            port.setCountryCode(line);
            getline (myfile,line,'\n');
            port.setCountry(line);
            if(myfile.eof()) break;
            ports.push_back(port);
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    cout<<"Creating Database "<<file.substr(0,file.length()-4)<<"..."<<endl;
    //for(Port p : ports) p.getDetails();
    CreateDatabase(ports);
    cout<<"Done!"<<endl;
    return EXIT_SUCCESS;
}
