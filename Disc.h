#ifndef DISC_H
#define DISC_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class Disc
{
	private:
		char* memory;
		int* sectors;
		int amoutSectors;
	public:
		Disc(int discSize, int sectorSize)
		{
			amoutSectors = discSize / sectorSize; 
			memory = new char[discSize];
			sectors = new int[sectorSize];

			for (int i = 0; i < sectorSize; i++)
			{
				sectors[i] = 0;
			}
			for (int i = 0; i < discSize; i++)
			{
				memory[i] = '#';
			}
		}
		int* getSectors()
		{
			return sectors;
		}
		char* getMemory()
		{
			return memory;
		}
		int TrySaveFile(string text)
		{
			double amoutReserveSectors = text.length();
			amoutReserveSectors /= amoutSectors;
			amoutReserveSectors = ceil(amoutReserveSectors);

			int numberIndexBlock = findFirstFreeSectorOrDefault();
			sectors[numberIndexBlock] = 1;
			int* numbersIndexMemory = findFewFreeSectorOrDefault(amoutReserveSectors);

			int beginIndex = numberIndexBlock * amoutSectors;
			memory[beginIndex] = '0';
			int i, j;
			
			for (i = beginIndex + 1, j =0; j < amoutReserveSectors; i++, j++)
			{
				memory[i] = numbersIndexMemory[j] + '0';
			}

			int indexText = 0;
			for (i = 0; i < amoutReserveSectors; i++)
			{
				int indexMemory = numbersIndexMemory[i] * amoutSectors;
				memory[indexMemory] = '1';
				indexMemory++;
				j = 1;
				while((j < amoutSectors)&&(indexText < text.length()))
				{
					memory[indexMemory] = text[indexText];
					indexMemory++;
					indexText++;
					j++;
				}
			}
			return numberIndexBlock;
		}
		string TryOpenFile(int numberSector)
		{

			return "";
		}
	private:
		int findFirstFreeSectorOrDefault()
		{
			for (int i = 0; i < amoutSectors; i++)
			if (sectors[i] == 0)
				return i;

			return	-1;
		}
		int* findFewFreeSectorOrDefault(int amout)
		{
			int* freeSectors = new int[amout];
			int j = 0;

			for (int i = 0; i < amout; i++)
			{
				int freeSector = findFirstFreeSectorOrDefault();
				if (sectors[freeSector] != 1)
				{
					if (sectors[freeSector] == 0)
					{
						sectors[freeSector] = 1;
						freeSectors[j] = freeSector;
						j++;
					}
					else return NULL;
				}
			}
			return freeSectors;
		}
		char* getSector(int numberSector)
		{
			int startIndex = numberSector * amoutSectors;

		}
};


#endif DISC_H