#include "employee.h"

Employee::Employee() {};
Employee::Employee(string name, string addr_line1, string addr_line2, string addr_city, 
			string phone,date doj, long salary, string manager_status) {
	this->name = name;
	this->addr_line1 = addr_line1;
	this->addr_line2 = addr_line2;
	this->addr_city = addr_city;
	this->phone = phone;
	this->date_of_joining = doj;
	this->salary = salary;
	this->manager_status = manager_status;
}
Employee::~Employee() {};

void Employee::add_employee(shared_ptr<sql::Connection> conn) {
	cout << "Enter Your Id for verification : ";
	cin >> id; cin.ignore();
	// verify whether you are manager
	string query = "SELECT * FROM employees WHERE id=?;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		string status = res->getString(8);
		if (status == "F") {
			cout << endl <<"You Do Not have Manager Rights!!!" << endl << endl;
			return;
		}
	}
	else {
		cout << endl << "Employee Not Found!!" << endl << endl;
		return;
	}
	// add new employee
	cout << "Enter The details of new employees!!" << endl;
	cout << "Enter The name of the employee : "; getline(cin, name);
	cout << "Enter the Address (in 3 lines) : " << endl;
	cout << "Address Line 1: "; getline(cin, addr_line1);
	cout << "Address Line 2: "; getline(cin, addr_line2);
	cout << "Address City: "; getline(cin, addr_city);
	cout << "Enter phone number: "; getline(cin, phone);
	cout << "Enter the salary : "; cin >> salary;
	cin.ignore();
	query = "INSERT INTO employees (name, addr_line1, addr_line2, addr_city, \
				date_of_joining, phone, salary) VALUES (?, ?, ?, ?, CURDATE(), ?, ?);";
	ps_stmt.reset(conn->prepareStatement(query));
	ps_stmt->setString(1, name);
	ps_stmt->setString(2, addr_line1);
	ps_stmt->setString(3, addr_line2);
	ps_stmt->setString(4, addr_city);
	ps_stmt->setString(5, phone);
	ps_stmt->setBigInt(6, to_string(salary));
	int res_up = ps_stmt->executeUpdate();
	if (res_up)
		cout << endl << "Employee Added Succesfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR" << endl <<endl;
}

void Employee::search_by_id(shared_ptr<sql::Connection> conn) {
	cout << "Enter employee's Id for searching: ";
	cin >> id; cin.ignore();
	// find
	string query = "SELECT * FROM employees WHERE id=?;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());

	if (res->next()) {
		cout << "Employees Details" << endl;
		cout << "Name : " << res->getString(2) << endl;
		cout << "Address : " << res->getString(3) << ", " << res->getString(4) << ", " << res->getString(5) << endl;
		cout << "Phone number : " << res->getString(6) << endl;
		cout << "Date of Joining: " << res->getString(7) << endl;
		cout << "Salary : " << res->getString(8) << endl;
		cout << "Manager status: " << res->getString(9) << endl;
		cout << endl;
	}
	else {
		cout << endl << "No Employee Found!!" << endl << endl;
	}
}

void Employee::search_all(shared_ptr<sql::Connection> conn) {
	string query = "SELECT * FROM employees;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());

	cout << "List Employees Details" << endl;
	while (res->next()) {
		cout << "Name : " << res->getString(2) << endl;
		cout << "Address : " << res->getString(3) << ", " << res->getString(4) << ", " << res->getString(5) << endl;
		cout << "Phone number : " << res->getString(6) << endl;
		cout << "Date of Joining: " << res->getString(7) << endl;
		cout << "Salary : " << res->getString(8) << endl;
		cout << "Manager status: " << res->getString(9) << endl;
		cout << endl;
	}
}

void Employee::assign_manager_status(shared_ptr<sql::Connection> conn) {
	cout << "Enter Your Id for verification : ";
	cin >> id; cin.ignore();
	// verify whether you are manager
	string query = "SELECT * FROM employees WHERE id=?;";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setInt(1, id);
	shared_ptr<sql::ResultSet> res(ps_stmt->executeQuery());
	if (res->next()) {
		string status = res->getString(8);
		if (status == "F") {
			cout << endl << "You Do Not have Manager Rights!!!" << endl << endl;
			return;
		}
	}
	else {
		cout << endl << "Employee Not Found!!" << endl << endl;
		return;
	}
	// assign management status
	cout << "Enter employee's Id for assignment: ";
	cin >> id; cin.ignore();
	query = "UPDATE employees SET manager_status=? WHERE id=?";
	ps_stmt.reset(conn->prepareStatement(query));
	ps_stmt->setString(1, "T");
	ps_stmt->setInt(2, id);
	int res_upate = ps_stmt->executeUpdate();
	if (res_upate)
		cout << endl << "Employee Updated Succesfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR" << endl << endl;
}

void Employee::update_salary(shared_ptr<sql::Connection> conn) {
	cout << "Enter employee's Id for update salary: ";
	cin >> id;
	cout << "Enter the updated salary : ";
	cin >> salary; cin.ignore();
	string query = "UPDATE employees SET salary=? WHERE id=?";
	shared_ptr<sql::PreparedStatement> ps_stmt(conn->prepareStatement(query));
	ps_stmt->setBigInt(1, to_string(salary));
	ps_stmt->setInt(2, id);
	int res_upate = ps_stmt->executeUpdate();
	if (res_upate)
		cout << endl << "Employee Updated salary succesfully!" << endl << endl;
	else
		cout << endl << "Entry ERROR" << endl << endl;
}

void employee_menu(shared_ptr<sql::Connection> conn) {
	Employee employee;
	int option;
	while (1) {
		cout << endl;
		cout << "*******************************************************" << endl;
		cout << "			Employee Menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "   1. ADD EMPLOYEE" << endl;
		cout << "   2. ASSIGN MANAGER STATUS" << endl;
		cout << "   3. SEARCH ALL" << endl;
		cout << "   4. SEARCH EMPLOYEE BY ID" << endl;
		cout << "   5. UPDATE SALARY" << endl;
		cout << "   6. RETURN TO MAIN MENU" << endl << endl;
		cout << "Enter your choice: ";
		cin >> option; cin.ignore();

		switch (option) {
		case 1: employee.add_employee(conn); break;
		case 2: employee.assign_manager_status(conn); break;
		case 3: employee.search_all(conn); break;
		case 4: employee.search_by_id(conn); break;
		case 5: employee.update_salary(conn); break;
		case 6: return;
		default: cout << endl << "Invalid input" << endl; break;
		}
	}
}