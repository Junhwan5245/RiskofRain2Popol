#include "stdafx.h"

Item_Normal::Item_Normal(string i) : id(i)
{
}

void Item_Normal::add(ItemComponent* item)
{
	normalItems.push_back(item);
}

void Item_Normal::list() const
{
	cout << id << endl;
	for(auto it = normalItems.begin(); it != normalItems.end(); it++)
	{
		(*it)->list();
	}
}
