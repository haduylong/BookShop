#pragma once
/* Standard C++ include */
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <vector>
/* MySQL include */
/* note: mysql_driver.h is for mysql; cppconn/driver.h is for general */
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h> 
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

typedef struct {
	int date;
	int month;
	int year;
} date;

void main_menu(shared_ptr<sql::Connection> conn);
void book_menu(shared_ptr<sql::Connection> conn);
void supplier_menu(shared_ptr<sql::Connection> conn);
void purchase_menu(shared_ptr<sql::Connection> conn);
void employee_menu(shared_ptr<sql::Connection> conn);
void member_menu(shared_ptr<sql::Connection> conn);
void sale_menu(shared_ptr<sql::Connection> conn);