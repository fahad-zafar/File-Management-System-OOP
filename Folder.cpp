#include "Folder.h"

Folder :: Folder ()
{
	folderName = "";
	parentFolder = "";
	folderIndex = 0;
	vectorIndex = 0;
	status = false;
	setter("");
}

Folder :: Folder (string name, int folderInd, int vectorInd)
{
	folderName = name;
	parentFolder = "";
	folderIndex = folderInd;
	vectorIndex = vectorInd;
	status = false;
	setter(name);
}

string Folder :: getFolderName ()
{
	return folderName;
}

string Folder :: getParentFolder ()
{
	return parentFolder;
}

bool Folder :: getStatus ()
{
	return status;
}

vector <Item *>  Folder ::  getCompositeItems ()
{
	return compositeItems;
}

int Folder :: getFolderIndex ()
{
	return folderIndex;
}

int Folder :: getVectorIndex ()
{
	return vectorIndex;
}

void Folder :: setParentFolder (string name)
{
	parentFolder = name;
}

void Folder :: setStatus (bool s)
{
	status = s;
}

void Folder :: add (Item* obj)
{
	compositeItems.push_back(obj);
}

void Folder :: remove (Item* obj)
{
	for (int i = 0; i < compositeItems.size(); i++)
	{
		if (compositeItems[i]->getter() == obj->getter())
		{
			compositeItems.erase(compositeItems.begin()+i);
		}
	}
}

void Folder :: clear ()
{
	compositeItems.erase(compositeItems.begin(), compositeItems.begin() + compositeItems.size());
}

void Folder :: print() 
{
	cout << "\n\t -> Folder: " << folderName << "\n";
	if (compositeItems.size() == 0)
	{
		cout << "Empty Folder\n";
		return;
	}
	for (int i = 0; i < compositeItems.size(); i++)
	{
		Item* temp = compositeItems.at(i);
		cout << i+1 << ". " << (*temp).getter() << endl;
	}
}
