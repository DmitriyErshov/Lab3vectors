#include "utills.h"
#include "Book.h"
#include "BooksContainer.h"
#include "ReadersContainer.h"
#include "BooksBorrowingLogsContainer.h"
#include "input.h"

//������������� �������� ����������, ��������� � �������� �������� ����������.
//����������� ���� � ����� ��������� ���������� � �������������� ��������� ���������� �� ����� � � ����.
//����������� �������� ������ �� �������� ��������� � ������� ������������ ��������� �� �������� ���������.����������� ����� � ���� ��������� : �������� ����� � �������� ����� �� ��������������� ����������.
//������������� ����� ������������ ������� �� ����� � � ����.




int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//�������� ������������� �� �����
	//�������� ���� �� �����
	BooksContainer books;
	ReadersContainer readers;
	BooksBorrowings borrowingsHystory;

	
	//�������� ���������� 
	try {
		readers.readFromFile("readers.bin");
	}
	catch(std::bad_alloc& e){
		readers.resetId();
	}
	try {
		books.readFromFile("books.bin");
	}
	catch (std::bad_alloc& e) {
		books.resetId();
	}
	
	int mode = -1;
	

	do {
		cout << "1.��������\n2.������������\n0.���������� ������\n";
		mode = inputNumberInRange(0, 2);

		switch (mode)
		{
		//��������
		case 1:
		{
			//������� ������ � ���� �����
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
						//������� ����� �� ��������� � ���������� 
						books.printToTheConsole();
						break;
					
					case 2:
						//����� �����
						//��������� ��� ����� ���� � �������� � � ������������ � �������� �� ������, �������� ������ �����
						do {
							cout << "������� id: ";
							cin >> bookId;
						} while (books.findById(bookId).size() == 0);
						//���������� ����������
						try {
							books.borrowBook(readerId, bookId);
							borrowingsHystory.borrowBook(readerId, bookId);
						}catch(exception){
							cout << "������ ����� ��������� �� ����� � ������� ������������" << endl;
						}
						

						break;
					
					case 3:
						//������� �����
						//��������� ����� � ������� � �� ��������, �������� ������ �����
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
						
						
						break;
					}
				} while (choice != 0);
			}
			break;
		}
		//������������
		case 2:
		{
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

					Reader input;
					int readerId;
					switch (choice)
					{
					case 1:
						//����������
						cin >> input;
						readers.add(input);
						break;
						
					case 2:
						//��������
						readers.printToTheConsole();

						books.printToTheConsole();
						do {
							cout << "������� id: ";
							cin >> readerId;
						} while (readers.findById(readerId).size() == 0);

						readers.remove(readerId);
						break;
						
					case 3:
						//��������������
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
						break;
					}
					break;
				}
				//������������� �����
				case 2:
				{
					cout << "1.�������� �����\n2.������� �����\n3.������������� �����\n";
					int choice = inputNumberInRange(1, 3);

					Book inputBook;
					int bookId;
					switch (choice)
					{
						//�������� �����
					case 1:
						//������ ����� � �������� � ��������� 
						std::cin >> inputBook;
						books.add(inputBook);
						break;
						//������� �����
					case 2:
						//������ ����� � ������� �� ����������
						books.printToTheConsole();
						do {
							cout << "������� id: ";
							cin >> bookId;
						} while (books.findById(bookId).size() == 0);

						books.remove(bookId);
						break;
						//������������� �����
					case 3:
						//������ ����� � ����������
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
						break;
					}
					break;
				}
				
				case 3:
					int bookId;
					//���������� ������� ������ �����
					//borrowingsHystory.printToTheConsole();

					break;
				//��������� ��������� � �����
				case 4:
					books.printToFile("books.bin");
					readers.printToFile("readers.bin");
					break;
				default:
					break;
				}
			} while (choice != 0);
			
			break;
		}
		default:
			break;
		}
	}while (mode != 0);



	return 0;
}


//std::ofstream fout("books.bin", std::ios::out | std::ios::binary);
	//string s1 = "test";
	//
	//writeStr(s1, fout);
	//fout.close();

	//string s2;
	//ifstream ifile("books.bin", ios::binary);
	//readStr(s2, ifile);
	//ifile.close();


/*
11.12.2019
3 ������
������
������
2013
���
113

10.4.2021
3 ������
�������
����� � ���
1999
�����
500

��������
10.1.2017
1 �����
��������
������ � ���������
2001
���
300
6
�������
18.7.2015
1 �����
�����������
������������ � ���������
2009
������
250

*/