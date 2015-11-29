#include "SystemFiles.h"
#include <cstdlib>


void DeleteFile(SystemFiles* systemFiles)
{
	string fileName;
	cout << "Podaj nazwe pliku: ";
	cin.ignore();
	getline(cin, fileName);
	if (systemFiles->FileIsOnlyRead(fileName))
		cout << "Plik systemowy! Nie mozna usuwac.";
	getchar();
}

void EditFile(SystemFiles* systemFiles)
{
	system("cls");
	string oldName;
	cout << "Podaj nazwe pliku: ";
	cin.ignore();
	getline(cin, oldName);
	if (systemFiles->FileIsOnlyRead(oldName))
	{
		cout << "Plik systemowy! Nie mozna edytowac.";
	}
	else
	{
		char* content = systemFiles->OpenFile(oldName);
		system("cls");
		if (content != "")
		{
			cout << "Edytujesz plik o nazwie " << oldName << ":" << endl;
			cout << content << endl;
		}
		string newName;
		cout << "Podaj nowa nazwe pliku: ";
		getline(cin, newName);
		cout << "Podaj tresc: ";
		string text;
		getline(cin, text);
		if (systemFiles->EditFile(newName, oldName, text) == -1)
			cout << "Za ma³o miejsca na dysku!!";
	}
	getchar();
}

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
	cout << "Ustal prawa dostepu 0. Tylko odczyt 1. Pelna kontrola  : ";
	int law;
	cin >> law;
	if (systemFiles->AddFile(name, text, law) == -1)
		cout << "Za ma³o miejsca na dysku!!";
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
		system("cls");
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

		cout << endl <<"1. Dodaj plik  2. Pokaz tablice indeksowa oraz pamiec 3. Otworz plik  4. Usun \n5. Wyswietl katalog  6. Edytuj plik" << endl;
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
				cout << systemFiles->MemoryToString()<<endl <<endl;
				cout << systemFiles->SectorsToString() << endl;
				system("pause");
				break;
			}
			case '3':
			{
				OpenFile(systemFiles);
				break;
			}
			case '4':
			{
				DeleteFile(systemFiles);
				break;
			}
			case '5':
			{
				cout << systemFiles->CatalogToString() << endl;
				system("pause");
				break;
			}
			case '6':
			{
				EditFile(systemFiles);
				system("pause");
				break;
			}
		}
	}
	return 0;
}