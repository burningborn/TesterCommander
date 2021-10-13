#include <io.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
using std::cout;
using std::cin;
#define MUTE
/*
Метод добавления строки в файл. [DONE]
Метод очистки файла (не удаление)[DONE]
Метод копирования файла по указанному пути []*/

void addStrToFile();//Метод добавления строки в файл
void clearFile();		//Метод очистки файла (не удаление)
void RussianMessage(const char* str);
void copyFileTo();		//Метод копирования файла по указанному пути
bool CopyFile(char* source, char* destination);

int main()
{
	//srand(time(0));
	setlocale(LC_ALL, "Russian");
#ifdef MUTE
	//предлагаем выбрать пункт меню для выполнения
	cout << " Выберите действие из списка:\n";
	//выбор пользователя
	char choice;
	do
	{
		//Метод добавления строки в файл
		cout << "\n 1 - Добавить строку в файл\n";
		//Метод очистки файла (не удаление)
		cout << " 2 - Очистить файл\n";
		//Метод копирования файла по указанному пути
		cout << " 3 - Копировать файл по указанному адресу\n";	
		//Выход
		cout << " 0 - Выход\n\n";
		cin >> choice;
		//анализируем и вызываем соответствующую функцию
		switch (choice)
		{
		case '1':
			addStrToFile();
			break;
		case '2':
			clearFile();
			break;
		case '3':
			copyFileTo();
			break;
		}
	} while (choice !='0');
#endif // MUTE
	//addStrToFile();
	//clearFile();
	//copyFileTo();
	return 0;
}

void addStrToFile()			//Метод добавления строки в файл
{
	cout << "Введите имя файла для добавления в него строки :\n";
	string name;
	getline(cin, name);//принимаем имя файла для добавления в него информации 

	ofstream ofs;      //создаём поток
	ofs.open(name, ofstream::app);	//открываем файл на добавление информации
	if (!ofs.is_open())				//проверяем что файл открыт
	{
		cout << "Ошибка открытия файла!\n";
	}
	else
	{
		cout << "Файл открыт\n";
		string str;				//создаём строку для приёма информации
		cout << "Введите строку для добавления её в файл\n";
		getline(cin, str);		//принимаем информацию в строку 
		ofs << str;				//добавляем информацию в файл
		cout << "Строка успешно добавлена\n";
	}
	ofs.close();				//закрываем файл
}
void clearFile()			//Метод очистки файла (не удаление)
{
	cout << "Введите имя файла который нужно очистить:\n";
	string name;
	getline(cin, name);//принимаем имя файла для удаления из него информации 

	ofstream ofs;      //создаём поток
	ofs.open(name, ofstream::out);	//открываем файл и удаляем из него информацию
	if (!ofs.is_open())				//проверяем что файл открыт
	{
		cout << "Ошибка открытия файла!\n";
	}
	else
	{
		cout << "Содержимое файла успешно удалено!\n";
	}
	ofs.close();				//закрываем файл
}
void RussianMessage(const char* str)//Функция, выводящая на экран строку
{
	char message[100];
	//перевод строки из кодировки Windows
	//в кодировку MS DOS
	CharToOem(str, message);
	cout << message;
}
void copyFileTo()			//Метод копирования файла по указанному пути
{
	//MAX_PATH - Константа, определяющая
	//максимальный размер пути.
	//Даная константа содержится в stdlib.h
	char source[_MAX_PATH];
	char destination[_MAX_PATH];
	char answer[20];
	RussianMessage("\nEnter name & path for copied file : \n");
	//Получение пути к первому файлу
	cin.getline(source, _MAX_PATH);
	//Проверка Существует ли файл
	if (_access(source, 00) == -1) {
		RussianMessage("\nWroeng name or path of file\n");

		return;
	}
	RussianMessage("\nEnter name & path for new file:\n");

	//Получение пути к второму файлу
	cin.getline(destination, _MAX_PATH);
	//Проверка на существование файла
	if (_access(destination, 00) == 0) {
		RussianMessage("\nFile already exist, overwrite it(1 - Yes / 2 - No) ? \n");
		cin.getline(answer, 20);
		if (!strcmp(answer, "2")) {
			RussianMessage("\nOperation canceled\n");
			return;
		}
		else if (strcmp(answer, "1")) {
			RussianMessage("\nWrong input\n");
			return;
		}
		if (_access(destination, 02) == -1) {
			RussianMessage("\nNo write access.\n");
			return;
		}
	}
	//Копирование файла
	if (!CopyFile(source, destination)) {
		RussianMessage("\nFile error\n");
	}
}
bool CopyFile(char* source, char* destination) //Функция копирования файла
{
	const int size = 65536;
	FILE* src, * dest;
	//Открытие Файла
	if (!(src = fopen(source, "rb"))) {
		return false;
	}
	//Получение дескриптора файла
	int handle = _fileno(src);
	//выделение памяти под буффер
	char* data = new char[size];
	if (!data) {
		return false;
	}
	//Открытие файла, куда будет производиться копирование
	if (!(dest = fopen(destination, "wb"))) {
		delete[]data;
		return false;
	}
	int realsize;
	while (!feof(src)) {
		//Чтение данных из файла
		realsize = fread(data, sizeof(char), size, src);
		//Запись данных в файл
		fwrite(data, sizeof(char), realsize, dest);
	}
	//Закрытие файлов
	fclose(src);
	fclose(dest);
	return true;
}