//Здесь находятся функции переименования и удаления
#include <stdio.h>
//Здесь находятся функции для поиска файлов
#include <io.h>
#include <string.h>
#include <iostream>
using namespace std;
//Переименовать существующий файл
void RenameFile();
//Удалить существующий файл
void RemoveFile();
//Создать файл
void CtreateFile();
//Поиск файлов в каталоге
void Dir();
void main()
{
	//предлагаем выбрать пункт меню для выполнения
	cout << "Please, select preffer number...\n";
	//выбор пользователя
	char ch;
	do {
		//Переименовать
		cout << "\n1 - Rename\n";
		//Удалить
		cout << "2 - Remove\n";
		//Просмотреть некоторую папку(каталог)
		cout << "3 - Create File\n";
		cout << "4 - View some folder\n";
		//Выход
		cout << "0 - Exit\n\n";
		cin >> ch;
		//анализируем и вызываем
//соответствующую функцию
		switch (ch)
		{
		case '1':
			RenameFile();
			break;
		case '2':
			RemoveFile();
			break;
		case '3':
			CtreateFile();
			break;
		case '4':
			Dir();
			break;
		}
	} while (ch != '0'); //Выход из программы
}
//Переименовать существующий файл
void RenameFile()
{
	string path;
	char oldName[50], newName[50];
	//В одной переменной запомним существующее имя
	//(oldName),
	cout << "Enter old name:";
	cin >> oldName;
	//А в другой новое имя(newName)
	cout << "Enter new name:";
	cin >> newName;
	//Произведем переименование и проверку результата
	if (rename(oldName, newName) != 0)
		cout << "Error!\n Couldn't rename file. Check old and new filename...\n\n";
	else
		cout << "Ok...\n\n";	
}
//Удалить существующий файл
void RemoveFile()
{
	char Name[50];
	//Получаем имя и путь к удаляемому файлу
	cout << "Enter name:";
	cin >> Name;
	//Удаляем файл и проверяем результат
	if (remove(Name) != 0)
		cout << "Error!\n Couldn't remove file. Check filename...\n";
	else
		cout << "Ok...\n";
}
void CtreateFile()
{
	char Name[50];

}
//Поиск файлов в каталоге
void Dir()
{
	//Запросим ПУТЬ (например, папка Temp на диске C,
	//запишется таким вот образом: c:\temp\)
	char path[70];
	cout << "\nEnter full path (for example, C:\\):";
	cin >> path;
	//Запросим маску файлов
	char mask[15];
	cout << "\nEnter mask (for example, *.* or *.txt):";
	cin >> mask;
	//Соединив две строки, мы получим результат
	//т.е. что хочет найти пользователь и где
	strcat(path, mask);
	//Объявление указателя fileinfo
//на структуру _finddata_t
//и создание динамического объекта
//структуры _finddata_t
	_finddata_t* fileinfo = new _finddata_t;
	//Начинаем поиск
	long done = _findfirst(path, fileinfo);
	//если done будет равняться -1,
	//то поиск вести бесмысленно
	int MayWeWork = done;
	//Счетчик, содержит информацию о количестве
	//найденых файлов.
	int count = 0;
	while (MayWeWork != -1)
	{
		count++;
		//Распечатали имя найденного файла
		cout << fileinfo->name << "\n\n";
		//Пытаемся найти следующий файл из группы
		MayWeWork = _findnext(done, fileinfo);
	}
	//Вывод сообщения о количестве найденных файлов.
	cout << "\nInformation: was found " << count;
	cout << " file(s) in folder..." << path << "\n\n";
	//Очистка памяти
	_findclose(done);
	delete fileinfo;
}