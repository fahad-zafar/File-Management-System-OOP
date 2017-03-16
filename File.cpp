#include "File.h"

File :: File ()
{
	fileName = "";
	fileIndex = 0;
	vectorIndex = 0;
	setter("");
}

File :: File (string name, int fileInd, int vectorInd)
{
	fileName = name;
	fileIndex = fileInd;
	vectorIndex = vectorInd;
	setter(name);
}

string File :: getFileName ()
{
	return fileName;
}

int File :: getFileIndex ()
{
	return fileIndex;
}

int File :: getVectorIndex ()
{
	return vectorIndex;
}

void File :: print ()
{
	cout << fileName << endl;
}