#include "stdafx.h"

Item_Syringe::Item_Syringe()
{
	item->LoadFile("Item_Syringe.xml");
	item->name = "Syringe";
	itemType = ItemType::NORMAL;
}

Item_Syringe::~Item_Syringe()
{
}

void Item_Syringe::Operate()
{
}

void Item_Syringe::Update()
{
	Item::Update();
}

void Item_Syringe::Render()
{
	Item::Render();
}
