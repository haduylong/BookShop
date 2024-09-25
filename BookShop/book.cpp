#include "book.h"

Book::Book(){}

Book::Book(string name, string author, int price, int quantity) {
	this->name = name;
	this->author = author;
	this->price = price;
	this->quantity = quantity;
}

Book::~Book() {};

void Book::add(shared_ptr<sql::Connection> conn) {
	string name, author;
	int price, quantity;
	cout << "Enter name of the Book: ";
	getline(cin, name); //cin >> this->name;
	cout << "Enter name of the Author: ";
	getline(cin, author); //cin >> this->author;
	cout << "Enter the Price : ";
	cin >> price;
	cout << "Enter the quantity : ";
	cin >> quantity;
	cin.ignore();

	stringstream ss_query("");
	ss_query << "INSERT INTO books (name, author, price, quantity) \
					VALUES (?, ?, ?, ?);";
	string query = ss_query.str();

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, name);
	ps_stmt->setString(2, author);
	ps_stmt->setInt(3, price);
	ps_stmt->setInt(4, quantity);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Insert book successfully" << endl << endl;
	else
		cout << endl << "Entry ERROR !" << endl;
}

void Book::search_by_id(shared_ptr<sql::Connection> conn) {
	cout << "Enter ID of the Book: ";
	cin >> this->id;
	cin.ignore();
	
	stringstream ss_query("");
	ss_query << "SELECT * FROM books WHERE id=?;";
	string query = ss_query.str();

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, this->id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());

	if (res->next()) {
		cout << "The Details of Book Id " << res->getInt(1) << endl;
		cout << "The Name of the book is : " << res->getString(2) << endl;
		cout << "THE Author of " << res->getString(2) << " is " << res->getString(3) << endl;
		cout << "The Price of the book is : " << res->getInt(4) << endl;
		cout << "The inventory count is: " << res->getInt(5) << endl;
	}	
	else
		cout << endl <<"No Book Found" << endl;
}
/* update all book from suppliers */
void Book::update_all(shared_ptr<sql::Connection> conn) {
	vector<int> book_id, quantity;
	// lấy thông tin book_id, quantity đã mua từ các nhà cung cấp
	stringstream ss_query("");
	ss_query << "SELECT book_id, quantity FROM purchases WHERE received=? AND inv IS NULL;";
	string query = ss_query.str();
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, "T");
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());

	// cập nhật lại inv của purchases
	ss_query.clear();
	ss_query << "UPDATE purchases SET inv=? WHERE received=? AND inv IS NULL;";
	query = ss_query.str();
	ps_stmt.reset(conn->prepareStatement(query));
	ps_stmt->setInt(1, 1);
	ps_stmt->setString(2, "T");
	ps_stmt->executeUpdate();

	// cập nhật lại books
	while (res->next()) {
		book_id.push_back(res->getInt(1));
		quantity.push_back(res->getInt(2));
	}

	for (int i = 0; i < book_id.size(); i++) {
		query = "UPDATE books SET quantity=? WHERE book_id=?;";
		ps_stmt.reset(conn->prepareStatement(query));
		ps_stmt->setInt(1, quantity[i]);
		ps_stmt->setInt(2, book_id[i]);
		ps_stmt->executeUpdate();
	}

	cout << "The orders recieved have been updated."<<endl;
};

void Book::remove(shared_ptr<sql::Connection> conn) {};

void Book::search_all(shared_ptr<sql::Connection> conn) {
	string query = "SELECT * FROM books;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	while (res->next()) {
		cout << "------------------------------------------------------" << endl;
		cout << "The Details of Book Id: " << res->getInt(1) << endl;
		cout << "The Name of the book is : " << res->getString(2) << endl;
		cout << "THE Author of " << res->getString(2) << " is: " << res->getString(3) << endl;
		cout << "The Price of the book is : " << res->getInt(4) << endl;
		cout << "The inventory count is: " << res->getInt(5) << endl;
		cout << "------------------------------------------------------" << endl;
	}
};
void Book::update_price(shared_ptr<sql::Connection> conn) {
	char choice;
	int newPrice;
	cout << "Enter the ID of the book you want to update: ";
	cin >> this->id; cin.ignore();
	// find book
	stringstream ss_query("");
	ss_query << "SELECT * FROM books WHERE id=?";
	string query = ss_query.str();

	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, this->id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	// update
	if (res->next()) {
		cout << "The Name of the book is : " << res->getString("name") << endl;
		cout << "The current price of the book is : " << res->getInt("price") << endl;
		cout << "Do you Want to Update the Price [y/n] : ";
		cin >> choice;
		if (choice == 121 || choice == 89) {
			cout << "Enter the new price: ";
			cin >> newPrice; cin.ignore();
			query = "UPDATE books SET price=? WHERE id=?";
			ps_stmt.reset(conn->prepareStatement(query));
			ps_stmt->setInt(1, newPrice);
			ps_stmt->setInt(2, this->id);
			int status = ps_stmt->executeUpdate();
			if (status)
				cout << endl << "Update Successfully!" << endl;
			else
				cout << endl << "Entry ERROR!" << endl;
		}
		else {
			cout << endl << "No Change!" << endl;
		}
	}
	else {
		cout << endl << "No Book Found" << endl;
	}
};

void book_menu(shared_ptr<sql::Connection> conn) {
	Book book;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Book Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD" << endl;
		cout << "   2. UPDATE PRICE" << endl;
		cout << "   3. SEARCH BOOK BY ID" << endl;
		cout << "   4. UPDATE STATUS ALL" << endl;
		cout << "   5. DISPLAY ALL" << endl;
		cout << "   6. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
			case 1: book.add(conn); break;
			case 2: book.update_price(conn); break;
			case 3: book.search_by_id(conn); break;
			case 4: book.update_all(conn); break;
			case 5: book.search_all(conn); break;
			case 6: return;
			default: cout << endl << "Invalid input" << endl; break;
		}
	}
	
	return;
};