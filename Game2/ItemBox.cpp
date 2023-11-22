#include "stdafx.h"

ItemBox::ItemBox(string i) : id(i)
{
}

void ItemBox::add(ItemComponent* item)
{
	items.push_back(item);
}

void ItemBox::list() const
{
	cout << id << endl;
	for (auto it = items.begin(); it != items.end(); it++)
	{
		(*it)->list();
	}
}
