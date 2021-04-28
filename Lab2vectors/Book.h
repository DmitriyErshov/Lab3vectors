#pragma once
#include "utills.h"

class Book {
private :
	int id; //id книги
	int idReaders; //id читателя, у которого книга на руках

	string clientSecondName; //фамилия абонента
	string issuingBookDate; //дата выдачи
	string returnBookDeadline; //срок возврата
	string author;
	string name;
	string publisher;
	string publicationDate;
	int price;

public:
	Book() {
		this->id = -1;
		this->clientSecondName = "unnamed";
		this->author = "unnamed";
		this->name = "unnamed";
		this->publicationDate = "";
		this->price = 0;
	}
	Book(int id, string secondName, string author, string name, int publicationDate, int price) {
		this->id = id;
		this->clientSecondName = secondName;
		this->author = author;
		this->name = name;
		this->publicationDate = publicationDate;
		this->price = price;
	}

	int getId() { return id; }
	string getClientSecondName() { return clientSecondName; }
	string getAuthor() { return author; }
	string getName() { return name; }
	string getPublisher() {return publisher; } 
	int getPrice() { return price; }


	friend bool operator==(const Book& left, const Book& right);
	friend istream& operator>>(istream& in, Book& book);
	friend ostream& operator<<(ostream& out, const Book& book);
};