#include "supplier.h"

Supplier::Supplier() { };
Supplier::Supplier(string name, string phone, string addr_line1, 
					string addr_line2,string addr_city) {
	this->name = name;
	this->phone = phone;
	this->addr_line1 = addr_line1;
	this->addr_line2 = addr_line2;
	this->addr_city = addr_city;
}
Supplier::~Supplier() {};

void Supplier::add_supplier(shared_ptr<sql::Connection> conn) {
	cout << "Enter name of Supplier: "; getline(cin, name);
	cout << "Enter phone number: "; getline(cin, phone);
	cout << "Enter address in 3 line (..., district, city): "<<endl;
	cout << "Address line 1: "; getline(cin, addr_line1);
	cout << "Address line 2: "; getline(cin, addr_line2);
	cout << "Address city: "; getline(cin, addr_city);

	string query = "INSERT INTO suppliers (name, phone, addr_line1, \
		addr_line2, addr_city) VALUES (?, ?, ?, ?, ?);";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, name);
	ps_stmt->setString(2, phone);
	ps_stmt->setString(3, addr_line1);
	ps_stmt->setString(4, addr_line2);
	ps_stmt->setString(5, addr_city);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Insert supplier successfully!" << endl;
	else
		cout << endl << "Entry ERROR!" << endl;
}

void Supplier::remove_supplier(shared_ptr<sql::Connection> conn) {
	cout << "Enter the supplier id to remove the Supplier : ";
	cin >> id; cin.ignore();

	string query = "DELETE FROM suppliers WHERE id=?;";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Remove supplier successfully!" << endl;
	else
		cout << endl << "Entry ERROR!" << endl;
}

void Supplier::search_by_id(shared_ptr<sql::Connection> conn) {
	cout << "Enter the supplier id to find the Supplier details : ";
	cin >> id; cin.ignore();

	string query = "SELECT * FROM suppliers WHERE id=?;";

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		cout << "Details of Supplier Id : " << res->getInt(1) << endl;
		cout << "Name : " << res->getString(2) << endl;
		cout << "Phone no. : " << res->getString(3) << endl;
		cout << "Address Line 1 : " << res->getString(4) << endl;
		cout << "Address Line 2 : " << res->getString(5) << endl;
		cout << "City : " << res->getString(5) << endl;
	}
	else {
		cout << endl << "No Supplier Found!!" << endl;
	}
}

void supplier_menu(shared_ptr<sql::Connection> conn) {
	Supplier supplier;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Supplier Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD" << endl;
		cout << "   2. REMOVE" << endl;
		cout << "   3. SEARCH SUPPLIER BY ID" << endl;
		cout << "   4. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
		case 1: supplier.add_supplier(conn); break;
		case 2: supplier.remove_supplier(conn); break;
		case 3: supplier.search_by_id(conn); break;
		case 4: return;
		default: cout << endl << "Invalid input" << endl; break;
		}
	}
}