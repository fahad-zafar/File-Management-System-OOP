#pragma once
#include "File.h"

class Folder : public Item 
{
private:
	vector <Item *> compositeItems;						// stores files or sub-folders
	string folderName;									// stores folder name
	string parentFolder;								// stores the parent of folder
	int folderIndex;									// to track location of folder in .txt file
	int vectorIndex;									// to track location of folder in all_Folders vector
	bool status;										// true - in case of current directory, false otherwise
public:
	Folder ();
	Folder (string, int, int);
	string getFolderName ();
	string getParentFolder ();
	bool getStatus ();
	vector <Item *> getCompositeItems ();
	int getFolderIndex ();
	int getVectorIndex ();
	void setParentFolder (string);
	void setStatus (bool);
	void add (Item*);									// add a new file or folder
	void remove (Item*);								// remove a file or folder
	void clear ();										// makes the folder empty
	void print();
};

