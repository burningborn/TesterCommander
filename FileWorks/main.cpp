#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
#define MUTE

void create_big_file(string fname, int row_count) {
	// создаем поток файла
	ofstream out;
	// открываем файл на запись data
	out.open(fname, ofstream::out);
	// записываем
	for (int i = 0; i < row_count; i++)
		out << i + 1 << ": some data" << endl;
	out.close();

}

string get_string_with_number(string fname, int number) {
	ifstream input(fname, ofstream::in);

	int row_count;
	input >> row_count;
	string* rows = new string[row_count];
	for (int i = 0; i < row_count && !input.eof(); i++)
	{
		string row;
		getline(input, rows[i]);
		
	}
	input.close();

	string res = rows[number - 1];
	delete[]rows;
	return res;
}

int main() 
{
	srand(time(0));

#ifdef MUTE
	FILE* w = fopen("test.txt", "w");
	if (w == NULL)
	{
		cout << "Oops!" << endl;
		return -1;
	}
	else
	{
		cout << "w = " << _fileno(w) << endl;
	}
	fprintf(w, "Hello from program!");
	fclose(w);
	FILE* r = fopen("test.txt", "r");
	if (r == NULL)
	{
		cout << "Oops!" << endl;
		return -1;
	}
	cout << "r = " << _fileno(r) << endl;
	while (!feof(r))
	{
		char str[100];
		fscanf(r, "%s", str);
		cout << str << " ";
	}
	cout << endl;
	fclose(r);
	ofstream out;
	out.open("test.dat", ofstream::out);
	out << "This massage write with C++ object " << 3 << endl;
	out.close();

	ifstream input("test.dat", ofstream::in);
	if (!input.is_open()) {
		cout << "Oops";
		return-1;
	}

	while (!input.eof())
	{
		string s;
		input >> s;
		cout << s << endl;
	}
	
	input.close();
#endif // MUTE

	//create_big_file("big.txt", 10000);
	//cout << get_string_with_number("big.txt", 100);
	FILE* test = fopen("TestFile.txt", "w");

	return 0;
}