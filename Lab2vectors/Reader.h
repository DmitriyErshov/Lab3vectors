#pragma once
#include "utills.h"
#include "Book.h"

class Reader
{
	int id;
	string firstName, secondName;

	list<Book> container; //������ ����, ������� �� ����� � ������������

	Reader(string firstName, string secondName, int id) {
		this->firstName = firstName;
		this->secondName = secondName;
		this->id = id;
	}


};

