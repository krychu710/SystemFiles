#ifndef SYSTEMFILES_H
#define SYSTEMFILES_H

#include "File.h"
#include <list>

class SystemFiles
{
	private:
		const int sizeMemory = 256;
		const int sizeSector = 16;
		Disc* disc;
		list<File*> files;
	public:
		SystemFiles()
		{
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
		void ShowMemory()
		{
			char* memory = disc->getMemory();
			for (int i = 0; i < sizeMemory; i++)
			{
				cout << "[" << i << "]" << " - " << memory[i] << endl;
			}
		}
		void GetNamesFiles()
		{
			for (list<File*>::iterator i = files.begin(); i != files.end(); i++)
				cout << "-" << (*i)->GetName() << endl;
		}
		void OpenFile(string name)
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
			disc->TryOpenFile(numberSector);
		}

};

#endif SYSTEMFILES_H