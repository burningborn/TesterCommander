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
����� ���������� ������ � ����. [DONE]
����� ������� ����� (�� ��������)[DONE]
����� ����������� ����� �� ���������� ���� []*/

void addStrToFile();//����� ���������� ������ � ����
void clearFile();		//����� ������� ����� (�� ��������)
void RussianMessage(const char* str);
void copyFileTo();		//����� ����������� ����� �� ���������� ����
bool CopyFile(char* source, char* destination);

int main()
{
	//srand(time(0));
	setlocale(LC_ALL, "Russian");
#ifdef MUTE
	//���������� ������� ����� ���� ��� ����������
	cout << " �������� �������� �� ������:\n";
	//����� ������������
	char choice;
	do
	{
		//����� ���������� ������ � ����
		cout << "\n 1 - �������� ������ � ����\n";
		//����� ������� ����� (�� ��������)
		cout << " 2 - �������� ����\n";
		//����� ����������� ����� �� ���������� ����
		cout << " 3 - ���������� ���� �� ���������� ������\n";	
		//�����
		cout << " 0 - �����\n\n";
		cin >> choice;
		//����������� � �������� ��������������� �������
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

void addStrToFile()			//����� ���������� ������ � ����
{
	cout << "������� ��� ����� ��� ���������� � ���� ������ :\n";
	string name;
	getline(cin, name);//��������� ��� ����� ��� ���������� � ���� ���������� 

	ofstream ofs;      //������ �����
	ofs.open(name, ofstream::app);	//��������� ���� �� ���������� ����������
	if (!ofs.is_open())				//��������� ��� ���� ������
	{
		cout << "������ �������� �����!\n";
	}
	else
	{
		cout << "���� ������\n";
		string str;				//������ ������ ��� ����� ����������
		cout << "������� ������ ��� ���������� � � ����\n";
		getline(cin, str);		//��������� ���������� � ������ 
		ofs << str;				//��������� ���������� � ����
		cout << "������ ������� ���������\n";
	}
	ofs.close();				//��������� ����
}
void clearFile()			//����� ������� ����� (�� ��������)
{
	cout << "������� ��� ����� ������� ����� ��������:\n";
	string name;
	getline(cin, name);//��������� ��� ����� ��� �������� �� ���� ���������� 

	ofstream ofs;      //������ �����
	ofs.open(name, ofstream::out);	//��������� ���� � ������� �� ���� ����������
	if (!ofs.is_open())				//��������� ��� ���� ������
	{
		cout << "������ �������� �����!\n";
	}
	else
	{
		cout << "���������� ����� ������� �������!\n";
	}
	ofs.close();				//��������� ����
}
void RussianMessage(const char* str)//�������, ��������� �� ����� ������
{
	char message[100];
	//������� ������ �� ��������� Windows
	//� ��������� MS DOS
	CharToOem(str, message);
	cout << message;
}
void copyFileTo()			//����� ����������� ����� �� ���������� ����
{
	//MAX_PATH - ���������, ������������
	//������������ ������ ����.
	//����� ��������� ���������� � stdlib.h
	char source[_MAX_PATH];
	char destination[_MAX_PATH];
	char answer[20];
	RussianMessage("\nEnter name & path for copied file : \n");
	//��������� ���� � ������� �����
	cin.getline(source, _MAX_PATH);
	//�������� ���������� �� ����
	if (_access(source, 00) == -1) {
		RussianMessage("\nWroeng name or path of file\n");

		return;
	}
	RussianMessage("\nEnter name & path for new file:\n");

	//��������� ���� � ������� �����
	cin.getline(destination, _MAX_PATH);
	//�������� �� ������������� �����
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
	//����������� �����
	if (!CopyFile(source, destination)) {
		RussianMessage("\nFile error\n");
	}
}
bool CopyFile(char* source, char* destination) //������� ����������� �����
{
	const int size = 65536;
	FILE* src, * dest;
	//�������� �����
	if (!(src = fopen(source, "rb"))) {
		return false;
	}
	//��������� ����������� �����
	int handle = _fileno(src);
	//��������� ������ ��� ������
	char* data = new char[size];
	if (!data) {
		return false;
	}
	//�������� �����, ���� ����� ������������� �����������
	if (!(dest = fopen(destination, "wb"))) {
		delete[]data;
		return false;
	}
	int realsize;
	while (!feof(src)) {
		//������ ������ �� �����
		realsize = fread(data, sizeof(char), size, src);
		//������ ������ � ����
		fwrite(data, sizeof(char), realsize, dest);
	}
	//�������� ������
	fclose(src);
	fclose(dest);
	return true;
}