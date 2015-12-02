#ifndef SYSTEMFILES_H
#define SYSTEMFILES_H

#include "File.h"
#include <sstream>
#include <iomanip>
#include "Catalog.h"
#include "SaveDefaultData.h"


class SystemFiles
{
private:
	const int sizeMemory = 256;
	const int sizeSector = 16;
	int amountSectors;
	Disc* disc;
	list<File*> files;
	Catalog* catalog;
public:
	SystemFiles()
	{
		amountSectors = sizeMemory / sizeSector;
		disc = new Disc(sizeMemory, sizeSector);
		files = list<File*>();
		catalog = new Catalog("root", &files);
		saveDefaultData();
	}
	int AddFile(string fileName, string fileContent, int access = 1)
	{
		int realSize = 0;
		int occupiedSpace = 0;
		int numberIndexBlock = disc->TrySaveFile(fileContent, realSize, occupiedSpace);
		if (numberIndexBlock == -1)
			return -1;
		if (getFile(fileName))
			return -2;
		File* file = new File(fileName, numberIndexBlock, occupiedSpace, realSize, access);
		files.push_back(file);
		return 0;
	}
	int EditFile(string newFileName, string oldFileName, string fileContent)
	{
		if (!getFile(oldFileName))
			return -2;
		int realSize = 0;
		int numberIndexBlock = checkNumberIndexBlock(oldFileName);
		if (numberIndexBlock != -1)
		{
			File* oldFile = getFile(oldFileName);
			int occupiedSpace = oldFile->GetOccupiedSpace();
			if (disc->EditFile(numberIndexBlock, fileContent, occupiedSpace, realSize) == -1)
				return -1;
			File* file = new File(newFileName, numberIndexBlock, occupiedSpace, realSize);
			files.push_back(file);
			files.remove(oldFile);
		}
		return 0;
	}
	string SectorsToString()
	{
		stringstream stream;
		int* sectors = disc->getSectors();
		for (int i = 0; i < sizeSector; i++)
		{
			stream << "[" << i << "]" << ": " << sectors[i] << " ";
			if (i == 7)
				stream << endl;
		}
		return stream.str();
	}

	string MemoryToString()
	{
		int indexMemory = 0;
		stringstream stream;
		char* memory = disc->getMemory();
		for (int i = 0; i < amountSectors; i += 4)
		{
			indexMemory = i*amountSectors;
			stream << " Sektor " << i << "\t    Sektor " << i + 1 << "\t       Sektor " << i + 2 << "          Sektor " << i + 3 << endl;
			for (int j = 0; j < amountSectors / 2; j++)
			{
				int index = indexMemory;
				for (int z = 0; z < amountSectors / 2; z++)
				{
					stringstream tmpStream;
					tmpStream << "[" << index << "]: " << memory[index];
					string tmp = tmpStream.str();
					if (z % 2 != 0)
						stream << setw(9) << tmp << " ";
					else
						stream << setw(9) << tmp;
					index += 8;
				}
				indexMemory++;
				stream << endl;
			}
		}

		return stream.str();
	}
	list<File*> GetNamesFiles()
	{
		return files;
	}
	char* OpenFile(string fileName)
	{
		if (!getFile(fileName))
			return "";
		int numberSector = checkNumberIndexBlock(fileName);
		if (numberSector > -1 && numberSector < amountSectors)
			return disc->TryOpenFile(numberSector);
		else return "";
	}
	void DeleteFile(string fileName)
	{
		if (!getFile(fileName))
			return;
		int numberSector = -1;
		File* file = getFile(fileName);
		disc->DeleteFile(file->GetNumberSector());
		files.remove(file);
	}
	string CatalogToString()
	{
		stringstream stream;

		stream << catalog->getName() << ": " << endl;
		int amountFiles = catalog->getAmountFiles();
		string* files = catalog->getNamesFilesInside();
		for (int i = 0; i < amountFiles; i++)
		{
			stream << files[i] << endl;
		}
		return stream.str();
	}
	bool FileIsOnlyRead(string fileName)
	{
		File* file = getFile(fileName);
		if (file->GetAccess() == 0)
			return true;
		else return false;
	}
	int GetSizeFreeMemory()
	{
		return disc->AmoutFreeSectors()*sizeSector;
	}
	private:
		void saveDefaultData()
		{
			int amount = 5;
			string names[] = {"plik1.txt", "plik2.txt", "plik3.txt", "plik5.txt", "plik4.txt"};
			SaveDefaultData* save = new SaveDefaultData(names, amount);
			string* data = save->Save();
			for (int i = 0; i < amount; i++)
			{
				AddFile(names[i], data[i]);
			}
			delete save;
		}
		int checkNumberIndexBlock(string fileName)
		{
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
				if ((*i)->GetName() == fileName)
					return (*i)->GetNumberSector();
			return -1;
		}
		File* getFile(string fileName)
		{
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
				if ((*i)->GetName() == fileName)
					return *i;
			return NULL;
		}
};

#endif SYSTEMFILES_H