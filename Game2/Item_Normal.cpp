#include "stdafx.h"

Item_Normal::Item_Normal()
{
}

void Item_Normal::Init()
{


}

void Item_Normal::add(ItemComponent* item)
{
	Item1* item1 = new Item1();
	Item3* item3 = new Item3();

	normalItems["item1"] = item1;
	normalItems["item3"] = item3;
}

void Item_Normal::list() const
{
	//cout << id << endl;
	//for(auto it = normalItems.begin(); it != normalItems.end(); it++)
	//{
	//	(*it)->list();
	//}
}
