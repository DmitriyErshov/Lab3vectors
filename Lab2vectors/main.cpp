#include "utills.h"
#include "Book.h"
#include "BooksContainer.h"
#include "ReadersContainer.h"
#include "BooksBorrowingLogsContainer.h"
#include "input.h"
#include "menu.h"

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Menu menu;
	menu.run();

	return 0;
}

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