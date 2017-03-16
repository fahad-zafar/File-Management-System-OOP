#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Item
{
private:
	string itemName;					
public:
	virtual void print() = 0;				// abstract class
	string getter ();
	void setter (string);
};
