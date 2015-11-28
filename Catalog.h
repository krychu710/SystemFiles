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
		int getAmoutFiles() { return checkAmoutFiles(); }
		string getName() { return name; }
		string* getNamesFilesInside()
		{
			int amout = checkAmoutFiles();
			string* names = new string[amout];
			int j=0;
			for (list<File*>::iterator i = files->begin(); i != files->end(); i++)
			{
				names[j] = (*i)->GetName();
				j++;
			}
			return names;
		}
	private:
		int checkAmoutFiles()
		{
			int j = 0;
			for (list<File*>::iterator i = files->begin(); i != files->end(); i++)
				j++;
			return j;
		}
};

#endif CATALOG_H