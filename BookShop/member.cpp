#include "member.h"

Member::Member() {};
Member::Member(string name, string addr_line1, string addr_line2, string addr_city, string phone, 
	date begin_date, date end_date, string valid) {
	// TODO
}
Member::~Member() {};

void Member::add_member(shared_ptr<sql::Connection> conn) {
	cout << "Enter the name of the member : ";
	getline(cin, name);
	cout << "Enter phone no. : ";
	getline(cin, phone);
	cout << "Enter address (in 3 lines)" << endl;
	cout << "Address Line 1: "; getline(cin, addr_line1);
	cout << "Address Line 2: "; getline(cin, addr_line2);
	cout << "Address City: "; getline(cin, addr_city);

	string query = "INSERT INTO members (name, addr_line1, addr_line2, addr_city, \
		phone, begin_date, end_date) VALUES (?, ?, ?, ?, ?, CURDATE(), DATE_ADD(CURDATE(), INTERVAL ? YEAR));";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, name);
	ps_stmt->setString(2, addr_line1);
	ps_stmt->setString(3, addr_line2);
	ps_stmt->setString(4, addr_city);
	ps_stmt->setString(5, phone);
	ps_stmt->setInt(6, 1);
	int res = ps_stmt->executeUpdate();
	if (res)
		cout << endl << "Insert new member successfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR!" << endl << endl;
};

void Member::refresh(shared_ptr<sql::Connection> conn) {
	string query = "UPDATE members SET valid=? WHERE end_date<=CURDATE();";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setString(1, "valid");
	int res = ps_stmt->executeUpdate();
}

void Member::search_by_id(shared_ptr<sql::Connection> conn) {
	cout << "Enter member ID for searching: ";
	cin >> id; cin.ignore();

	string query = "SELECT * FROM members WHERE id=?;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		cout << endl;
		cout << "Member Details" << endl;
		cout << "Name : " << res->getString(2) << endl;
		cout << "Address : " << res->getString(3) << ", " << res->getString(4) << ", " << res->getString(5) << endl;
		cout << "Phone number : " << res->getString(6) << endl;
		cout << "Membership begin date : " << res->getString(7) << endl;
		cout << "Membership end date  : " << res->getString(8) << endl;
		cout << "Membership Status : " << res->getString(9) << endl << endl;
	}
	else {
		cout << endl << "No member found!" << endl << endl;
	}
};

void member_menu(shared_ptr<sql::Connection> conn) {
	Member member;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Member Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD MEMBER" << endl;
		cout << "   2. REFRESH" << endl;
		cout << "   3. SEARCH MEMBER BY ID" << endl;
		cout << "   4. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
		case 1: member.add_member(conn); break;
		case 2: member.refresh(conn); break;
		case 3: member.search_by_id(conn); break;
		case 4: return;
		default: cout << endl << "Invalid input" << endl; break;
		}
	}
}