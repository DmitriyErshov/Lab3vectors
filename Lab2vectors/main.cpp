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