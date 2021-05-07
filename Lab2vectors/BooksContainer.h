#pragma once
#include "Book.h"
#include "BooksContainer.h"
#include "utills.h"


bool compById(Book &left, Book &right) {
	return left.getId() < right.getId();
}

bool compByAuthor(Book& left, Book& right) {
	return left.getAuthor() < right.getAuthor();
}

bool compByPublisher(Book& left, Book& right) {
	return left.getPublisher() < right.getPublisher();
}



enum sortedParam { id , author, publisher, none };

class BooksContainer {
private:
	vector<Book> container;
	sortedParam sortedBy = none;
	int id = 1;
public:
	void resetId() {
		id = 1;
	}
	//добавление 
	void add(Book &book) {
		book.setId(id++);
		container.push_back(book);
	}

	//редактирование
	void edit(int id, Book &newBook) {
		int editIndex = 0;
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].getId() == id) {
				editIndex = i;
				break;
			}
		}

		container.at(editIndex) = newBook;
	}

	//удаление
	void remove(Book &book) {
		int deleteIndex = 0;
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i] == book) {
				deleteIndex = i;
				break;
			}
		}

		container.erase(container.begin() + deleteIndex);
	}

	//удаление
	void remove(int id) {
		int deleteIndex = 0;
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].getId() == id) {
				deleteIndex = i;
				break;
			}
		}

		container.erase(container.begin() + deleteIndex);
	}

	void borrowBook(int idReader, int idBook) {
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].getId() == idBook) {
				if (container[i].getIdReaders() == -1) {
					container[i].setIdReaders(idReader);
				}
				else {
					//книга у кого-то на руках
					throw exception();
				}
				
			}
		}
	}

	void returnBook(int idReader, int idBook) {
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].getId() == idBook) {
				
				if (container[i].getIdReaders() == idReader) {
					container[i].setIdReaders(-1);
				}
				else {
					//книга принадлежит другому юзеру 
					throw exception();
				}
			}
		}
	}

	//вывод контейнера
	void printToTheConsole() {
		ostream_iterator<Book> cout_it(cout, " ");
		copy(container.begin(), container.end(), cout_it);
	}

	static void printToTheConsole(typename vector <Book> ::iterator begin, typename vector <Book> ::iterator end) {
		ostream_iterator<Book> cout_it(cout, " ");

		copy(begin, end, cout_it);
	}

	void writeStr(const string& s, ofstream& f)
	{
		int l = s.length();
		f.write((char*)&l, sizeof(int));
		f.write(s.data(), l);
	}

	void readStr(string& s, ifstream& f)
	{
		int l;
		f.read((char*)&l, sizeof(int));
		char* str = new char[l + 1];
		f.read(str, l);
		str[l] = 0;
		s = str;
		delete[] str;
	}
	
	void printToFile(string fileName) {	
		std::ofstream fout(fileName, std::ios::out | std::ios::binary);

		//Запишем кол-во записей
		int n = container.size();
		fout.write((char*)&n, sizeof(int)); // Запись POD-члена

		for (size_t i = 0; i < container.size(); i++)
		{
			int tempInt;
			string tempStr;

			tempInt = container[i].getId();
			fout.write((char*)&tempInt, sizeof(int)); // Запись POD-члена

			tempInt = container[i].getIdReaders();
			fout.write((char*)&tempInt, sizeof(int)); // Запись POD-члена

			tempStr = container[i].getIssuingBookDate();
			writeStr(tempStr, fout);

			tempStr = container[i].getBookDeadline();
			writeStr(tempStr, fout);

			tempStr = container[i].getAuthor();
			writeStr(tempStr, fout);

			tempStr = container[i].getName();
			writeStr(tempStr, fout);

			tempStr = container[i].getPublicationDate();
			writeStr(tempStr, fout);

			tempStr = container[i].getPublisher();
			writeStr(tempStr, fout);

			tempInt = container[i].getPrice();
			fout.write((char*)&tempInt, sizeof(int)); // Запись POD-члена
		}

		fout.close();
	}

	void readFromFile(string fileName) {
		ifstream ifile(fileName, ios::binary);
		Book temp;

		//считаем кол-во записей
		int n;
		ifile.read((char*)&n, sizeof(int));

		for (size_t i = 0; i < n; i++)
		{
			int tempInt;
			string tempStr;

			ifile.read((char*)&tempInt, sizeof(int));   // Чтение POD-члена
			temp.setId(tempInt);
			//редактируем id контейнера
			id = tempInt + 1;

			ifile.read((char*)&tempInt, sizeof(int));   // Чтение POD-члена
			temp.setIdReaders(tempInt);

			readStr(tempStr, ifile);
			temp.setIssuingBookDate(tempStr);

			readStr(tempStr, ifile);
			temp.setBookDeadline(tempStr);

			readStr(tempStr, ifile);
			temp.setAuthor(tempStr);

			readStr(tempStr, ifile);
			temp.setName(tempStr);

			readStr(tempStr, ifile);
			temp.setPublicationDate(tempStr);

			readStr(tempStr, ifile);
			temp.setPublisher(tempStr);

			ifile.read((char*)&tempInt, sizeof(tempInt));   // Чтение POD-члена
			temp.setPrice(tempInt);

			container.push_back(temp);
		}

		ifile.close();
		

		
	}


	void readFromConsole() {
		istream_iterator<Book> cin_it(cin), eos;

		copy(cin_it, eos, back_inserter(container));
	}

	template<class T>
	vector<Book> findBy(T sortparam, sortedParam sortparamType) {

		vector<Book> result;

		copy_if(container.begin(), container.end(), back_inserter(result), [&sortparam, &sortparamType](Book& b) {return getParam<T>(sortparamType, b) == sortparam; });

		return result;
	}

	vector<Book> findById(int id) {

		vector<Book> result;

		copy_if(container.begin(), container.end(), back_inserter(result), [&id](Book& b) {return b.getId() == id; });

		return result;
	}


	vector<Book> findByAuthor(string author) {
		vector<Book> result;
		
		copy_if(container.begin(), container.end(), result.begin(), [&author](Book& b) {return b.getAuthor() == author; });

		return result;
	}

	vector<Book> findByPublisher(string publisher) {
		vector<Book> result;
		
		copy_if(container.begin(), container.end(), result.begin(), [&publisher](Book& b) {return b.getPublisher() == publisher; });

		return result;
	}



	static string getParam(sortedParam sortparamType, Book& book) {
		string result = "";
		switch (sortparamType)
		{
			case author:
				result = book.getAuthor();
				break;
			case publisher:
				result = book.getPublisher();
				break;
			default:
				break;
		}
		return result;
	}

	template<class T>
	static T getParam(sortedParam sortparamType, Book& book) {
		T result;
		switch (sortparamType)
		{
		case id:
			result = book.getId();
			break;
		default:
			break;
		}
		return result;
	}

	template<class T>
	vector<Book> findByWithBinarySearch(T sortparam, sortedParam sortparamType) {
		//если контейнер не отсортирован по нужному параметру
		if (sortedBy != sortparamType) {
			//берём указатель на нужный компаратор
			bool (*cmpPtr)(Book & left, Book & right) = NULL;
			switch (sortparamType)
			{
			case id:
				cmpPtr = compById;
				break;
			case author:
				cmpPtr = compByAuthor;
				break;
			case publisher:
				cmpPtr = compByPublisher;
				break;
			default:
				break;
			}

			sort(container.begin(), container.end(), cmpPtr);
			sortedBy = sortparamType;
		}

		//бинарный поиск
		vector<Book> result;
		int m, l = 0, r = container.size();
		T container_i_param;
		while (l < r) {
			m = (l + r) / 2;
			container_i_param = getParam<T>(sortparamType, container[m]);
			if (container_i_param < sortparam) l = m + 1;
			else r = m;
			//если r-ый элемент подходит, то ищем в его окрестносятях такие же

		container_i_param = getParam<T>(sortparamType, container[r]);
		if (container_i_param == sortparam) {
			result.push_back(container[r]);

			//проверим элементы слева от найденного
			bool search = true;
			int idx = r - 1;
			while (search && r >= 0) {
				container_i_param = getParam<T>(sortparamType, container[idx]);
				if (container_i_param == sortparam) {
					result.push_back(container[idx]);
					idx--;
				}
				else {
					search = false;
				}
			}

			//проверим элементы справа от найденного
			idx = r + 1;
			search = true;
			while (search && r < container.size()) {
				container_i_param = getParam<T>(sortparamType, container[idx]);
				if (container_i_param == sortparam) {
					result.push_back(container[idx]);
					idx++;
				}
				else {
					search = false;
				}
			}
		}

		return result;
		}
	}


































	//vector<Book> findByIdWithBinarySearch(int id) {
	//	//сортировать

	//	if (sortedBy != sortedParam::id) {
	//		sort(container.begin(), container.end(), compById);
	//	}

	//	vector<Book> result;
	//	//тут должен быть бинарный поиск
	//	int m, l = 0, r = container.size();
	//	while (l < r) {
	//		m = (l + r) / 2;
	//		if (container[m].getId() < id) l = m + 1;
	//		else r = m;
	//	}

	//	//если r-ый элемент подходит, то ищем в его окрестносятях такие же
	//	if (container[r].getId() == id) {
	//		result.push_back(container[r]);

	//		bool search = true;
	//		int idx = r - 1;
	//		while (search && r >= 0) {
	//			if (container[idx].getId() == id) {
	//				result.push_back(container[idx]);
	//				idx--;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}

	//		idx = r + 1;
	//		search = true;
	//		while (search && r < container.size()) {
	//			if (container[idx].getId() == id) {
	//				result.push_back(container[idx]);
	//				idx++;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}
	//	}
	//	

	//	return result;
	//}

	//vector<Book> findByAuthorWithBinarySearch(string author) {
	//	//сортировать
	//	sort(container.begin(), container.end(), compByAuthor);
	//		
	//	vector<Book> result;
	//	//тут должен быть бинарный поиск
	//	int m, l = 0, r = container.size();
	//	while (l < r) {
	//		m = (l + r) / 2;
	//		if (container[m].getAuthor() < author) l = m + 1;
	//		else r = m;
	//	}

	//	//если r-ый элемент подходит, то ищем в его окрестносятях такие же
	//	if (container[r].getAuthor() == author) {
	//		result.push_back(container[r]);

	//		bool search = true;
	//		int idx = r - 1;
	//		while (search && r >= 0) {
	//			if (container[idx].getAuthor() == author) {
	//				result.push_back(container[idx]);
	//				idx--;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}

	//		idx = r + 1;
	//		search = true;
	//		while (search && r < container.size()) {
	//			if (container[idx].getAuthor() == author) {
	//				result.push_back(container[idx]);
	//				idx++;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}
	//	}



	//	return result;
	//}

	//vector<Book> findByPublisherWithBinarySearch(string publisher) {
	//	//сортировать
	//	sort(container.begin(), container.end(), compByPublisher);

	//	vector<Book> result;
	//	//тут должен быть бинарный поиск
	//	int m, l = 0, r = container.size();
	//	while (l < r) {
	//		m = (l + r) / 2;
	//		if (container[m].getPublisher() < publisher) l = m + 1;
	//		else r = m;
	//	}

	//	//если r-ый элемент подходит, то ищем в его окрестносятях такие же
	//	if (container[r].getPublisher() == publisher) {
	//		result.push_back(container[r]);

	//		bool search = true;
	//		int idx = r - 1;
	//		while (search && r >= 0) {
	//			if (container[idx].getPublisher() == publisher) {
	//				result.push_back(container[idx]);
	//				idx--;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}

	//		idx = r + 1;
	//		search = true;
	//		while (search && r < container.size()) {
	//			if (container[idx].getPublisher() == publisher) {
	//				result.push_back(container[idx]);
	//				idx++;
	//			}
	//			else {
	//				search = false;
	//			}
	//		}
	//	}

	//	return result;
	//}
};






	/*	for (const Book& b : container)
			cout << b << "\n";*/
