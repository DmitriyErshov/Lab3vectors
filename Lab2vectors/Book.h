#pragma once
#include "utills.h"

class Book {
private :
	int id; //id книги
	int idReaders; //id читателя, у которого книга на руках

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
		this->idReaders = -1;
		this->author = "unnamed";
		this->name = "unnamed";
		this->publicationDate = "";
		this->price = 0;
	}
	Book(int id, string author, string name, int publicationDate, int price) {
		this->id = id;
		this->author = author;
		this->name = name;
		this->publicationDate = publicationDate;
		this->price = price;
	}

	int getId() { return id; }
	int getIdReaders() { return idReaders; }
	string getIssuingBookDate() { return issuingBookDate; }
	string getBookDeadline() { return returnBookDeadline; }
	string getAuthor() { return author; }
	string getName() { return name; }
	string getPublisher() {return publisher; } 
	string getPublicationDate() { return publicationDate; }
	int getPrice() { return price; }

	void setId(int id) { this->id = id; }
	void setIdReaders(int idReaders) { this->idReaders = idReaders; }
	void setIssuingBookDate(string issuingBookDate) { this->issuingBookDate = issuingBookDate; }
	void setBookDeadline(string returnBookDeadline) { this->returnBookDeadline = returnBookDeadline; }
	void setAuthor(string author) { this->author = author; }
	void setName(string name) { this->name = name; }
	void setPublisher(string publisher) { this->publisher = publisher; }
	void setPublicationDate(string publicationDate) { this->publicationDate = publicationDate; }
	void setPrice(int price) { this->price = price; }


	friend bool operator==(const Book& left, const Book& right);
	friend istream& operator>>(istream& in, Book& book);
	friend ostream& operator<<(ostream& out, const Book& book);
};