#pragma once
#include "utills.h"
#include "Book.h"

class Reader
{
	int id;
	string firstName, secondName;

	//list<int> container; //список книг, которые на руках у пользователя

public:
	Reader() {
		this->id = -1;
		this->firstName =  "unnamed";
		this->secondName = "unnamed";
	}

	Reader(string firstName, string secondName, int id) {
		this->firstName = firstName;
		this->secondName = secondName;
		this->id = id;
	}

	int getId() { return id; }
	string getFirstName() { return firstName; }
	string getSecondName() { return secondName; }

	void setId(int id) { this->id = id; }
	void setFirstName(string firstName) { this->firstName = firstName; }
	void setSecondName(string secondName) { this->secondName = secondName; }

	friend bool operator==(const Reader& left, const Reader& right);
	friend istream& operator>>(istream& in, Reader& reader);
	friend ostream& operator<<(ostream& out, const Reader& reader);

	//void borowBook(Book& book) {
	//	container.push_back(book.getId());
	//}
	//
	//void returnBook(Book& book) {
	//	container.remove(book.getId());
	//}
};

