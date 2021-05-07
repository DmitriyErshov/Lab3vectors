#pragma once
#include "utills.h"
#include <limits>


//void showCommands(string s, ...)
//{
//	int result = 0;
//	// �������� ��������� �� �������� n
//	for (string* ptr = &s; s > 0; s--)
//	{
//		result += *(++ptr);
//	}
//}

//int inputNumberInRange(int low, int high) {
//	char k;
//	//��� ����� ��������� ���������� 
//	int num = 0;
//	do {
//		printf("������� �������� �� %d �� %d: ", low, high);
//		scanf_s("%d", &num);
//		k = getchar();
//		printf("%s", "\n");
//	} while (num < low || num > high);
//
//	return num;
//}

int inputNumberInRange(int low, int high) {
	char k;
	//��� ����� ��������� ���������� 
	int num = 0;
	do {
		/*if (char(cin.peek()) == '\n')
			cin.ignore();*/

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		cout << "������� �������� �� " << low << " �� " << high << ": ";
		cin >> num;
		cout << endl;
	} while (num < low || num > high || !cin.good());

	return num;
}