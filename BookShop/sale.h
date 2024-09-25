#pragma once
#include "init.h"

class Sale {
private:
	int invoice_id;
	int member_id;
	int book_id;
	int quantity;
	int amount;
	date date_s;
public:
	Sale();
	Sale(int, int, int, int, date);
	~Sale();
	void add_sale(shared_ptr<sql::Connection> conn);
	void search_total_sale(shared_ptr<sql::Connection> conn);
};