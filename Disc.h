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
		int sectorAmout;
		int sectorSize;
		int discSize;
	public:
		Disc(int discSize, int sectorSize)
		{
			this->discSize = discSize;
			this->sectorSize = sectorSize;
			sectorAmout = discSize / sectorSize; 
			sectors = new int[sectorSize];
			memory = getEmptyArray(discSize);

			for (int i = 0; i < sectorSize; i++)
			{
				sectors[i] = 0;
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
		//zapis do pliku na dysku 
		int TrySaveFile(string text, int &size, int &occupiedSpace)
		{
			double amoutReserveSectors = text.length();
			amoutReserveSectors /= sectorAmout;
			amoutReserveSectors = ceil(amoutReserveSectors);

			int numberIndexBlock = findFirstFreeSectorOrDefault();
			sectors[numberIndexBlock] = 1;
			int* numbersIndexMemory = findFewFreeSectorOrDefault(amoutReserveSectors);

			occupiedSpace = text.length() + (amoutReserveSectors * 2) + 1;
			size = (amoutReserveSectors + 1) * sectorSize;

			//zapis bloku indeksowego
			int beginIndex = numberIndexBlock * sectorAmout;
			memory[beginIndex] = '0';
			int i, j;
			
			for (i = beginIndex + 1, j =0; j < amoutReserveSectors; i++, j++)
			{
				memory[i] = numbersIndexMemory[j] + '0';
			}

			//zapis bloku z danymi
			int indexText = 0;
			for (i = 0; i < amoutReserveSectors; i++)
			{
				int indexMemory = numbersIndexMemory[i] * sectorAmout;
				memory[indexMemory] = '1';
				indexMemory++;
				j = 1;
				while((j < sectorAmout)&&(indexText < text.length()))
				{
					memory[indexMemory] = text[indexText];
					indexMemory++;
					indexText++;
					j++;
				}
				//wypelnienie niewykorzystanej przestrzeni sektora znakami pustymi
				//w celu wyeliminowania niechcianych danych(smieci - pozostalosci po porzednich plikach)
				while ((j < sectorAmout) && (indexText >= text.length()))
				{
					memory[indexMemory] = '\0';
					indexMemory++;
					j++;
				}
			}
			return numberIndexBlock;
		}
		char* TryOpenFile(int numberSector)
		{
			int amoutIndexesOfBlock = 0;
			int* indexes = getIndexesOfBlock(numberSector, amoutIndexesOfBlock);
			char* content = getEmptyArray(amoutIndexesOfBlock*sectorAmout);
			int x = 0;
			for (int i = 0; i < amoutIndexesOfBlock; i++)
			{
				char* block = getBlock(indexes[i]);
				for (int j = 1; j < sectorAmout && block[i]!='\0'; j++)
					content[x++] = block[j];	
			}
			return content;
		}
		void DeleteFile(int indexBlockNumber)
		{
			int indexesBlockAmout = 0;
			int* indexes = getIndexesOfBlock(indexBlockNumber, indexesBlockAmout);

			for (int i = 0; i < indexesBlockAmout; i++)
				sectors[indexes[i]]= 0;
			
			sectors[indexBlockNumber] = 0;
		}
	private:
		char* getEmptyArray(int length)
		{
			char* emptyArray = new char[length];
			for (int i = 0; i < length; i++)
			{
				emptyArray[i] = '\0';
			}
			return emptyArray;
		}
		int findFirstFreeSectorOrDefault()
		{
			for (int i = 0; i < sectorAmout; i++)
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
			int startIndex = numberSector * sectorAmout;
			char* block = getEmptyArray(sectorAmout);
			memcpy(block, &memory[startIndex], sectorAmout);
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