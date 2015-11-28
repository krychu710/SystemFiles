#include "SystemFiles.h"
#include <cstdlib>

void AddFile(SystemFiles* systemFiles)
{
	system("cls");
	string name;
	cout << "Podaj nazwe pliku: ";
	cin.ignore();
	getline(cin, name);
	cout << "Podaj tresc: ";
	string text;
	getline(cin, text);
	systemFiles->AddFile(name, text);
	getchar();
}
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
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "|     Nazwa     | Z. miejsce | R. rozmiar |      Data utworzenia      |" << endl;
		cout << "-----------------------------------------------------------------------" << endl;
		list<File*> files = systemFiles->GetNamesFiles();
		if (!files.empty())
		for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
			cout << "|" << setw(14) << (*i)->GetName() << " |" << setw(10) << (*i)->GetOccupiedSpace() << "B |" << setw(10) << (*i)->GetRealSize() << "B |" << setw(26) << (*i)->DateCreatedToChar();
		else
			cout << "|                 BRAK PLIKOW NA DYSKU! " << endl;

		cout << "-----------------------------------------------------------------------" << endl;

		cout << endl <<"1. Dodaj plik  2. Pokaz tablice indeksowa oraz pamiec 3. Otworz plik " << endl;
		cin >> item;
		switch (item)
		{
			case '1':
			{
				AddFile(systemFiles);
				break;
			}
			case '2':
			{
				cout << systemFiles->MemoryToString();
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