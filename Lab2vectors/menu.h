#pragma once

#include "BooksContainer.h"
#include "ReadersContainer.h"
#include "BooksBorrowingLogsContainer.h"
#include "input.h"

class Menu {
	
	//загрузка пользователей из файла
	//загрузка книг из файла
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
			cout << "1.Читатель\n2.Библиотекарь\n0.Завершение работы\n";
			mode = inputNumberInRange(0, 2);

			switch (mode)
			{
			case 1:
			{
				//читатель
				readerMode();
				break;
			}
			case 2:
			{
				//библиотекарь
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
			cout << "список читателей пуст\n";
		}
		else {
			readers.printToTheConsole();
			int readerId;
			do {
				cout << "Введите id: ";
				cin >> readerId;
			} while (readers.findById(readerId).size() == 0);

			int choice;
			do {
				cout << "1.Найти книгу\n2.Взять книгу\n3.Вернуть книгу\n0.Выход\n";
				choice = inputNumberInRange(0, 3);
				int bookId;
				switch (choice)
				{
				case 1:
					//Найти книгу
					findBook();
					break;
				case 2:
					//Взять книгу
					borrowBook(readerId);

					break;
				case 3:
					//Вернуть книгу
					returnBook(readerId);

					break;
				}
			} while (choice != 0);
		}
	}

	void adminMode() {
		int choice = -1;
		do {
			cout << "1.Редактировать читателя\n2.Редактировать книгу\n3.Посмотреть историю выдачи книги\n4.Сохранить изменения\n0.Выход\n";
			choice = inputNumberInRange(0, 4);

			switch (choice)
			{
				//Редактировать читателя
			case 1:
			{
				cout << "1.Зарегистрировать читателя\n2.Удалить читателя\n3.Редактировать читателя\n";
				int choice = inputNumberInRange(1, 3);

				switch (choice)
				{
				case 1:
					//добавление
					addReader();
					break;

				case 2:
					//удаление
					deleteReader();
					break;

				case 3:
					//редактирование
					editReader();
					break;
				}
				break;
			}
			//Редактировать книгу
			case 2:
			{
				cout << "1.Добавить книгу\n2.Удалить книгу\n3.Редактировать книгу\n";
				int choice = inputNumberInRange(1, 3);

				switch (choice)
				{

				case 1:
					//Добавить книгу
					addBook();
					break;
				case 2:
					//Удалить книгу
					deleteBook();
					break;
				case 3:
					//Редактировать книгу
					editBook();
					break;
				}
				break;
			}

			case 3:
				//Посмотреть историю выдачи книги
				viewLogs();
				break;

			case 4:
				//сохранить изменения в файле
				saveChanges();
				break;
			default:
				break;
			}
		} while (choice != 0);
	}



	void findBook(){
		//вызвать поиск по аттрибуту в контейнере 
		cout << "1.Поиск по названию\n2.Поиск по автору\n3.Поиск по изданию\n4.Напечатать весь список книг\n0.Выход\n";
		int choice = inputNumberInRange(1, 4);

		string s;
		vector<Book> searchResult;
		switch (choice)
		{
		case 1:
			//Поиск по названию
			cout << "Введите название книги: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::name);
			break;
		case 2:
			//Поиск по автору
			cout << "Введите автора книги: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::author);
			break;
		case 3:
			//Поиск по изданию
			cout << "Введите издание книги: ";
			cin >> s;
			searchResult = books.findBy<string>(s, sortedParam::publisher);
			break;
		case 4:
			//Поиск по изданию
			books.printToTheConsole();
			break;
		}

		BooksContainer::printToTheConsole(searchResult.begin(), searchResult.end());
	}

	void borrowBook(int readerId) {
		//проверить что книга есть и добавить её к библиотекарю и читателю во взятые, поменять статус книги
		int bookId;

		do {
			cout << "Введите id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);
		//обработать исключение
		try {
			books.borrowBook(readerId, bookId);
			borrowingsHystory.borrowBook(readerId, bookId);
		}
		catch (exception) {
			cout << "Данная книга находится на руках у другого пользователя" << endl;
		}
	}

	void returnBook(int readerId) {
		//проверить книгу и удалить её из читателя, поменять статус книги
		int bookId;

		do {
			cout << "Введите id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);

		try {
			books.returnBook(readerId, bookId);
			borrowingsHystory.returnBook(readerId, bookId);
		}
		catch (exception) {
			cout << "Данная книга не находится у вас на руках" << endl;
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
			cout << "Введите id: ";
			cin >> readerId;
		} while (readers.findById(readerId).size() == 0);

		char k = getchar();

		Reader newReader;
		cout << "Введите редактированный вариант читателя:\n";
		cin >> newReader;
		newReader.setId(readerId);
		readers.edit(readerId, newReader);
	}
	void deleteReader() {
		int readerId;

		readers.printToTheConsole();

		books.printToTheConsole();
		do {
			cout << "Введите id: ";
			cin >> readerId;
		} while (readers.findById(readerId).size() == 0);

		readers.remove(readerId);
	}

	void addBook() {
		//ввести книгу и добавить в контейнер 
		Book inputBook;

		cin >> inputBook;
		books.add(inputBook);
	}

	void editBook() {
		//ввести книгу и заредачить
		int bookId;

		books.printToTheConsole();

		do {
			cout << "Введите id: ";
			cin >> bookId;
		} while (books.findById(bookId).size() == 0);

		char k = getchar();

		Book newBook;
		cout << "Введите отредактированный вариант книги\n";
		std::cin >> newBook;
		newBook.setId(bookId);
		books.edit(bookId, newBook);
	}

	void deleteBook() {
		//ввести книгу и удалить из контейнера
		int bookId;

		books.printToTheConsole();
		do {
			cout << "Введите id: ";
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