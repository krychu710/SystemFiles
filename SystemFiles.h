#ifndef SYSTEMFILES_H
#define SYSTEMFILES_H

#include "File.h"
#include <list>
#include <sstream>
#include <iomanip>

class SystemFiles
{
	private:
		const int sizeMemory = 256;
		const int sizeSector = 16;
		int sectorLenght;
		Disc* disc;
		list<File*> files;
	public:
		SystemFiles()
		{
			sectorLenght = sizeMemory / sizeSector;
			disc = new Disc(sizeMemory, sizeSector);
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
		void ShowSectors()
		{
			int* sectors = disc->getSectors();
			for (int i = 0; i < sizeSector; i++)
			{
				cout << "[" << i << "]" << " - " << sectors[i] << endl;
			}
		}

		string ShowMemory()
		{
			int indexMemory = 0;
			stringstream stream;
			char* memory = disc->getMemory();
			for (int i = 0; i < sectorLenght; i+=4)
			{
				indexMemory = i*sectorLenght;
				stream << " Sektor "<< i <<"\t    Sektor "<<i+1 <<"\t       Sektor "<< i+2 <<"          Sektor "<< i+3 <<endl;
				for (int j = 0; j < sectorLenght/2; j++)
				{
					int index = indexMemory;
					for (int z = 0; z < sectorLenght/2; z++)
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
		void GetNamesFiles()
		{
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
				cout << "-" << (*i)->GetName() << endl;
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
			if (numberSector>-1 && numberSector < sectorLenght)
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
};

#endif SYSTEMFILES_H