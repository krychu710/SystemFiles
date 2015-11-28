#ifndef FILE_H
#define FILE_H
#include "Disc.h"
#include <ctime>

class File
{
	private:
		string name;
		int numberSector;
		int occupiedSpace;
		int realSize;
		time_t dateCreated;
	public:
		File(string name, int numberSector, int occupiedSpace, int realSize)
		{
			this->name = name;
			this->numberSector = numberSector;
			this->occupiedSpace = occupiedSpace;
			this->realSize = realSize;
			this->dateCreated = time(0);
		}
		string GetName() { return name; }
		int GetNumberSector() { return numberSector; }
		int GetOccupiedSpace() { return occupiedSpace; }
		int GetRealSize() { return realSize; }
		char* DateCreatedToChar() { return ctime(&dateCreated); }
};


#endif FILE_H