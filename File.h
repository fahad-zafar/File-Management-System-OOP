#pragma once
#include "Item.h"

class File: public Item
{
private:
	string fileName;						// stores file name
	int fileIndex;							// to track location of file in .txt
	int vectorIndex;						// to track location of file in all_Files vector
public:
	File ();
	File (string, int, int);
	string getFileName ();
	int getFileIndex ();
	int getVectorIndex ();
	void print();
};
