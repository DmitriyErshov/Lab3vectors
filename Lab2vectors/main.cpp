#include "utills.h"
#include "Book.h"
#include "BooksContainer.h"
#include "ReadersContainer.h"
#include "BooksBorrowingLogsContainer.h"
#include "input.h"

//Предусмотреть операции добавления, изменения и удаления элемента контейнера.
//Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл.
//Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным критериям.Реализовать поиск в двух вариантах : линейный поиск и двоичный поиск на отсортированном контейнере.
//Предусмотреть вывод подмножества выборки на экран и в файл.




int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//загрузка пользователей из файла
	//загрузка книг из файла
	BooksContainer books;
	ReadersContainer readers;
	BooksBorrowings borrowingsHystory;

	
	//добавить исключения 
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
		cout << "1.Читатель\n2.Библиотекарь\n0.Завершение работы\n";
		mode = inputNumberInRange(0, 2);

		switch (mode)
		{
		//читатель
		case 1:
		{
			//вывести список и дать выбор
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
						//вызвать поиск по аттрибуту в контейнере 
						books.printToTheConsole();
						break;
					
					case 2:
						//Взять книгу
						//проверить что книга есть и добавить её к библиотекарю и читателю во взятые, поменять статус книги
						do {
							cout << "Введите id: ";
							cin >> bookId;
						} while (books.findById(bookId).size() == 0);
						//обработать исключение
						try {
							books.borrowBook(readerId, bookId);
							borrowingsHystory.borrowBook(readerId, bookId);
						}catch(exception){
							cout << "Данная книга находится на руках у другого пользователя" << endl;
						}
						

						break;
					
					case 3:
						//Вернуть книгу
						//проверить книгу и удалить её из читателя, поменять статус книги
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
						
						
						break;
					}
				} while (choice != 0);
			}
			break;
		}
		//библиотекарь
		case 2:
		{
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

					Reader input;
					int readerId;
					switch (choice)
					{
					case 1:
						//добавление
						cin >> input;
						readers.add(input);
						break;
						
					case 2:
						//удаление
						readers.printToTheConsole();

						books.printToTheConsole();
						do {
							cout << "Введите id: ";
							cin >> readerId;
						} while (readers.findById(readerId).size() == 0);

						readers.remove(readerId);
						break;
						
					case 3:
						//редактирование
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
						break;
					}
					break;
				}
				//Редактировать книгу
				case 2:
				{
					cout << "1.Добавить книгу\n2.Удалить книгу\n3.Редактировать книгу\n";
					int choice = inputNumberInRange(1, 3);

					Book inputBook;
					int bookId;
					switch (choice)
					{
						//Добавить книгу
					case 1:
						//ввести книгу и добавить в контейнер 
						std::cin >> inputBook;
						books.add(inputBook);
						break;
						//Удалить книгу
					case 2:
						//ввести книгу и удалить из контейнера
						books.printToTheConsole();
						do {
							cout << "Введите id: ";
							cin >> bookId;
						} while (books.findById(bookId).size() == 0);

						books.remove(bookId);
						break;
						//Редактировать книгу
					case 3:
						//ввести книгу и заредачить
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
						break;
					}
					break;
				}
				
				case 3:
					int bookId;
					//Посмотреть историю выдачи книги
					//borrowingsHystory.printToTheConsole();

					break;
				//сохранить изменения в файле
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
3 месяца
Пушкин
Онегин
2013
спб
113

10.4.2021
3 месяца
Толстой
Война и мир
1999
эскмо
500

кузнецов
10.1.2017
1 месяц
Булгаков
Мастер и Маргарита
2001
врн
300
6
Смирнов
18.7.2015
1 месяц
Достоевский
Преступление и Наказание
2009
феникс
250

*/