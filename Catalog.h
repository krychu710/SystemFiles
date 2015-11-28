#ifndef CATALOG_H
#define CATALOG_H
#include "File.h"
#include <list>
class Catalog
{
	private:
		list<File*>* files;
		string name;
	public:
		Catalog(string name, list<File*>* files)
		{
			this->name = name;
			this->files = files;
		}
		int getAmountFiles() { return checkAmountFiles(); }
		string getName() { return name; }
		string* getNamesFilesInside()
		{
			int amount = checkAmountFiles();
			string* names = new string[amount];
			int j=0;
			for (list<File*>::iterator i = files->begin(); i != files->end(); i++)
			{
				names[j] = (*i)->GetName();
				j++;
			}
			return names;
		}
	private:
		int checkAmountFiles()
		{
			int j = 0;
			for (list<File*>::iterator i = files->begin(); i != files->end(); i++)
				j++;
			return j;
		}
};

#endif CATALOG_H