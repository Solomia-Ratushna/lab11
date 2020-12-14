#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void CreateBIN(char* fname) // створення файлу символів з введених рядків
{
	ofstream fout(fname, ios::binary); // відкрили файл для запису
	char ch; // відповідь користувача – чи продовжувати введення
	string s; // введений користувачем рядок
	do
	{
		cin.get(); // очищуємо буфер клавіатури – щоб не було символу
		cin.sync(); // "кінець рядка", який залишився після вводу числа
		cout << "enter line: "; getline(cin, s); // ввели рядок
		for (unsigned i = 0; i < s.length(); i++) // скануємо введений рядок
			fout.write((char*)&s[i], sizeof(s[i])); // записали символ у файл
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname) // виведення файлу на екран
{
	ifstream fin(fname, ios::binary); // відкрили файл для зчитування
	char c; // прочитаний символ
	while (fin.read((char*)&c, sizeof(c))) // поки можна прочитати символ
	{
		cout << c << endl; // виводимо його на екран
	}
	cout << endl;
}
void ProcessBIN1(char* fname, char* gname) // переписати із файлу f
{ // у файл g символи-цифри
	ifstream f(fname, ios::binary); // відкрили файл для зчитування
	ofstream g(gname, ios::binary); // відкрили файл для запису
	char c; // прочитаний символ
	while (f.read((char*)&c, sizeof(c))) // поки можна прочитати символ
	{
		if (c >= '0' && c <= '9') // якщо символ є цифрою
			g.write((char*)&c, sizeof(c)); // записуємо його у файл g
	}
}
void fWrite(fstream& f, const int i, const char x)
{
	f.seekp(i * (long)sizeof(char)); // встановили вказівник
	f.write((char*)&x, sizeof(char)); // записали значення
}

char fRead(fstream & f, const int i)
{
	char x;
	f.seekg(i * (long)sizeof(char)); // встановили вказівник
	f.read((char*)&x, sizeof(char)); // прочитали значення
	return x;
}
void fChange(fstream& f, const int i, const int j)
{
	char x = fRead(f, i);
	char y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void SortBIN(char* fname) // сортування файлу – за допомогою
{ // прямого доступу до файлу
	fstream f(fname, ios::binary | ios::in | ios::out);
	// обов'язково слід вказати режими
	// ios::binary | ios::in | ios::out
   // - бінарний файл, для якого
	// одночасно доступні операції
   // - зчитування та
	// - запису
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
void SortBIN(char* fname, char* gname) // сортування файлу – за допомогою
{ // послідовного доступу: зчитуємо
 // з одного файлу і записуємо в інший
	ofstream g(gname, ios::binary); // відкрили файл для зчитування і запису
	char s, mins, z = 0; // s – прочитаний з файлу f символ
	// mins – символ, який вважається
	// найменшим
   // z - записаний у файл g символ
	int k; // - вказує, чи є ще символи, які слід
	// записати у файл g
	do // цикл запису мінімального символу
	{ // з тих, які ще не записані у файл g
		k = 0; // обнуляємо лічильник символів,
		// які слід записати
		ifstream f(fname, ios::binary); // відкрили перший файл для зчитування
		// тепер будемо читати файл з початку
		
			// цикл початку пошуку мінімального із ще не записаних символів
			while (f.read((char*)&s, sizeof(char))) // поки можна зчитувати
			{ // символи
				if (s <= z) // якщо цей символ вже записаний у файл g
					continue; // - пропускаємо його
				mins = s; // вважаємо перший ще не записаний символ
				// - мінімальним
				k++; // знайшли ще не записаний символ
				// - збільшили лічильник
				break; // вийшли з циклу присвоєння змінній
			} // mins початкового значення
			// цикл пошуку мінімального із ще не записаних символів
		while (f.read((char*)&s, sizeof(char))) // поки можна зчитувати
		{ // символи
			if (s <= z) // якщо цей символ вже записаний у файл g
				continue; // - пропускаємо його
			if (s < mins) // якщо прочитаний символ менший
			{ // мінімального
				mins = s; // - вважаємо його мінімальним
				k++; // збільшили лічильник ще не записаних
			} // символів
		}
		// запис мінімального з не записаних рядків у файл g
		z = mins; // будемо записувати знайдений
		// мінімальний з не записаних символів
		if (k > 0) // якщо були знайдені ще не записані
			g.write((char*)&z, sizeof(char)); // символи - записуємо
			// мінімальний з них
		f.close(); // закрили перший файл
	} // щоб потім читати файл з початку
	while (k > 0); // повторюємо, поки є не записані рядки
}
int main()
{
	// binary files
	char fname[100]; // ім'я першого файлу
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname); // ввели рядки файлу з клавіатури
	PrintBIN(fname); // вивели вміст першого файлу на екран
	char gname[100]; // ім'я другого файлу
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname); // вивели вміст другого файлу на екран
	SortBIN(fname, gname); // відсортували символи файлу,
	PrintBIN(gname); // вивели вміст файлу на екран
	SortBIN(fname); // відсортували символи файлу,
	PrintBIN(fname); // вивели вміст файлу на екран
	return 0;
}