#include "stdafx.h"

Item_Normal::Item_Normal(string i) : id(i)
{
}

void Item_Normal::add(Item* item)
{
	normalItems.push_back(item);
}

void Item_Normal::list() const
{

}
