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
	//������� ������
	vector<bookLogRecord> history;

	//��������
	vector<Reader> readers;

	//�����
	/*BooksContainer books;
	
	Librarian(vector<Reader> &readers, BooksContainer& books) {
		this->readers = readers;
		this->books = books;
	}*/

	//����������� ��������
	void addReader();

	//�������� ��������
	void deleteReader();

	//�������������� ��������
	void editReader();

	//���������� �����
	void addBook();

	//�������� �����
	void deleteBook();

	//�������������� �����
	void editBook();
};

