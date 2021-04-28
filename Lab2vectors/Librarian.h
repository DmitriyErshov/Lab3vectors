#pragma once
#include "utills.h"
#include "Reader.h"
#include "Book.h"

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
	vector<Book> books;
	
	Librarian(vector<Reader> &readers, vector<Book>& books) {
		this->readers = readers;
		this->books = books;
	}

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

