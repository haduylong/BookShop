#pragma once
#include "init.h"

class Employee {
private:
	int id;
	string name;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string phone;
	date date_of_joining;
	long salary;
	string manager_status;
public:
	Employee();
	Employee(string, string, string, string, string, date, long, string);
	~Employee();
	void add_employee(shared_ptr<sql::Connection> conn);
	void search_by_id(shared_ptr<sql::Connection> conn);
	void assign_manager_status(shared_ptr<sql::Connection> conn);
	void search_all(shared_ptr<sql::Connection> conn);
	void update_salary(shared_ptr<sql::Connection> conn);
};