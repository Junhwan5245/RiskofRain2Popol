#include "stdafx.h"

Item_Glasses::Item_Glasses()
{
	item->LoadFile("Item_Glasses.xml");
	item->name = "Glasses";
	itemType = ItemType::NORMAL;
}

Item_Glasses::~Item_Glasses()
{
}

void Item_Glasses::Operate()
{
}

void Item_Glasses::Update()
{
	Item::Update();
}

void Item_Glasses::Render()
{
	Item::Render();
}
