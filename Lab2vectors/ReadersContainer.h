#pragma once
#include "Reader.h"

class ReadersContainer
{
private:
	vector<Reader> container;
	int id = 1;
public:
	int getSize() {
		return container.size();
	}
	void resetId() {
		id = 1;
	}
	//добавление 
	void add(Reader& reader) {
		reader.setId(id++);
		container.push_back(reader);
	}

	//редактирование
	void edit(int id, Reader& newReader) {
		int editIndex = 0;
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].getId() == id) {
				editIndex = i;
				break;
			}
		}

		container.at(editIndex) = newReader;
	}

	//удаление
	void remove(Reader& reader) {
		int deleteIndex = 0;
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i] == reader) {
				deleteIndex = i;
				break;
			}
		}

		container.erase(container.begin() + deleteIndex);
	}

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

	//вывод контейнера
	void printToTheConsole() {
		ostream_iterator<Reader> cout_it(cout, " ");
		copy(container.begin(), container.end(), cout_it);
	}

	static void printToTheConsole(typename vector <Reader> ::iterator begin, typename vector <Reader> ::iterator end) {
		ostream_iterator<Reader> cout_it(cout, " ");

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

			tempStr = container[i].getFirstName();
			writeStr(tempStr, fout);

			tempStr = container[i].getSecondName();
			writeStr(tempStr, fout);
		}

		fout.close();
	}

	void readFromFile(string fileName) {
		ifstream ifile(fileName, ios::binary);
		Reader temp;
		
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

			readStr(tempStr, ifile);
			temp.setFirstName(tempStr);

			readStr(tempStr, ifile);
			temp.setSecondName(tempStr);

			container.push_back(temp);
		}

		ifile.close();
	}


	void readFromConsole() {
		istream_iterator<Reader> cin_it(cin), eos;

		copy(cin_it, eos, back_inserter(container));
	}

	//template<class T>
	//vector<Book> findBy(T sortparam, sortedParam sortparamType) {

	//	vector<Book> result;

	//	copy_if(container.begin(), container.end(), back_inserter(result), [&sortparam, &sortparamType](Book& b) {return getParam<T>(sortparamType, b) == sortparam; });

	//	return result;
	//}

	vector<Reader> findById(int id) {

		vector<Reader> result;

		copy_if(container.begin(), container.end(), back_inserter(result), [&id](Reader& r) {return r.getId() == id; });

		return result;
	}

	//vector<Book> findByClientSecondName(string secondName) {
	//	vector<Book> result;

	//	copy_if(container.begin(), container.end(), result.begin(), [&secondName](Book& b) {return b.getClientSecondName() == secondName; });

	//	return result;
	//}

	//vector<Book> findByAuthor(string author) {
	//	vector<Book> result;

	//	copy_if(container.begin(), container.end(), result.begin(), [&author](Book& b) {return b.getAuthor() == author; });

	//	return result;
	//}

	//vector<Book> findByPublisher(string publisher) {
	//	vector<Book> result;

	//	copy_if(container.begin(), container.end(), result.begin(), [&publisher](Book& b) {return b.getPublisher() == publisher; });

	//	return result;
	//}



	//static string getParam(sortedParam sortparamType, Book& book) {
	//	string result = "";
	//	switch (sortparamType)
	//	{
	//	case author:
	//		result = book.getAuthor();
	//		break;
	//	case publisher:
	//		result = book.getPublisher();
	//		break;
	//	default:
	//		break;
	//	}
	//	return result;
	//}

	//template<class T>
	//static T getParam(sortedParam sortparamType, Book& book) {
	//	T result;
	//	switch (sortparamType)
	//	{
	//	case id:
	//		result = book.getId();
	//		break;
	//	default:
	//		break;
	//	}
	//	return result;
	//}

	//template<class T>
	//vector<Book> findByWithBinarySearch(T sortparam, sortedParam sortparamType) {
	//	//если контейнер не отсортирован по нужному параметру
	//	if (sortedBy != sortparamType) {
	//		//берём указатель на нужный компаратор
	//		bool (*cmpPtr)(Book & left, Book & right) = NULL;
	//		switch (sortparamType)
	//		{
	//		case id:
	//			cmpPtr = compById;
	//			break;
	//		case author:
	//			cmpPtr = compByAuthor;
	//			break;
	//		case publisher:
	//			cmpPtr = compByPublisher;
	//			break;
	//		default:
	//			break;
	//		}

	//		sort(container.begin(), container.end(), cmpPtr);
	//		sortedBy = sortparamType;
	//	}

	//	//бинарный поиск
	//	vector<Book> result;
	//	int m, l = 0, r = container.size();
	//	T container_i_param;
	//	while (l < r) {
	//		m = (l + r) / 2;
	//		container_i_param = getParam<T>(sortparamType, container[m]);
	//		if (container_i_param < sortparam) l = m + 1;
	//		else r = m;
	//		//если r-ый элемент подходит, то ищем в его окрестносятях такие же

	//		container_i_param = getParam<T>(sortparamType, container[r]);
	//		if (container_i_param == sortparam) {
	//			result.push_back(container[r]);

	//			//проверим элементы слева от найденного
	//			bool search = true;
	//			int idx = r - 1;
	//			while (search && r >= 0) {
	//				container_i_param = getParam<T>(sortparamType, container[idx]);
	//				if (container_i_param == sortparam) {
	//					result.push_back(container[idx]);
	//					idx--;
	//				}
	//				else {
	//					search = false;
	//				}
	//			}

	//			//проверим элементы справа от найденного
	//			idx = r + 1;
	//			search = true;
	//			while (search && r < container.size()) {
	//				container_i_param = getParam<T>(sortparamType, container[idx]);
	//				if (container_i_param == sortparam) {
	//					result.push_back(container[idx]);
	//					idx++;
	//				}
	//				else {
	//					search = false;
	//				}
	//			}
	//		}

	//		return result;
	//	}
	//}
};

