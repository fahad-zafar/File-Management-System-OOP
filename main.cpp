#include "Folder.h"
#include <fstream>

static int each_item_index = 0;
const int MAX_SIZE = 1000;

vector <File*> all_Files;			// stores files
vector <Folder*> all_Folders;		// stores folders

ofstream fout ("Data.txt");			// file output stream
ifstream fin ("Data.txt");			// file input stream

void menu ()
{
	cout << "Press 1. to create a file\n";
	cout << "Press 2. to delete a file\n";
	cout << "Press 3. to create a folder\n";
	cout << "Press 4. to delete a folder\n";
	cout << "Press 5. to read a file\n";
	cout << "Press 6. to write a file\n";
	cout << "Press 7. to change current directory\n";
	cout << "Press 8. to view contents of a folder\n";
	cout << "Press 0. to quit\n";
}

// search for a 'File' in all_Files vector
bool searchInFileVector (string name, int &index)
{
	for (int i = 0; i < all_Files.size(); i++)
	{
		if (all_Files[i]->getFileName() == name)
		{
			index = all_Files[i]->getVectorIndex();
			return true;
		}
	}
	return false;
}

// removes spaces from lower end of string
char* removeSpaces (char* data)
{
	bool check = false;
	for (int i = 0, k = 0; i < strlen (data); i++)
	{
		if (data[i] == ' ')
		{
			for (int j = i; j < MAX_SIZE; j++)
			{
				if (data[j] != ' ')
				{
					check = false;
					break;
				}
				check = true;
			}
			if (check == true)
			{
				data[k] = '\0';
				return data;
			}
		}
		k++;
	}
}

// prints the name of current directory
void printCurrDirectory ()
{
	for (int i = 0; i < all_Folders.size(); i++)
	{
		// if status == true
		if (all_Folders[i]->getStatus())
		{
			cout << "\n\t\t << Current Directory: " << all_Folders[i]->getFolderName() << " >>\n";
		}
	}
}

// get the index of current directory
int currDirectoryIndex ()
{
	for (int i = 0; i < all_Folders.size(); i++)
	{
		if (all_Folders[i]->getStatus())
		{
			return i;
		}
	}
}

void changeDirectory (string name)
{
	int prevFolder = 0;
	for (int i = 0; i < all_Folders.size(); i++)
	{
		// set the previous folder's status to false
		if (all_Folders[i]->getStatus())
		{
			prevFolder = i;
			all_Folders[i]->setStatus (false);
			break;
		}
	}
	for (int i = 0; i < all_Folders.size(); i++)
	{
		// set the new folder's status to true
		if (all_Folders[i]->getFolderName() == name)
		{
			all_Folders[i]->setStatus(true);
			cout << "Directory Changed Successfully!\n";
			return;
		}
	}
		
	cout << "Folder Not Found!\n";
	all_Folders[prevFolder]->setStatus (true);
}

void viewDirectory (string name)
{
	for (int i = 0; i < all_Folders.size(); i++)
	{
		if (all_Folders[i]->getFolderName() == name)
		{
			all_Folders[i]->print ();
			return;
		}
	}
	cout << "Folder Not Found!\n";
}

void createFile (string name)
{
	File* obj = new File (name, fout.tellp(), each_item_index++);			// new File object pointer created
	int index = currDirectoryIndex();										// getting index of current directory
	all_Folders[index]->add (obj);											// add File to current directory
	all_Files.push_back (obj);												// also add File to all_Files vector
	fout << name << endl;													// printing in .txt file
	cout << "File Created Successfully!\n";
}

bool deleteFile (string &name)
{
	int fileIndex = 0, vectorIndex = 0, i = 0;
	bool check = false;
	for (; i < all_Files.size(); i++)
	{
		if (all_Files[i]->getFileName() == name)
		{
			vectorIndex = all_Files[i]->getVectorIndex();
			fileIndex = all_Files[i]->getFileIndex();
			check = true;
			break;
		}
	}
	if (check == false)
	{
		cout << "File Not Found!\n";
		return check;
	}

	File* obj = new File (name, fileIndex, vectorIndex);		// create new File pointer object
	int index = currDirectoryIndex();							// get current directory index
	all_Folders[index]->remove (obj);							// remove from current directory

	// to delete the content of file
	int prevIndex = fout.tellp ();								// store previous fout position
	fout.seekp (vectorIndex * MAX_SIZE);						// goto vectorIndex * MAX_Size position
	for (int i = vectorIndex * MAX_SIZE; i < (vectorIndex * MAX_SIZE + MAX_SIZE); i++)
	{
		fout << " ";											// erasing content
	}
	fout.seekp (prevIndex);										// restore previous fout position

	// to delete the name of file
	prevIndex = fout.tellp ();
	fout.seekp (fileIndex);
	int length = name.length();
	for (int i = fileIndex; i < fileIndex + length; i++)		// fileIndex contains the index of fileName in .txt File
	{
		fout << " ";
	}
	fout.seekp (prevIndex);
	all_Files.erase(all_Files.begin() + i);						// remove from all_Files vector
	cout << "File Deleted Successfully!\n";
	return check;
}

void createFolder (string name)
{
	Folder* obj = new Folder (name, fout.tellp (), each_item_index++);		// new pointer to Folder Object
	int index = currDirectoryIndex();										// index of current Directory
	all_Folders[index]->add (obj);											// add folder to current directory
	all_Folders.push_back (obj);											// also add folder to all_Folders
	all_Folders[all_Folders.size()-1]->setParentFolder (all_Folders[index]->getFolderName());			// saving parent folder's name
	fout << name << endl;
	cout << "Folder Created Successfully!\n";
}

