#pragma once
#include "utills.h"
#include <limits>


//void showCommands(string s, ...)
//{
//	int result = 0;
//	// получаем указатель на параметр n
//	for (string* ptr = &s; s > 0; s--)
//	{
//		result += *(++ptr);
//	}
//}

//int inputNumberInRange(int low, int high) {
//	char k;
//	//тут будет обработка исключений 
//	int num = 0;
//	do {
//		printf("¬ведите значение от %d до %d: ", low, high);
//		scanf_s("%d", &num);
//		k = getchar();
//		printf("%s", "\n");
//	} while (num < low || num > high);
//
//	return num;
//}

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
		cout << "¬ведите значение от " << low << " до " << high << ": ";
		cin >> num;
		cout << endl;
	} while (num < low || num > high || !cin.good());

	return num;
}