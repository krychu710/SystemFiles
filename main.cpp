#include "SystemFiles.h"
#include <cstdlib>


void OpenFile(SystemFiles* systemFiles)
{
	string name;
	cout << "Podaj nazwe pliku: ";
	cin.ignore();
	getline(cin, name);
	char* content = systemFiles->OpenFile(name);
	system("cls");
	if (content != "")
	{
		cout << "Tresc pliku o nazwie " << name << ":" << endl;
		cout << content << endl;
	}
	else
		cout << "Plik o podanej nazwie nie istnieje :/";
	getchar();
}



int main()
{
	SystemFiles* systemFiles = new SystemFiles();
	while (1)
	{
		char item = '0';

		cout << "Twoje pliki: " << endl;
		systemFiles->GetNamesFiles();
		cout << "--------------------------------------------------------------------" << endl;
		cout << "1. Dodaj plik  2. Pokaz tablice indeksowa oraz pamiec 3. Otworz plik " << endl;
		cin >> item;
		switch (item)
		{
			case '1':
			{
				string name;
				cout << "Podaj nazwe pliku: ";
				cin.ignore();
				getline(cin, name);
				cout << "Podaj tresc: ";
				string text;
				getline(cin, text);
				systemFiles->AddFile(name, text);
				break;
			}
			case '2':
			{
				cout << systemFiles->ShowMemory();
				break;
			}
			case '3':
			{
				OpenFile(systemFiles);
				break;
			}
			case '4':
			{
				string name;
				cout << "Podaj nazwe pliku: ";
				cin.ignore();
				getline(cin, name);
				systemFiles->DeleteFile(name);
				break;
			}

		}

		cout << "--------------------" << endl;
	}
	return 0;
}