bool deleteFolder (string name)
{
	int folderIndex = 0, vectorIndex = 0, i = 0;
	bool check = false;
	string parent;
	for (; i < all_Folders.size(); i++)
	{
		if (all_Folders[0]->getFolderName() == name)						// can't delete root directory
		{
			cout << "Error.. Can't Delete 'root' Folder\n";
			return check;
		}
		if (all_Folders[i]->getFolderName() == name)
		{
			vectorIndex = all_Folders[i]->getVectorIndex();
			folderIndex = all_Folders[i]->getFolderIndex();
			parent = all_Folders[i]->getParentFolder();
			check = true;
			break;
		}
	}
	if (check == false)
	{
		cout << "Folder Not Found!\n";
		return check;
	}

	int prevIndex = 0;
	vector <Item *> dataOfFolder = all_Folders[i]->getCompositeItems ();			// list of each file + folder, it contains
	for (int k = 0; k < dataOfFolder.size (); k++)
	{
		string itemName = dataOfFolder[k]->getter();
		bool check = searchInFileVector (itemName, prevIndex);						// searching if itemName is file or folder

		if (check == true)						// file
			deleteFile (itemName);
		else
			deleteFolder (itemName);			// recursize function
	}
	all_Folders[i]->clear();

	// remove from parent directory
	for (int j = 0; j < all_Folders.size(); j++)
	{
		if (all_Folders[j]->getFolderName() == parent)
		{
			all_Folders[j]->remove (all_Folders[i]);
		}
	}
	all_Folders.erase (all_Folders.begin() + i);			// removed from all_Folders vector

	// to delete the name of folder
	prevIndex = fout.tellp ();
	fout.seekp (folderIndex);
	int length = name.length();
	for (int i = folderIndex; i < folderIndex + length; i++)
	{
		fout << " ";
	}
	fout.seekp (prevIndex);

	cout << "Folder Deleted Successfully!\n";
	changeDirectory ("root");								// current directory changed to root
	return check;
}

bool readFile (string name)
{
	int index = 0;
	bool check = searchInFileVector (name, index);					// search for file in all_Files vector
	if (check == false)
	{
		cout << "File Not Found!\n";
		return check;
	}
	char* data = new char [MAX_SIZE];
	int prevIndex = fin.tellg ();
	fin.seekg (index * MAX_SIZE);
	char ch;
	fin.get (ch);
	int j = 0;
	for (int i = index * MAX_SIZE; i < (index * MAX_SIZE + MAX_SIZE); i++, j++)
	{
		data[j] = ch;												// storing each character
		fin.get(ch);												// reading each character
	}
	data[strlen(data) - 1] = '\0';

	cout << removeSpaces (data) << endl;							// removes spaces at the end of data
	fin.clear ();													// clearing file input stream
	fin.seekg (prevIndex);
}

bool writeFile (string name)
{
	int index = 0;
	bool check = searchInFileVector (name, index);
	if (check == false)
	{
		cout << "File Not Found!\n";
		return check;
	}
	int prevIndex = fout.tellp ();
	fout.seekp (index * MAX_SIZE);
	cout << "Data to be written: ";
	char* data = new char [MAX_SIZE];
	cin.ignore ();
	cin.getline (data, MAX_SIZE, '\n');					// getting input from user
	fout << data;										// writing data
	
	for (int i = index * MAX_SIZE + strlen (data); i < index * MAX_SIZE + MAX_SIZE; i++)
	{
		fout << " ";									// flushing each the whole block
	}
	fout.seekp (prevIndex);
	cout << "Data Written Successfully!\n";
}

int main() 
{
	// for root directory
	Folder* root = new Folder ("root", 0, each_item_index++);
	root->setStatus(true);								// setting current directory
	all_Folders.push_back (root);						// adding root in all_Folders vector
	fout << "root" << endl;
	
	// infinite loop
	while (1)
	{
		printCurrDirectory();
		char choice;
		cout << endl;
		menu ();
		cin >> choice;
		string name;

		if (choice == '1')
		{
			cout << "\nEnter File Name: ";
			cin >> name;
			createFile (name);
		}
		else if (choice == '2')
		{
			cout << "\nEnter File Name: ";
			cin >> name;
			bool check = deleteFile (name);
			if (!check)
				continue;
		}
		else if (choice == '3')
		{
			cout << "\nEnter Folder Name: ";
			cin >> name;
			createFolder (name);
		}
		else if (choice == '4')
		{
			cout << "\nEnter Folder Name: ";
			cin >> name;
			bool check = deleteFolder (name);
			if (!check)
				continue;
		}
		else if (choice == '5')
		{
			cout << "Enter File Name: ";
			cin >> name;
			bool check = readFile (name);
			if (!check)
				continue;
		}
		else if (choice == '6')
		{
			cout << "Enter File Name: ";
			cin >> name;
			bool check = writeFile (name);
			if (!check)
				continue;
		}
		else if (choice == '7')
		{
			cout << "Enter Folder Name: ";
			cin >> name;
			changeDirectory (name);
		}
		else if (choice == '8')
		{
			cout << "Enter Folder Name: ";
			cin >> name;
			viewDirectory (name);
		}
		else if (choice == '0')
		{
			fout.close();
			fin.close();
			break;
		}
		else
		{
			cout << "\n\tInvalid Input. Try Again\n";
		}
	}
	system("pause");
	return 0;
}