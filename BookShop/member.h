#pragma once
#include "init.h"

class Member {
private:
	int id;
	string name;
	string addr_line1;
	string addr_line2;
	string addr_city;
	string phone;
	date begin_date;
	date end_date;
	string valid;
public:
	Member();
	Member(string, string, string, string, string, date, date, string);
	~Member();
	void add_member(shared_ptr<sql::Connection> conn);
	void refresh(shared_ptr<sql::Connection> conn);
	void search_by_id(shared_ptr<sql::Connection> conn);
};