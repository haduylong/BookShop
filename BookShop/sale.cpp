#include "sale.h"

Sale::Sale() {};
Sale::Sale(int member_id, int book_id, int quantity, int amount, date date_s) {

};
Sale::~Sale() {};

void Sale::add_sale(shared_ptr<sql::Connection> conn) {
	cout << "Enter Menber id : ";
	cin >> member_id;
	cout << "Enter the book id : ";
	cin >> book_id;
	cout << "Enter the quantity : ";
	cin >> quantity; cin.ignore();

	// total cost = price * quantity
	string query = "SELECT price*? FROM books WHERE id=?;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, quantity);
	ps_stmt->setInt(2, book_id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		cout << "The bill amount: " << res->getInt(1) << endl;
		amount = res->getInt(1);
	}
	else {
		cout << endl << "Book Id may be wrong!" << endl << endl;
		return;
	}
	// add sale
	query = "INSERT INTO sales (member_id, book_id, quantity, amount, date_s) \
		VALUES (?, ?, ?, ?, CURDATE());";
	ps_stmt.reset(conn->prepareStatement(query));
	ps_stmt->setInt(1, member_id);
	ps_stmt->setInt(2, book_id);
	ps_stmt->setInt(3, quantity);
	ps_stmt->setInt(4, amount);
	int res_insert = ps_stmt->executeUpdate();
	if (res_insert)
		cout << endl << "Insert Sale successfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR!" << endl << endl;
};

void Sale::search_total_sale(shared_ptr<sql::Connection> conn) {
	string query = "SELECT SUM(amount) FROM sales WHERE YEAR(date_s) = YEAR(CURDATE());";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		cout << endl << "Total sale of this year: " << res->getInt(1) << endl << endl;
	}
	else {
		cout << endl << "Entry ERROR!" << endl << endl;
	}
};

void sale_menu(shared_ptr<sql::Connection> conn) {
	Sale sale;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Sale Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD SALE" << endl;
		cout << "   2. TOTAL SALE" << endl;
		cout << "   3. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
		case 1: sale.add_sale(conn); break;
		case 2: sale.search_total_sale(conn); break;
		case 3: return;
		default: cout << endl << "Invalid input" << endl; break;
		}
	}
}