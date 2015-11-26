#ifndef FILE_H
#define FILE_H
#include "Disc.h"

class File
{
	private:
		string name;
		int numberSector;
	public:
		File(string name, int numberSector)
		{
			this->name = name;
			this->numberSector = numberSector;
		}
		string GetName()
		{
			return name;
		}
		int GetNumberSector()
		{
			return numberSector;
		}
};


#endif FILE_H