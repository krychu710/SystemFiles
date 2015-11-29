#ifndef SAVE_DEFAULT_DATA_H
#define SAVE_DEFAULT_DATA_H
#include <fstream>

class SaveDefaultData
{
	private:
		int amount;
		string* namesFiles;
	public:
		SaveDefaultData(string* namesFiles, int amount)
		{
			this->amount = amount;
			this->namesFiles = namesFiles;
		}
		string* Save()
		{
			string* data = new string[amount];
			for (int i = 0; i < amount; i++)
			{
				data[i] =  saveToVirtualDisc(namesFiles[i]);
			}
			return data;
		}
	private:
		string saveToVirtualDisc(string name)
		{
			fstream plik;
			plik.open(name, ios::in);
			if (plik.good())
			{
				string dane;
				getline(plik, dane);
				plik.close();
				return dane;
			}
			return "";
		}
};

#endif SAVE_DEFAULT_DATA_H