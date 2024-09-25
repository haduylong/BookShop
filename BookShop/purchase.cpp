#include "purchase.h"

Purchase::Purchase() {};
Purchase::Purchase(int book_id, int sup_id, int quantity, date date_order,
				int estimation, char received, int inv) {
	this->book_id = book_id;
	this->sup_id = sup_id;
	this->quantity = quantity;
	this->date_order = date_order;
	this->estimation = estimation;
	this->received = received;
	this->inv = inv;
}
Purchase::~Purchase() {};

void Purchase::add_order(shared_ptr<sql::Connection> conn) {
	cout << "Enter the book Id : ";
	cin >> book_id;
	cout << "Enter Supplier Id : ";
	cin >> sup_id;
	cout << "Enter the Quantity : ";
	cin >> quantity;
	cout << "Estimated expected Delivery (in days) : ";
	cin >> estimation;
	cin.ignore();

	string query = "INSERT INTO purchases (book_id, sup_id, quantity, date_order, \
			estimation) VALUES (?, ?, ?, CURDATE(), DATE_ADD(CURDATE(), INTERVAL ? DAY));";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, book_id);
	ps_stmt->setInt(2, sup_id);
	ps_stmt->setInt(3, quantity);
	ps_stmt->setInt(4, estimation);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Insert new order successfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR!" << endl << endl;
}

void Purchase::view(shared_ptr<sql::Connection> conn) {
	int option;
	cout << "Select an Option" << endl;
	cout << "1. View orders NOT Recieved" << endl;
	cout << "2. View orders Cancelled" << endl;
	cout << "3. View orders Recieved" << endl;
	cout << "Enter Your choice : ";
	cin >> option; cin.ignore();
	
	if (option == 1)
		received = 'F';
	else if (option == 2)
		received = 'C';
	else if (option == 3)
		received = 'T';
	else
		return;

	string query = "SELECT * FROM purchases WHERE received=?";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, string(1, received));
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (option == 1)
		cout << endl << "Orders not recieved are" << endl;
	else if (option == 2)
		cout << endl << "Orders Cancelled are" << endl;
	else if (option == 3)
		cout << endl << "Orders recieved are" << endl;
	while (res->next()) {
		cout << endl;
		cout << "Order Id : " << res->getInt(1) << endl;
		cout << "Book Id : " << res->getInt(2) << endl;
		cout << "Supplier Id :" << res->getInt(3) << endl;
		cout << "Quantity : " << res->getInt(4) << endl;
		cout << "Date Ordered : " << res->getString(5) << endl;
		cout << "Estimated Delivery date : " << res->getString(6) << endl;
		cout << "Received status : " << res->getString(7) << endl;
		cout << endl;
	}
}

void Purchase::mark_cancel(shared_ptr<sql::Connection> conn) {
	cout << "Enter the order id for order cancelled : ";
	cin >> ord_id; cin.ignore();

	string query = "UPDATE purchases SET received=? WHERE ord_id=?";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, string(1, 'C'));
	ps_stmt->setInt(2, ord_id);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Mark cancelled order successfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR!" << endl << endl;
}

void Purchase::mark_received(shared_ptr<sql::Connection> conn) {
	cout << "Enter the order id for order recieved : ";
	cin >> ord_id; cin.ignore();

	string query = "UPDATE purchases SET received=? WHERE ord_id=?";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, string(1, 'T'));
	ps_stmt->setInt(2, ord_id);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Mark received order successfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR!" << endl << endl;
}

void purchase_menu(shared_ptr<sql::Connection> conn) {
	Purchase purchase;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Purchase Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD ORDER" << endl;
		cout << "   2. VIEW" << endl;
		cout << "   3. MARK CANCEL" << endl;
		cout << "   4. MARK RECEIVED" << endl;
		cout << "   5. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
		case 1: purchase.add_order(conn); break;
		case 2: purchase.view(conn); break;
		case 3: purchase.mark_cancel(conn); break;
		case 4: purchase.mark_received(conn); break;
		case 5: return;
		default: cout << endl << "Invalid input" << endl; break;
		}
	}
}