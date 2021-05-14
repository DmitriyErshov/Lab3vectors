#pragma once
#include "utills.h"
#include <limits>



int inputNumberInRange(int low, int high) {
	char k;
	//тут будет обработка исключений 
	int num = 0;
	do {
		/*if (char(cin.peek()) == '\n')
			cin.ignore();*/

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		cout << "Введите значение от " << low << " до " << high << ": ";
		cin >> num;
		cout << endl;
	} while (num < low || num > high || !cin.good());

	return num;
}