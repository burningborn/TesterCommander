//����� ��������� ������� �������������� � ��������
#include <stdio.h>
//����� ��������� ������� ��� ������ ������
#include <io.h>
#include <string.h>
#include <iostream>
using namespace std;
//������������� ������������ ����
void RenameFile();
//������� ������������ ����
void RemoveFile();
//������� ����
void CtreateFile();
//����� ������ � ��������
void Dir();
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
		//����������� ��������� �����(�������)
		cout << "3 - Create File\n";
		cout << "4 - View some folder\n";
		//�����
		cout << "0 - Exit\n\n";
		cin >> ch;
		//����������� � ��������
//��������������� �������
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
	} while (ch != '0'); //����� �� ���������
}
//������������� ������������ ����
void RenameFile()
{
	string path;
	char oldName[50], newName[50];
	//� ����� ���������� �������� ������������ ���
	//(oldName),
	cout << "Enter old name:";
	cin >> oldName;
	//� � ������ ����� ���(newName)
	cout << "Enter new name:";
	cin >> newName;
	//���������� �������������� � �������� ����������
	if (rename(oldName, newName) != 0)
		cout << "Error!\n Couldn't rename file. Check old and new filename...\n\n";
	else
		cout << "Ok...\n\n";	
}
//������� ������������ ����
void RemoveFile()
{
	char Name[50];
	//�������� ��� � ���� � ���������� �����
	cout << "Enter name:";
	cin >> Name;
	//������� ���� � ��������� ���������
	if (remove(Name) != 0)
		cout << "Error!\n Couldn't remove file. Check filename...\n";
	else
		cout << "Ok...\n";
}
void CtreateFile()
{
	char Name[50];

}
//����� ������ � ��������
void Dir()
{
	//�������� ���� (��������, ����� Temp �� ����� C,
	//��������� ����� ��� �������: c:\temp\)
	char path[70];
	cout << "\nEnter full path (for example, C:\\):";
	cin >> path;
	//�������� ����� ������
	char mask[15];
	cout << "\nEnter mask (for example, *.* or *.txt):";
	cin >> mask;
	//�������� ��� ������, �� ������� ���������
	//�.�. ��� ����� ����� ������������ � ���
	strcat(path, mask);
	//���������� ��������� fileinfo
//�� ��������� _finddata_t
//� �������� ������������� �������
//��������� _finddata_t
	_finddata_t* fileinfo = new _finddata_t;
	//�������� �����
	long done = _findfirst(path, fileinfo);
	//���� done ����� ��������� -1,
	//�� ����� ����� �����������
	int MayWeWork = done;
	//�������, �������� ���������� � ����������
	//�������� ������.
	int count = 0;
	while (MayWeWork != -1)
	{
		count++;
		//����������� ��� ���������� �����
		cout << fileinfo->name << "\n\n";
		//�������� ����� ��������� ���� �� ������
		MayWeWork = _findnext(done, fileinfo);
	}
	//����� ��������� � ���������� ��������� ������.
	cout << "\nInformation: was found " << count;
	cout << " file(s) in folder..." << path << "\n\n";
	//������� ������
	_findclose(done);
	delete fileinfo;
}