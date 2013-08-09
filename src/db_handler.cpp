#include <iostream>
#include "db_handler.h"
#include <mysql.h>
#include <my_global.h>

using namespace std;

void SDBHandler::find_peer_address() {
	
}

int SDBHandler::add_peer_address() {

}

int SDBHandler::connect_to_db() {
	MYSQL *con;
	con = mysql_init(NULL);
	if(!con) {
		cout <<" Connect failed"<<endl;
	}
	 if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "password", 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

  if (mysql_query(con, "CREATE DATABASE testdb")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  mysql_close(con);
	return 0;
}


