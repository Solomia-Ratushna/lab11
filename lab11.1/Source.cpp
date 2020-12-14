#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void CreateBIN(char* fname) // ��������� ����� ������� � �������� �����
{
	ofstream fout(fname, ios::binary); // ������� ���� ��� ������
	char ch; // ������� ����������� � �� ������������ ��������
	string s; // �������� ������������ �����
	do
	{
		cin.get(); // ������� ����� ��������� � ��� �� ���� �������
		cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
		cout << "enter line: "; getline(cin, s); // ����� �����
		for (unsigned i = 0; i < s.length(); i++) // ������� �������� �����
			fout.write((char*)&s[i], sizeof(s[i])); // �������� ������ � ����
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname) // ��������� ����� �� �����
{
	ifstream fin(fname, ios::binary); // ������� ���� ��� ����������
	char c; // ���������� ������
	while (fin.read((char*)&c, sizeof(c))) // ���� ����� ��������� ������
	{
		cout << c << endl; // �������� ���� �� �����
	}
	cout << endl;
}
void ProcessBIN1(char* fname, char* gname) // ���������� �� ����� f
{ // � ���� g �������-�����
	ifstream f(fname, ios::binary); // ������� ���� ��� ����������
	ofstream g(gname, ios::binary); // ������� ���� ��� ������
	char c; // ���������� ������
	while (f.read((char*)&c, sizeof(c))) // ���� ����� ��������� ������
	{
		if (c >= '0' && c <= '9') // ���� ������ � ������
			g.write((char*)&c, sizeof(c)); // �������� ���� � ���� g
	}
}
void fWrite(fstream& f, const int i, const char x)
{
	f.seekp(i * (long)sizeof(char)); // ���������� ��������
	f.write((char*)&x, sizeof(char)); // �������� ��������
}

char fRead(fstream & f, const int i)
{
	char x;
	f.seekg(i * (long)sizeof(char)); // ���������� ��������
	f.read((char*)&x, sizeof(char)); // ��������� ��������
	return x;
}
void fChange(fstream& f, const int i, const int j)
{
	char x = fRead(f, i);
	char y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void SortBIN(char* fname) // ���������� ����� � �� ���������
{ // ������� ������� �� �����
	fstream f(fname, ios::binary | ios::in | ios::out);
	// ����'������ ��� ������� ������
	// ios::binary | ios::in | ios::out
   // - ������� ����, ��� �����
	// ��������� ������� ��������
   // - ���������� ��
	// - ������
	f.seekg(0, ios::end);
	int size = f.tellg();
	f.seekg(0, ios::beg);
	for (int i0 = 1; i0 < size; i0++)
		for (int i1 = 0; i1 < size - i0; i1++)
		{
			char a = fRead(f, i1);
			char b = fRead(f, i1 + 1);
			if (a > b)
				fChange(f, i1, i1 + 1);
		}
	f.seekp(0, ios::end);
}
void SortBIN(char* fname, char* gname) // ���������� ����� � �� ���������
{ // ����������� �������: �������
 // � ������ ����� � �������� � �����
	ofstream g(gname, ios::binary); // ������� ���� ��� ���������� � ������
	char s, mins, z = 0; // s � ���������� � ����� f ������
	// mins � ������, ���� ���������
	// ���������
   // z - ��������� � ���� g ������
	int k; // - �����, �� � �� �������, �� ���
	// �������� � ���� g
	do // ���� ������ ���������� �������
	{ // � ���, �� �� �� ������� � ���� g
		k = 0; // ��������� �������� �������,
		// �� ��� ��������
		ifstream f(fname, ios::binary); // ������� ������ ���� ��� ����������
		// ����� ������ ������ ���� � �������
		
			// ���� ������� ������ ���������� �� �� �� ��������� �������
			while (f.read((char*)&s, sizeof(char))) // ���� ����� ���������
			{ // �������
				if (s <= z) // ���� ��� ������ ��� ��������� � ���� g
					continue; // - ���������� ����
				mins = s; // ������� ������ �� �� ��������� ������
				// - ���������
				k++; // ������� �� �� ��������� ������
				// - �������� ��������
				break; // ������ � ����� ��������� �����
			} // mins ����������� ��������
			// ���� ������ ���������� �� �� �� ��������� �������
		while (f.read((char*)&s, sizeof(char))) // ���� ����� ���������
		{ // �������
			if (s <= z) // ���� ��� ������ ��� ��������� � ���� g
				continue; // - ���������� ����
			if (s < mins) // ���� ���������� ������ ������
			{ // ����������
				mins = s; // - ������� ���� ���������
				k++; // �������� �������� �� �� ���������
			} // �������
		}
		// ����� ���������� � �� ��������� ����� � ���� g
		z = mins; // ������ ���������� ���������
		// ��������� � �� ��������� �������
		if (k > 0) // ���� ���� ������� �� �� �������
			g.write((char*)&z, sizeof(char)); // ������� - ��������
			// ��������� � ���
		f.close(); // ������� ������ ����
	} // ��� ���� ������ ���� � �������
	while (k > 0); // ����������, ���� � �� ������� �����
}
int main()
{
	// binary files
	char fname[100]; // ��'� ������� �����
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname); // ����� ����� ����� � ���������
	PrintBIN(fname); // ������ ���� ������� ����� �� �����
	char gname[100]; // ��'� ������� �����
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname); // ������ ���� ������� ����� �� �����
	SortBIN(fname, gname); // ����������� ������� �����,
	PrintBIN(gname); // ������ ���� ����� �� �����
	SortBIN(fname); // ����������� ������� �����,
	PrintBIN(fname); // ������ ���� ����� �� �����
	return 0;
}