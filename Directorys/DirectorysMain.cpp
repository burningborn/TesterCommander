#include <iostream>
#include <direct.h>
#include <stdio.h>
using namespace std;
//������������� ������������ ����������
void RenameDirectory();
//������� ������������ ����������
void RemoveDirectory();
//������� ����������
void CreateDirectory();
void main()
{
	//���������� ������� ����� ���� ��� ����������
	cout << "Please, select preffer number...\n";
	//����� ������������
	char ch;
	do {
		//�������������
		cout << "\n1 - Rename\n";
		//�������
		cout << "2 - Remove\n";
		//�������
		cout << "3 - Create\n";
		//�����
		cout << "0 - Exit\n\n";
		cin >> ch;
		//����������� � ��������
		//��������������� �������
		switch (ch)
		{
		case '1':
			RenameDirectory();
			break;
		case '2':
			RemoveDirectory();
			break;
		case '3':
			CreateDirectory();
			break;
		}
	} while (ch != '0'); // ����� �� ���������
}
//������������� ������������ ����������
void RenameDirectory()
{
	char oldName[50], newName[50];
	//� ����� ���������� ��������
	//������������ ��� (oldName),
	cout << "Enter old name:";
	cin >> oldName;
	//� � ������ ����� ���(newName)
	cout << "Enter new name:";
	cin >> newName;
	//���������� �������������� � �������� ����������
	if (rename(oldName, newName) != 0)
		cout << "Error!\n Couldn't rename directory.\n\n";
	else
		cout << "Ok...\n\n";
}
//������� ������������ ����������
void RemoveDirectory()
{
	char Name[50];
	//�������� ��� � ���� � ��������� ����������
	cout << "Enter name:";
	cin >> Name;
	//������� ���������� � ��������� ���������
	if (_rmdir(Name) == -1)
		cout << "Error!\n Couldn't remove directory.\n";
	else
		cout << "Ok...\n";
}
//������� ����������
void CreateDirectory()
{
	char Name[50];
	//�������� ��� � ���� � ����������� ����������
	cout << "Enter name:";
	cin >> Name;
	//������� ���������� � ��������� ���������
	if (_mkdir(Name) == -1)
		cout << "Error!\n Couldn't create directory.\n";
	else
		cout << "Ok...\n";
}