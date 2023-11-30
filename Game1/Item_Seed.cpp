#include "stdafx.h"

Item_Seed::Item_Seed()
{
	item->LoadFile("Item_Seed.xml");
	item->name = "Seed";
	itemType = ItemType::RARE;
}

Item_Seed::~Item_Seed()
{
}

void Item_Seed::Operate()
{
}

void Item_Seed::Update()
{
	Item::Update();
}

void Item_Seed::Render()
{
	Item::Render();
}
