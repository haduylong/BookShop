#pragma once
#include "init.h"

class Purchase {
private:
	int ord_id;
	int book_id;
	int sup_id;	// supplier id
	int quantity;
	date date_order;
	int estimation;	// estimated expected delivery by day
	char received;	// 'T', 'C', 'F' (true, cancel, false)
	int inv;
public:
	Purchase();
	Purchase(int, int, int, date, int, char, int);
	~Purchase();
	void add_order(shared_ptr<sql::Connection> conn);
	void view(shared_ptr<sql::Connection> conn);
	void mark_cancel(shared_ptr<sql::Connection> conn);
	void mark_received(shared_ptr<sql::Connection> conn);
};