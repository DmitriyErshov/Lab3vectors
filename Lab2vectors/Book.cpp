#include "Book.h"

bool operator==(const Book& left, const Book& right)
{
    return left.id == right.id && left.name == right.name &&
        left.author == right.author;
}

istream& operator>>(istream& in, Book& book)
{
    cout << "Введите дату выдачи: ";
    getline(in, book.issuingBookDate);

    cout << "Введите срок возврата: ";
    getline(in, book.returnBookDeadline);

    cout << "Введите автора: ";
    getline(in, book.author);

    cout << "Введите название: ";
    getline(in, book.name);

    cout << "Введите год издания: ";
    getline(in, book.publicationDate);

    cout << "Введите издательство: ";
    getline(in, book.publisher);

    cout << "Введите цену: ";
    in >> book.price;

    char k = getchar();

    return in;
}

ostream& operator<<(ostream& out, const Book& book)
{
    out << "id книги: " << book.id << endl;
    if (book.idReaders == -1) {
        out << "Книга свободна ";
    }
    else {
        out << "Книга на руках у читателя с id : " << book.idReaders;
    }
    out << endl;

    out << "Дата выдачи: " << book.issuingBookDate << endl;
    out << "Срок возврата: " << book.returnBookDeadline << endl;
    out << "Автор: " << book.author << endl;
    out << "Название: " << book.name << endl;
    out << "Год издания: " << book.publicationDate << endl;
    out << "Издательство: " << book.publisher << endl;
    out << "Цена: " << book.price << endl;
    out << "----------------------------------" << endl;
    return out;
}
