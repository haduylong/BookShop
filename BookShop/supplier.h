#pragma once
#include "init.h"

class Supplier {
private:
	int id;
	string name;
	string phone;
	string addr_line1;
	string addr_line2;
	string addr_city;
public:
	Supplier();
	Supplier(string, string, string, string, string);
	~Supplier();
	void add_supplier(shared_ptr<sql::Connection> conn);
	void remove_supplier(shared_ptr<sql::Connection> conn);
	void search_by_id(shared_ptr<sql::Connection> conn);
};