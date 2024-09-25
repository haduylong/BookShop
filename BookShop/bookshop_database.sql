USE Management;

CREATE TABLE books (
	id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    author VARCHAR(255),
    price INT NOT NULL,
    quantity INT DEFAULT 0,
    
    PRIMARY KEY(id)
);
/*
RENAME TABLE book to books;
DROP TABLE books;
*/

CREATE TABLE suppliers (
	id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    phone VARCHAR(25),
    addr_line1 VARCHAR(255),
    addr_line2 VARCHAR(255),
    addr_city VARCHAR(255) NOT NULL,
    
    PRIMARY KEY(id)
);

CREATE TABLE purchases (
	ord_id INT AUTO_INCREMENT,
    book_id INT,
    sup_id INT,
    quantity INT DEFAULT 0,
    date_order DATE,
    estimation DATE, -- Estimated expected Delivery by day
    received ENUM('T', 'C', 'F') DEFAULT 'F',
    inv int,
    
    PRIMARY KEY(ord_id),
    CONSTRAINT FK_BookOrder FOREIGN KEY (book_id) REFERENCES books(id),
    CONSTRAINT FK_SupplierOrder FOREIGN KEY (sup_id) REFERENCES suppliers(id)
);
/*
DROP TABLE purchases;
*/

CREATE TABLE employees(
	id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,    
    addr_line1 VARCHAR(255),
    addr_line2 VARCHAR(255),
    addr_city VARCHAR(255) NOT NULL,
    phone VARCHAR(25),
    date_of_joining DATE,
    salary BIGINT,
    manager_status ENUM('T', 'F') DEFAULT 'F',
    
    PRIMARY KEY(id)
);

CREATE TABLE members(
	id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,    
    addr_line1 VARCHAR(255),
    addr_line2 VARCHAR(255),
    addr_city VARCHAR(255) NOT NULL,
    phone VARCHAR(25),
    begin_date DATE,
    end_date DATE NOT NULL,
    valid ENUM('valid', 'invalid') DEFAULT 'valid', -- equal invalid at expỉation
    
    PRIMARY KEY(id)
);

CREATE TABLE sales(
	invoice_id INT AUTO_INCREMENT,
    member_id INT,
    book_id INT,
    quantity INT,
    amount INT, -- total cost = price*quantity
    date_s DATE, -- sale date
    
    PRIMARY KEY(invoice_id),
    CONSTRAINT FK_MemberSale FOREIGN KEY(member_id) REFERENCES members(id),
    CONSTRAINT FK_BookSale FOREIGN KEY(book_id) REFERENCES books(id)
);


INSERT INTO `management`.`employees` (`name`, `addr_line1`, `addr_line2`, `addr_city`, `phone`, `salary`, `manager_status`) 
VALUES ('Manager01', 'Hoang Hoa', 'Tam Duong', 'Vinh Phuc', '0235146898', '2000000', 'T');
