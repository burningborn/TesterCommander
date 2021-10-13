#include <iostream>
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string>
#include <string.h>
using namespace std;
const int size = 255;
//�������, ������� ������� ������ ����� � ������� ������
void RemoveRSpacesAndRSlashes(char* str) {
	int index = strlen(str) - 1;
	while (str[index] == '\\' || str[index] == ' ') {
		index--;
	}
	strncpy(str, str, index);
	str[index + 1] = '\0';
}
//������� ��� ������ ������� ����������
void ShowCurrentDir(char path[], char temp[]) {
	CharToOem(path, temp);
	printf("%s>", temp);
}
//������� �������� �� ��������� Windows � ��������� DOS ��� ����������� ����������� ��������
void RussianMessage(char path[]) {
	CharToOem(path, path);
}
//����� �� ����� ����������� �����
bool ShowDir(char path[]) {
	//����� ����������� ������� ����������
	_finddata_t find;
	char pathfind[MAX_PATH];
	strcpy(pathfind, path);
	strcat(pathfind, "\\*.*");
	char info[MAX_PATH];
	//������ ������
	int result = _findfirst(pathfind, &find);
	//������� ������
	system("cls");
	int flag = result;
	if (flag == -1) {
		strcpy(info, "����� ���������� ���");
		RussianMessage(info);
		printf("%s\n", info);
		return false;
	}
	while (flag != -1) {
		if (strcmp(find.name, ".") && strcmp(find.name, "..")) {
			//��������� ���������� ��� ���
			find.attrib& _A_SUBDIR ? strcpy(info, " ������� ") :
				strcpy(info, " ���� ");
			RussianMessage(info);
			RussianMessage(find.name);
			printf("%30s %10s\n", find.name, info);
		}
		//���������� �����
		flag = _findnext(result, &find);
	}
	ShowCurrentDir(path, info);
	//������� �������, ���������� ��� �����
	_findclose(result);
	return true;
}
void main() {
	//� ������ ���������� ����� ���������
	//���� � ����������
	char path[MAX_PATH];
	//� ������ ���������� ����� �������, ���������
	//�������������
	char action[size];
	//��������� ����������
	char temp[MAX_PATH];
	//�������� ���� � ������� ����������
	GetCurrentDirectory(sizeof(path), path);
	bool flag = true;
	//����� ����������� ������� ����������
	ShowDir(path);
	do {
		//���� ������� ������������
		cin.getline(action, size);
		//������� ������� � ����� ������
		RemoveRSpacesAndRSlashes(action);
		//������� � �������� �������
		if (!strcmpi(action, "root")) {
			path[2] = '\0';
			ShowDir(path);
		}
		//�������� �� ������� ������������ �����
		else if (!strcmpi(action, "exit")) {
			flag = false;
		}
		//�������� �� ������� cd
		else if (!strnicmp(action, "cd", 2)) {
			//����� ����������� ������� ����������
			if ((!strcmpi(action, "cd"))) {
				//����� ����������
				ShowDir(path);
			}
			//������� cd ���� ���� � �����������
			else if (!strnicmp(action, "cd ", 3)) {
				//������� ������ ���������
				int index = strspn(action + 2, " ");
				if (index) {
					//�������� �� ������ ���� � ����������
					if (strchr(action + index + 2, ':')) {
						//������� ���������� ����������
						//����������
						if (ShowDir(action + index + 2)) {
							strcpy(path, action + index + 2);
						}
						else {
							//��������� ������
							ShowCurrentDir(path, temp);
						}
					}
					//����������� � ������������ �������
					else if (!strcmp(action + index + 2, "..")) {
						char* result = strrchr(path, '\\');
						if (result) {
							int delta = result - path;
							strncpy(temp, path, delta);
							temp[delta] = '\0';
						}
						else {
							strcpy(temp, path);
						}
						if (ShowDir(temp)) {
							strcpy(path, temp);
						}
						else {
							//��������� ������
							ShowCurrentDir(path, temp);
						}
					}
					//����� ����������
					else if (!strcmp(action + index + 2, ".")) {
						ShowDir(path);
					}
					else if (!strcmp(action + index + 2, "/")) {
						ShowDir(path);
					}
					else {
						//��� ��� �������� ����
						strcpy(temp, path);
						strcat(temp, "\\");
						strcat(temp, action + index + 2);
						//������� ���������� ����������
						//����������
						if (ShowDir(temp)) {
							strcpy(path, temp);
						}
						else {
							//��������� ������
							ShowCurrentDir(path, temp);
						}
					}
				}
				else {
					//����� ����������
					ShowDir(path);
				}
			}
			else {
				//����� ����������
				ShowDir(path);
			}
		}
		else {
			//����� ����������
			ShowDir(path);
		}
	} while (flag);
}