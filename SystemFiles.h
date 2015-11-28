#ifndef SYSTEMFILES_H
#define SYSTEMFILES_H

#include "File.h"
#include <sstream>
#include <iomanip>
#include "Catalog.h"

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
		}
		File* AddFile(string name, string text)
		{
			int realSize = 0;
			int occupiedSpace = 0;
			int numberIndexBlock = disc->TrySaveFile(text, occupiedSpace, realSize);
			File* file = new File(name, numberIndexBlock, occupiedSpace, realSize);
			files.push_back(file);

			return file;
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
			for (int i = 0; i < amountSectors; i+=4)
			{
				indexMemory = i*amountSectors;
				stream << " Sektor "<< i <<"\t    Sektor "<<i+1 <<"\t       Sektor "<< i+2 <<"          Sektor "<< i+3 <<endl;
				for (int j = 0; j < amountSectors/2; j++)
				{
					int index = indexMemory;
					for (int z = 0; z < amountSectors/2; z++)
					{
						stringstream tmpStream;
						tmpStream << "[" << index << "]: " << memory[index];
						string tmp = tmpStream.str();
						if (z%2!=0)
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
		char* OpenFile(string name)
		{
			int numberSector =-1;
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
			{
				if ((*i)->GetName() == name)
				{
					numberSector = (*i)->GetNumberSector();
					break;
				}
			}
			if (numberSector>-1 && numberSector < amountSectors)
				return disc->TryOpenFile(numberSector);
			else return "";
		}
		void DeleteFile(string name)
		{
			File* file;
			int numberSector = -1;
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
			{
				if ((*i)->GetName() == name)
				{
					file = *i;
					break;
				}
			}
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
};

#endif SYSTEMFILES_H