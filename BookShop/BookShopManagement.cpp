/*
 https://www.geeksforgeeks.org/how-to-setup-mysql-database-in-visual-studio-2022-for-a-cpp-application/
 https://youtu.be/a_W4zt5sR1M?si=gUX2ALe1bdBE8GVE
*/
#include "book.h"
#include "supplier.h"
#include "purchase.h"
#include "employee.h"
#include "member.h"
#include "sale.h"

#define HOST		"127.0.0.1"
#define USER		"root"
#define PASS		"123456789" // password of MySQL
#define DATABASE	"management"
#define PORT		3306
#define DB			"Management"
#define PASSWORD	"123456"	// password of application

void main_menu(shared_ptr<sql::Connection> conn) {
	int option;
	cout << endl;
	cout << "*******************************************************" << endl;
	cout << "			Main Menu" << endl;
	cout << "*******************************************************" << endl;
	cout << "   1. Book Menu" << endl;
	cout << "   2. Supplier Menu" << endl;
	cout << "   3. Purchase Menu" << endl;
	cout << "   4. Employee Menu" << endl;
	cout << "   5. Member Menu" << endl;
	cout << "   6. Sale Menu" << endl;
	cout << "   7. EXIT" << endl << endl;
	cout << "Enter your choice: ";
	cin >> option; cin.ignore();

	switch (option) {
		case 1: book_menu(conn); break;
		case 2: supplier_menu(conn); break;
		case 3: purchase_menu(conn); break;
		case 4: employee_menu(conn); break;
		case 5: member_menu(conn); break;
		case 6: sale_menu(conn); break;
		case 7: cout << endl << "EXITED!" << endl; exit(0);
		default: cout << endl << "Invalid input" << endl; break;
	}
}

int main(int argc, const char **argv) {
	try {
		string url(argc >= 2 ? argv[1] : "tcp://127.0.0.1:3306");
		const string user(argc >= 3 ? argv[2] : USER);
		const string pass(argc >= 4 ? argv[3] : PASS);
		const string database(argc >= 5 ? argv[4] : DB);

		sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
		shared_ptr<sql::Connection> conn(driver->connect(url, user, pass));
		conn->setSchema(database);

		while (1) {
			main_menu(conn);
		}

	}
	catch(sql::SQLException &e){
		/*
		 MySQL Connector/C++ throws three different exceptions:
		 - sql::MethodNotImplementedException (derived from sql::SQLException)
		 - sql::InvalidArgumentException (derived from sql::SQLException)
		 - sql::SQLException (derived from std::runtime_error)
		*/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return 0;
}

/*Book book;
book.add(conn);
book.search_by_id(conn);
book.search_all(conn);
book.update_price(conn);*/
/*Supplier supplier;
supplier.add_supplier(conn);
supplier.remove_supplier(conn);
supplier.search_by_id(conn);*/
/*Purchase purchase;
purchase.add_order(conn);
purchase.view(conn);
purchase.mark_cancel(conn);
purchase.view(conn);
purchase.mark_received(conn);
purchase.view(conn);*/
/*Employee employee;
employee.add_employee(conn);
employee.search_all(conn);
employee.assign_manager_status(conn);
employee.search_by_id(conn);
employee.update_salary(conn);*/
/*Member member;
member.add_member(conn);
member.search_by_id(conn);*/
/*Sale sale;
sale.add_sale(conn);
sale.search_total_sale(conn);*/