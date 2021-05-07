#pragma once
#include "utills.h"
#include "Reader.h"
//#include "Book.h"
//#include "BooksContainer.h"

struct bookLogRecord{
	int bookId;
	int readerId;
};

class Librarian
{
	//история выдачи
	vector<bookLogRecord> history;

	//читатели
	vector<Reader> readers;

	//книги
	/*BooksContainer books;
	
	Librarian(vector<Reader> &readers, BooksContainer& books) {
		this->readers = readers;
		this->books = books;
	}*/

	//регистрация читателя
	void addReader();

	//удаление читателя
	void deleteReader();

	//редактирование читателя
	void editReader();

	//добавление книги
	void addBook();

	//удаление книги
	void deleteBook();

	//редактирование книги
	void editBook();
};

