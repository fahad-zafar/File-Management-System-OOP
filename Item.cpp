#include "Item.h"

string Item :: getter ()
{
	return itemName;
}

void Item :: setter (string name)
{
	itemName = name;
}