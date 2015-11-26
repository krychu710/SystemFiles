#include "SystemFiles.h"
#include <cstdlib>




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
				systemFiles->ShowSectors();
				break;
			}
			case '3':
			{
				string name;
				cout << "Podaj nazwe pliku: ";
				cin.ignore();
				getline(cin, name);
				systemFiles->OpenFile(name);
				break;
			}

		}

		cout << "--------------------" << endl;
	}
	return 0;
}