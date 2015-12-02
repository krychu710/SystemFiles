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
		int sectorsAmount;
		int sectorSize;
		int discSize;
	public:
		Disc(int discSize, int sectorSize)
		{
			this->discSize = discSize;
			this->sectorSize = sectorSize;
			sectorsAmount = discSize / sectorSize; 
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
			amountReserveSectors /= sectorsAmount;
			amountReserveSectors = ceil(amountReserveSectors);

			if (AmoutFreeSectors()<amountReserveSectors + 1)
				return -1;

			int numberIndexBlock = findFirstFreeSectorOrDefault();
			sectors[numberIndexBlock] = 1;
			int* numbersIndexMemory = findFewFreeSectorOrDefault(amountReserveSectors);

			size = text.length() + (amountReserveSectors * 2) + 1;
			occupiedSpace = (amountReserveSectors + 1) * sectorSize;

			//zapis bloku indeksowego
			int beginIndex = numberIndexBlock * sectorsAmount;
			memory[beginIndex] = '0';
			cout << "Sektor indeksowy: " << numberIndexBlock << endl;
			int i, j;
			
			for (i = beginIndex + 1, j =0; j < amountReserveSectors; i++, j++)
			{
				memory[i] = numbersIndexMemory[j] + '0';
			}

			//uzupelnienie pozostalych blokow indeksowych pustymi znakami
			int endSector = (i + sectorsAmount - amountReserveSectors);
			for (; i < endSector; i++)
			{
				memory[i] = '\0';
			}

			cout << "Sektory z danymi: ";
			//zapis bloku z danymi
			int indexText = 0;
			for (i = 0; i < amountReserveSectors; i++)
			{
				int indexMemory = numbersIndexMemory[i] * sectorsAmount;
				cout << numbersIndexMemory[i] << " ";
				memory[indexMemory] = '1';
				indexMemory++;
				j = 1;
				while((j < sectorsAmount)&&(indexText < text.length()))
				{
					memory[indexMemory] = text[indexText];
					indexMemory++;
					indexText++;
					j++;
				}
				//wypelnienie niewykorzystanej przestrzeni sektora znakami pustymi
				//w celu wyeliminowania niechcianych danych(smieci - pozostalosci po porzednich plikach)
				while ((j < sectorsAmount) && (indexText >= text.length()))
				{
					memory[indexMemory] = '\0';
					indexMemory++;
					j++;
				}
				cout << endl;
			}
			return numberIndexBlock;
		}
		int EditFile(int numberIndexSector, string text, int &occupiedSpace, int &size)
		{
			double requiredSpace = text.length();
			requiredSpace /= sectorsAmount;
			requiredSpace = ceil(requiredSpace);
			double actuallyOccupiedSpace = (occupiedSpace / sectorsAmount) - 1;

			if (requiredSpace > actuallyOccupiedSpace)
			{
				if ((requiredSpace - actuallyOccupiedSpace) > AmoutFreeSectors())
					return -1;
			}
			DeleteFile(numberIndexSector);
			if (TrySaveFile(text, size, occupiedSpace) != -1)
				return 0;
			else return -1;
		}

		char* TryOpenFile(int numberIndexSector)
		{
			int amountIndexesOfBlock = 0;
			int* indexes = getNumbersSecorsWithData(numberIndexSector, amountIndexesOfBlock);
			char* content = getEmptyArray(amountIndexesOfBlock*sectorsAmount);
			int x = 0;
			for (int i = 0; i < amountIndexesOfBlock; i++)
			{
				char* sector = getSector(indexes[i]);
				for (int j = 1; j < sectorsAmount && sector[i]!='\0'; j++)
					content[x++] = sector[j];	
			}
			return content;
		}
		void DeleteFile(int numberIndexSector)
		{
			int indexesBlockAmount = 0;
			int* indexes = getNumbersSecorsWithData(numberIndexSector, indexesBlockAmount);

			for (int i = 0; i < indexesBlockAmount; i++)
				sectors[indexes[i]]= 0;
			
			sectors[numberIndexSector] = 0;
		}
		int AmoutFreeSectors()
		{
			int freeSectors = 0;
			for (int i = 0; i < sectorsAmount; i++)
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
			for (int i = 0; i < sectorsAmount; i++)
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
		char* getSector(int numberIndexSector)
		{
			int startIndex = numberIndexSector * sectorsAmount;
			char* sector = getEmptyArray(sectorsAmount);
			memcpy(sector, &memory[startIndex], sectorsAmount);
			return sector;
		}
		int* getNumbersSecorsWithData(int numberIndexSector, int& amountIndexesOfBlock)
		{
			char* indexSector = getSector(numberIndexSector);
			int i = 0;
			int* numbersSectorsWithData;
			if (indexSector[i] == '0')
			{
				int j = 0;
				i = 1;
				while (indexSector[i] != '\0')
				{
					j++;
					i++;
				}
				amountIndexesOfBlock = j;
				numbersSectorsWithData = new int[amountIndexesOfBlock];
				i = 1;
				while (indexSector[i] != '\0' && i <= j)
				{
					numbersSectorsWithData[i - 1] = indexSector[i] - '0';
					i++;
				}
			}
			return numbersSectorsWithData;
		}
};

#endif DISC_H