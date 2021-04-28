#include "Book.h"

bool operator==(const Book& left, const Book& right)
{
    return left.id == right.id && left.name == right.name &&
        left.author == right.author;
}

istream& operator>>(istream& in, Book& book)
{
    cout << "������� id ������������� ������: ";
    in >> book.id;
    char k = getchar();

    cout << "������� ������� ��������: ";
    getline(in, book.clientSecondName);

    cout << "������� ���� ������: ";
    getline(in, book.issuingBookDate);

    cout << "������� ���� ��������: ";
    getline(in, book.returnBookDeadline);

    cout << "������� ������: ";
    getline(in, book.author);

    cout << "������� ��������: ";
    getline(in, book.name);

    cout << "������� ��� �������: ";
    getline(in, book.publicationDate);

    cout << "������� ������������: ";
    getline(in, book.publisher);

    cout << "������� ����: ";
    in >> book.price;

    k = getchar();

    return in;
}

ostream& operator<<(ostream& out, const Book& book)
{
    out << "������������ ����� �: " << book.id << endl;
    out << "������� ��������: " << book.clientSecondName << endl;
    out << "���� ������: " << book.issuingBookDate << endl;
    out << "���� ��������: " << book.returnBookDeadline << endl;
    out << "�����: " << book.author << endl;
    out << "��������: " << book.name << endl;
    out << "��� �������: " << book.publicationDate << endl;
    out << "������������: " << book.publisher << endl;
    out << "����: " << book.price << endl;

    return out;
}
