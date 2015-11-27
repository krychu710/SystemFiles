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
				memory[i] = '\0';
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
		char* TryOpenFile(int numberSector)
		{
			int amoutIndexesOfBlock = 0;
			int* indexes = getIndexesOfBlock(numberSector, amoutIndexesOfBlock);
			char* content = new char[amoutIndexesOfBlock*amoutSectors];
			int x = 0;
			for (int i = 0; i < amoutIndexesOfBlock; i++)
			{
				char* block = getBlock(indexes[i]);
				for (int j = 1; j < amoutSectors && block[i]!='\0'; j++)
					content[x++] = block[j];	
			}
			return content;
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
		char* getBlock(int numberSector)
		{
			int startIndex = numberSector * amoutSectors;
			char* block = new char[amoutSectors];
			for (int i = 0; i < amoutSectors; i++)
			{
				block[i] = '\0';
			}
			memcpy(block, &memory[startIndex], amoutSectors);
			return block;
		}
		int* getIndexesOfBlock(int numberSector, int& amountIndexesOfBlock)
		{
			char* indexBlock = getBlock(numberSector);
			int i = 0;
			int* indexes;
			if (indexBlock[i] == '0')
			{
				int j = 0;
				i = 1;
				while (indexBlock[i] != '\0')
				{
					j++;
					i++;
				}
				amountIndexesOfBlock = j;
				indexes = new int[amountIndexesOfBlock];
				i = 1;
				while (indexBlock[i] != '\0' && i <= j)
				{
					indexes[i-1] = indexBlock[i]-'0';
					i++;
				}
			}
			
			return indexes;
		}
};


#endif DISC_H