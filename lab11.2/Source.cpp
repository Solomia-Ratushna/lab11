#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
enum Special { KN, SA, IS, KB };
string specialStr[] = { "����'����� �����", "��������� �����", "����������� ��������", "ʳ����������" };
struct Student
{
	string prizv;
	int kurs;
	Special special;
	union
	{
		int physic;
		int math;
		int inform;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
double find_prozent(Student* p, const int N);
int find_studend(Student* p, const int N);
void Sort(Student* p, const int N);
void CreateBIN(char* fname);
void PrintBIN(char* fname);
void ProcessBIN1(char* fname, char* gname);
void fWrite(fstream& f, const int i, const char x);
char fRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void SortBIN(char* fname);
void SortBIN(char* fname, char* gname);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ���������� N: "; cin >> N;

	Student* p = new Student[N];
	double proc;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] -������� ��������, � ���� ������� ��� ������ 4:" << endl;
		cout << " [4] - ������� ������������� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			proc = find_prozent(p, N);
			cout << "������� ��������, � ���� ������� ��� ������ 4:" << endl;
			cout << proc << "%" << endl;
			break;
		case 4:
			Sort(p, N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	

	char fname[100];
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname);
	PrintBIN(fname);
	char gname[100];
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname);
	SortBIN(fname, gname);
	PrintBIN(gname);
	SortBIN(fname);
	PrintBIN(fname);

	return 0;
}
void Create(Student* p, const int N)
{
	int special, kurs;
	for (int i = 0; i < N; i++)
	{
		cout << " ������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������ (0 -����'����� �����, 1-��������� �����, 2-����������� ��������, 3-ʳ���������� ): ";
		cin >> special;
		p[i].special = (Special)special;
		switch (p[i].special)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << " ������ : "; cin >> p[i].physic;
			cout << " ���������� : "; cin >> p[i].math;
			cout << " ����������� : "; cin >> p[i].inform;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(11) << left << specialStr[p[i].special];
		switch (p[i].special)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].physic << " |" << setw(13) << right << "|" << endl;
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right
				<< p[i].math << " |" << endl;
			cout << "| " << setw(15) << right << "|" << " " << setw(5) << right
				<< p[i].inform << " |" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

double find_prozent(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if (p[i].physic > 3 && p[i].math > 3 && p[i].inform > 3)
			k++;
	return 100.0 * k / N;
}

int find_studend(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if (((p[i].physic + p[i].math + p[i].inform) / 3) < 4)
			k++;
	return 100.0 * k / N;


}

void Sort (Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 <N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].kurs > p[i1 + 1].kurs)
				||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].special > p[i1 + 1].special))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}


void CreateBIN(char* fname)
{
	ofstream fout(fname, ios::binary);
	char ch;
	string s;
	do
	{
		cin.get();
		cin.sync();
		cout << "enter line: "; getline(cin, s);
		for (unsigned i = 0; i < s.length(); i++)
			fout.write((char*)&s[i], sizeof(s[i]));
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname)
{
	ifstream fin(fname, ios::binary);
	char c;
	while (fin.read((char*)&c, sizeof(c)))
	{
		cout << c << endl;
	}
	cout << endl;
}
void ProcessBIN1(char* fname, char* gname)
{
	ifstream f(fname, ios::binary);
	ofstream g(gname, ios::binary);
	char c;
	while (f.read((char*)&c, sizeof(c)))
	{
		if (c >= '0' && c <= '9')
			g.write((char*)&c, sizeof(c));
	}
}
void fWrite(fstream& f, const int i, const char x)
{
	f.seekp(i * (long)sizeof(char));
	f.write((char*)&x, sizeof(char));
}
char fRead(fstream& f, const int i)
{
	char x;
	f.seekg(i * (long)sizeof(char));
	f.read((char*)&x, sizeof(char));
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
void SortBIN(char* fname, char* gname)
{
	ofstream g(gname, ios::binary);
	char s, mins, z = 0;
	int k;
	do
	{
		k = 0;
		ifstream f(fname, ios::binary);
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			mins = s;
			k++;
			break;
		}
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			if (s < mins)
			{
				mins = s;
				k++;
			}
		}

		z = mins;
		if (k > 0)
			g.write((char*)&z, sizeof(char));
		f.close();
	} while (k > 0);
}
