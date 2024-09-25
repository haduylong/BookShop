#pragma once
#include "init.h"

class Book {
private:
	int id;
	string name;
	string author;
	int price;
	int quantity;
public:
	Book();
	Book(string name, string author, int price, int quantity);
	~Book();
	void add(shared_ptr<sql::Connection> conn);
	void search_by_id(shared_ptr<sql::Connection> conn);
	void update_all(shared_ptr<sql::Connection> conn);
	void remove(shared_ptr<sql::Connection> conn);
	void search_all(shared_ptr<sql::Connection> conn);
	void update_price(shared_ptr<sql::Connection> conn);
};