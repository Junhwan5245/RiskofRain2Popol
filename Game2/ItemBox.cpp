#include "stdafx.h"

ItemBox::ItemBox() 
{

}

void ItemBox::add(ItemComponent* item)
{
	items.push_back(item);
}

void ItemBox::list() const
{
	
	for (auto it = items.begin(); it != items.end(); it++)
	{
		(*it)->list();
	}
}

void ItemBox::Update()
{
}

void ItemBox::Render()
{
}

void ItemBox::Interection()
{
}
