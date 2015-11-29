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
		int sectorAmount;
		int sectorSize;
		int discSize;
	public:
		Disc(int discSize, int sectorSize)
		{
			this->discSize = discSize;
			this->sectorSize = sectorSize;
			sectorAmount = discSize / sectorSize; 
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
			double amountReserveSectors = text.length();
			amountReserveSectors /= sectorAmount;
			amountReserveSectors = ceil(amountReserveSectors);

			if (AmoutFreeSectors()<amountReserveSectors + 1)
				return -1;

			int numberIndexBlock = findFirstFreeSectorOrDefault();
			sectors[numberIndexBlock] = 1;
			int* numbersIndexMemory = findFewFreeSectorOrDefault(amountReserveSectors);

			occupiedSpace = text.length() + (amountReserveSectors * 2) + 1;
			size = (amountReserveSectors + 1) * sectorSize;

			//zapis bloku indeksowego
			int beginIndex = numberIndexBlock * sectorAmount;
			memory[beginIndex] = '0';
			int i, j;
			
			for (i = beginIndex + 1, j =0; j < amountReserveSectors; i++, j++)
			{
				memory[i] = numbersIndexMemory[j] + '0';
			}
			int endSector = (i + sectorAmount - amountReserveSectors);
			for (; i < endSector; i++)
			{
				memory[i] = '\0';
			}

			//zapis bloku z danymi
			int indexText = 0;
			for (i = 0; i < amountReserveSectors; i++)
			{
				int indexMemory = numbersIndexMemory[i] * sectorAmount;
				memory[indexMemory] = '1';
				indexMemory++;
				j = 1;
				while((j < sectorAmount)&&(indexText < text.length()))
				{
					memory[indexMemory] = text[indexText];
					indexMemory++;
					indexText++;
					j++;
				}
				//wypelnienie niewykorzystanej przestrzeni sektora znakami pustymi
				//w celu wyeliminowania niechcianych danych(smieci - pozostalosci po porzednich plikach)
				while ((j < sectorAmount) && (indexText >= text.length()))
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
			int amountIndexesOfBlock = 0;
			int* indexes = getIndexesOfBlock(numberSector, amountIndexesOfBlock);
			char* content = getEmptyArray(amountIndexesOfBlock*sectorAmount);
			int x = 0;
			for (int i = 0; i < amountIndexesOfBlock; i++)
			{
				char* block = getBlock(indexes[i]);
				for (int j = 1; j < sectorAmount && block[i]!='\0'; j++)
					content[x++] = block[j];	
			}
			return content;
		}
		void DeleteFile(int indexBlockNumber)
		{
			int indexesBlockAmount = 0;
			int* indexes = getIndexesOfBlock(indexBlockNumber, indexesBlockAmount);

			for (int i = 0; i < indexesBlockAmount; i++)
				sectors[indexes[i]]= 0;
			
			sectors[indexBlockNumber] = 0;
		}
		int AmoutFreeSectors()
		{
			int freeSectors = 0;
			for (int i = 0; i < sectorAmount; i++)
			{
				if (sectors[i] == 0)
					freeSectors++;
			}
			return freeSectors;
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
			for (int i = 0; i < sectorAmount; i++)
			if (sectors[i] == 0)
				return i;

			return	-1;
		}
		int* findFewFreeSectorOrDefault(int amount)
		{
			int* freeSectors = new int[amount];
			int j = 0;

			for (int i = 0; i < amount; i++)
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
			int startIndex = numberSector * sectorAmount;
			char* block = getEmptyArray(sectorAmount);
			memcpy(block, &memory[startIndex], sectorAmount);
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