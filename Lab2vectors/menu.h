#pragma once

#include "BooksContainer.h"
#include "ReadersContainer.h"
#include "BooksBorrowingLogsContainer.h"
#include "input.h"

class Menu {
	
	//�������� ������������� �� �����
	//�������� ���� �� �����
	BooksContainer books;
	ReadersContainer readers;
	BooksBorrowings borrowingsHystory;

	int mode = -1;

	void initialiaze() {
		try {
			readers.readFromFile("readers.bin");
		}
		catch (std::bad_alloc& e) {
			readers.resetId();
		}
		try {
			books.readFromFile("books.bin");
		}
		catch (std::bad_alloc& e) {
			books.resetId();
		}
		try {
			borrowingsHystory.readFromFile("booksLog.bin");
		}
		catch (std::bad_alloc& e) {

		}
	}

public:
	Menu() {
		initialiaze();
	}


	void run() {
		do {
			cout << "1.��������\n2.������������\n0.���������� ������\n";
			mode = inputNumberInRange(0, 2);

			switch (mode)
			{
			case 1:
			{
				//��������
				readerMode();
				break;
			}
			case 2:
			{
				//������������
				adminMode();
				break;
			}
			default:
				break;
			}
		} while (mode != 0);
	}


private:
	void readerMode() {
		if (readers.getSize() == 0) {
			cout << "������ ��������� ����\n";
		}
		else {
			readers.printToTheConsole();
			int readerId;
			do {
				cout << "������� id: ";
				cin >> readerId;
			} while (readers.findById(readerId).size() == 0);

			int choice;
			do {
				cout << "1.����� �����\n2.����� �����\n3.������� �����\n0.�����\n";
				choice = inputNumberInRange(0, 3);
				int bookId;
				switch (choice)
				{
				case 1:
					//����� �����
					findBook();
					break;
				case 2:
					//����� �����
					borrowBook(readerId);

					break;
				case 3:
					//������� �����
					returnBook(readerId);

					break;
				}
			} while (choice != 0);
		}
	}

	void adminMode() {
		int choice = -1;
		do {
			cout << "1.������������� ��������\n2.������������� �����\n3.���������� ������� ������ �����\n4.��������� ���������\n0.�����\n";
			choice = inputNumberInRange(0, 4);

			switch (choice)
			{
				//������������� ��������
			case 1:
			{
				cout << "1.���������������� ��������\n2.������� ��������\n3.������������� ��������\n";
				int choice = inputNumberInRange(1, 3);

				switch (choice)
				{
				case 1:
					//����������
					addReader();
					break;

				case 2:
					//��������
					deleteReader();
					break;

				case 3:
					//��������������
					editReader();
					break;
				}
				break;
			}
			//������������� �����
			case 2:
			{
				cout << "1.�������� �����\n2.������� �����\n3.������������� �����\n";
				int choice = inputNumberInRange(1, 3);

				switch (choice)
				{

				case 1:
					//�������� �����
					addBook();
					break;
				case 2:
					//������� �����
					deleteBook();
					break;
				case 3:
					//������������� �����
					editBook();
					break;
				}
				break;
			}

			case 3:
				//���������� ������� ������ �����
				viewLogs();
				break;

			case 4:
				//��������� ��������� � �����
				saveChanges();
				break;
			default:
				break;
			}
		} while (choice != 0);
	}



	void findBook(){
		//������� ����� �� ��������� � ���������� 
		cout << "1.����� �� ��������\n2.����� �� ������\n3.����� �� �������\n4.���������� ���� ������ ����\n0.�����\n";
		int choice = inputNumberInRange(1, 4);

		string s;
		vector<Book> searchResult;
		switch (choice)
		{
		case 1:
			//����� �� ��������
			cout << "������� �������� �����: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::name);
			break;
		case 2:
			//����� �� ������
			cout << "������� ������ �����: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::author);
			break;
		case 3:
			//����� �� �������
			cout << "������� ������� �����: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::publisher);
			break;
		case 4:
			//����� �� �������
			books.printToTheConsole();
			break;
		}

		BooksContainer::printToTheConsole(searchResult.begin(), searchResult.end());
	}

	void borrowBook(int readerId) {
		//��������� ��� ����� ���� � �������� � � ������������ � �������� �� ������, �������� ������ �����
		int bookId;

		do {
			cout << "������� id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);
		//���������� ����������
		try {
			books.borrowBook(readerId, bookId);
			borrowingsHystory.borrowBook(readerId, bookId);
		}
		catch (exception) {
			cout << "������ ����� ��������� �� ����� � ������� ������������" << endl;
		}
	}

	void returnBook(int readerId) {
		//��������� ����� � ������� � �� ��������, �������� ������ �����
		int bookId;

		do {
			cout << "������� id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);

		try {
			books.returnBook(readerId, bookId);
			borrowingsHystory.returnBook(readerId, bookId);
		}
		catch (exception) {
			cout << "������ ����� �� ��������� � ��� �� �����" << endl;
		}
	}

	void addReader() {
		Reader input;
		cin >> input;
		readers.add(input);
	}

	void editReader() {
		int readerId;

		readers.printToTheConsole();

		do {
			cout << "������� id: ";
			cin >> readerId;
		} while (readers.findById(readerId).size() == 0);

		char k = getchar();

		Reader newReader;
		cout << "������� ��������������� ������� ��������:\n";
		cin >> newReader;
		newReader.setId(readerId);
		readers.edit(readerId, newReader);
	}
	void deleteReader() {
		int readerId;

		readers.printToTheConsole();

		books.printToTheConsole();
		do {
			cout << "������� id: ";
			cin >> readerId;
		} while (readers.findById(readerId).size() == 0);

		readers.remove(readerId);
	}

	void addBook() {
		//������ ����� � �������� � ��������� 
		Book inputBook;

		cin >> inputBook;
		books.add(inputBook);
	}

	void editBook() {
		//������ ����� � ����������
		int bookId;

		books.printToTheConsole();

		do {
			cout << "������� id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);

		char k = getchar();

		Book newBook;
		cout << "������� ����������������� ������� �����\n";
		std::cin >> newBook;
		newBook.setId(bookId);
		books.edit(bookId, newBook);
	}

	void deleteBook() {
		//������ ����� � ������� �� ����������
		int bookId;

		books.printToTheConsole();
		do {
			cout << "������� id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);

		books.remove(bookId);
	}

	void viewLogs() {
		borrowingsHystory.printToTheConsole();
	}

	void saveChanges() {
		books.printToFile("books.bin");
		readers.printToFile("readers.bin");
		borrowingsHystory.printToFile("booksLog.bin");
	}
};