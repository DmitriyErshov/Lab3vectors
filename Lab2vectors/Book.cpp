#include "Book.h"

bool operator==(const Book& left, const Book& right)
{
    return left.id == right.id && left.name == right.name &&
        left.author == right.author;
}

istream& operator>>(istream& in, Book& book)
{
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

    char k = getchar();

    return in;
}

ostream& operator<<(ostream& out, const Book& book)
{
    out << "id �����: " << book.id << endl;
    if (book.idReaders == -1) {
        out << "����� �������� ";
    }
    else {
        out << "����� �� ����� � �������� � id : " << book.idReaders;
    }
    out << endl;

    out << "���� ������: " << book.issuingBookDate << endl;
    out << "���� ��������: " << book.returnBookDeadline << endl;
    out << "�����: " << book.author << endl;
    out << "��������: " << book.name << endl;
    out << "��� �������: " << book.publicationDate << endl;
    out << "������������: " << book.publisher << endl;
    out << "����: " << book.price << endl;
    out << "----------------------------------" << endl;
    return out;
}
