#include "stdafx.h"

Item_Syringe::Item_Syringe()
{
	item->LoadFile("Player2.xml");
	itemType = ItemType::RARE;
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
