#include "Reader.h"

bool operator==(const Reader& left, const Reader& right)
{
    return left.id == right.id && left.firstName == right.firstName &&
        left.secondName == right.secondName;
}

istream& operator>>(istream& in, Reader& reader)
{
    cout << "������� ������� ��������: ";
    getline(in, reader.secondName);

    cout << "������� ��� ��������: ";
    getline(in, reader.firstName);

    return in;
}


ostream& operator<<(ostream& out, const Reader& reader)
{
    out << "id: " << reader.id << endl;
    out << "������� ��������: " << reader.firstName << endl;
    out << "��� ��������: " << reader.secondName << endl;

    return out;
}