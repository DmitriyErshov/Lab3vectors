#pragma once

#include "utills.h"

struct recordBorrowBook {
	int idReader, idBook;
	bool onHand = true;
};

class BooksBorrowings {
private:
	vector<recordBorrowBook> container;
public:
	void borrowBook(int idReader, int idBook) {
		recordBorrowBook newRecord;
		newRecord.idBook = idBook;
		newRecord.idReader = idReader;
		container.push_back(newRecord);
	}

	void returnBook(int idReader, int idBook) {
		for (int i = 0; i < container.size(); i++)
		{
			if (container[i].idBook == idBook && container[i].idReader == idReader) {
				container[i].onHand = false;
			}
		}
	}

	void printToTheConsole() {
		ostream_iterator<Book> cout_it(cout, " ");
		copy(container.begin(), container.end(), cout_it);
	}

	void printToFile(string fileName) {
		std::ofstream fout(fileName, std::ios::out | std::ios::binary);

		//Запишем кол-во записей
		int n = container.size();

		recordBorrowBook tempRec;
		for (size_t i = 0; i < container.size(); i++)
		{
			tempRec = container[i];
			fout.write((char*)&tempRec, sizeof(recordBorrowBook)); // Запись POD-члена
		}

		fout.close();
	}

	void readFromFile(string fileName) {
		ifstream ifile(fileName, ios::binary);
		recordBorrowBook tempRec;

		int n;
		ifile.read((char*)&n, sizeof(int));

		for (size_t i = 0; i < n; i++)
		{
			ifile.read((char*)&tempRec, sizeof(recordBorrowBook));   // Чтение POD-члена

			container.push_back(tempRec);
		}

		ifile.close();

	}

};