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

			int numberIndexBlock = disc->TrySaveFile(text);
			File* file = new File(name, numberIndexBlock);
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

		string ShowMemoryv2()
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
		string ShowMemory()
		{
			stringstream stream;
			int indexMemoryOne = 0;
			int indexMemoryTwo = 0;
			char* memory = disc->getMemory();
			for (int i = 0; i < sectorLenght; i++)
			{
				stream << "Sektor " << i;
				int j = 0;
				int z = 0;
				stream << endl;
				for (int x = 2; x > 0; x--)
				{
					stream << endl;
					for (; j < sizeSector / x; j++)
					{
						stringstream tmp;
						tmp << "[" << indexMemoryOne++ << "]";
						stream << setw(6) << tmp.str();
					}
					stream << endl;
					for (; z < sizeSector / x; z++)
					{
						stringstream tmp;
						tmp << "\"" << memory[indexMemoryTwo++] << "\"";
						stream << setw(6) << tmp.str();
					}
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