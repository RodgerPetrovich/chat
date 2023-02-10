#pragma once

#include <stdlib.h>
#include "container.h"
#include "user.h"
#include "message.h"
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>


string name;
string login;
string password;
string currentUser;


void readMessage();
void writeMessage();
void userMenu();
void showUsers();

Container<User> users;
Container<Message> messages;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void reg()
{
	SetConsoleTextAttribute(hConsole, 11);
	cout << "������� ��� ������������: ";
	cin >> name;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getName() == name) throw "������������ � ����� ������ ��� ����������";
	}
	cout << "Enter login: ";
	cin >> login;
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getLogin() == login) throw "������ ����� �����";
	}
	while (true)
	{
		cout << "E������� ������ (������� 6 ��������): " << endl;
		cin >> password;

		if (password.length() <= 5)
		{
			SetConsoleTextAttribute(hConsole, 12);
			cout << "������ ������� ��������" << endl << endl;
			cout << "������� q ��� �������� � ����" << endl << endl;

			if (password == "q")
			{
				break;
				//exit(0);
			}
		}
		else
			break;
	}

	users.addItem(User(name, login, password));
}

bool signUp()
{
	SetConsoleTextAttribute(hConsole, 13);
	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	cin >> password;
	for (int i = 0; i < users.getSize(); ++i)
	{
		if (users[i].getLogin() == login && users[i].getPassword() == password)
		{
			system("cls");
			cout << "������ " << users[i].getName() << "!" << endl;
			currentUser = users[i].getName();
			return true;
		}					
	}
	throw "�������� ����� ��� ������";
}



void userMenu()
{
	SetConsoleTextAttribute(hConsole, 14);
	cout << "������� [r] - ��������� ���������; [w] - �������� ���������; [s] - ������� ������ �������������; ����� ������ ������ ��� �������� � ������� ����" << endl;
	char ch = 'null';
	cin >> ch;
	switch (ch)
	{
	case 'r':
		
		readMessage();
		break;
	case 'w':
		try { writeMessage(); }
		catch (const char* ex)
		{
			cout << ex << endl;
			userMenu();
		}
		break;
	case 's':
		showUsers();
		break;
	default:
		break;
	}
}

void readMessage()
{
	 
	for (int i = 0; i < messages.getSize(); i++)
	{
		if (messages[i].getTo() == currentUser || messages[i].getTo() == "all")
			cout << messages[i].getFrom() << ": " << messages[i].getMessage() << endl;
	}
	userMenu();
}

void writeMessage()
{
	
	string to;
	string sms;
	bool test = false;
	SetConsoleTextAttribute(hConsole, 9);
	cout << "������� ��� ��������(��� ������� all ����� ��������� ��������� ���� �������������)\n: ";
	cin >> to;
  cin.ignore();
	for (int i = 0; i < users.getSize(); i++)
	{
		if (users[i].getName() == to || to == "all")
		{
			test = true;
			continue;
		}
	}
	if (test == false) throw "������������ � ����� ������ ��� � ���� ����, ��������� ������ �������������";
	cout << "������� ���������: ";
	getline(cin, sms);
	messages.addItem(Message(currentUser, to, sms));
	userMenu();
}

void showUsers()
{
	SetConsoleTextAttribute(hConsole, 11);
	cout << "=============================================" << endl;
	for (int i = 0; i < users.getSize();i++)
	{
		cout << i + 1 << ". " << users[i].getName() << endl;
	}
	cout << "=============================================" << endl;
	userMenu();
}