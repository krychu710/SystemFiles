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
	else
		systemFiles->DeleteFile(fileName);
	getchar();
}

void EditFile(SystemFiles* systemFiles)
{
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
		int result = systemFiles->EditFile(newName, oldName, text);
		if (result == -1)
			cout << "Za ma³o miejsca na dysku!!";
		if (result == -2)
			cout << "Nie ma pliku o podanej nazwie!";
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
	int result = systemFiles->AddFile(name, text, law);
	if (result == -1)
		cout << "Za ma³o miejsca na dysku!!";
	if (result == -2)
		cout << "Plik o podanej nazwie juz istnieje!";
	system("pause");
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
		if (systemFiles->FileIsOnlyRead(name))
			cout << "Plik systemowy, tylko do odczytu." << endl;
	}
	else
		cout << "Plik o podanej nazwie nie istnieje :/";
	getchar();
}


void Menu()
{
	SystemFiles* systemFiles = new SystemFiles();
	while (1)
	{
		char item = '0';
		system("cls");
		cout << "Twoje pliki: " << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "|     Nazwa     | Z. miejsce | R. rozmiar | Prawa |    Data utworzenia      |" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		list<File*> files = systemFiles->GetNamesFiles();
		if (!files.empty())
		for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
			cout << "|" << setw(14) << (*i)->GetName() << " |" << setw(10) << (*i)->GetOccupiedSpace() << "B |" << setw(10) << (*i)->GetRealSize() << "B |" << setw(6) << (*i)->GetAccess() << " |" << setw(26) << (*i)->DateCreatedToChar();
		else
			cout << "|                 BRAK PLIKOW NA DYSKU! " << endl;

		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "Wolne miejsce na dysku: " << systemFiles->GetSizeFreeMemory() << "B" << endl;
		cout << endl << "1. Dodaj plik  2. Pokaz tablice indeksowa oraz pamiec 3. Otworz plik  \n4. Usun 5. Wyswietl katalog  6. Edytuj plik  0. Wyjscie" << endl;
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
				cout << systemFiles->MemoryToString() << endl << endl;
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
			case '0':
				return;
			default:
				break;
			
		}
	}
}

int main()
{
	Menu();
	return 0;
}