#include "stdafx.h"

Item_Rare::Item_Rare(string i) : id(i)
{
}

void Item_Rare::add(ItemComponent* item)
{
	rareItems.push_back(item);
}

void Item_Rare::list() const
{
	cout << id << endl;
	for (auto it = rareItems.begin(); it != rareItems.end(); it++)
	{
		(*it)->list();
	}
}
