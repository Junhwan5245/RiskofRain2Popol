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
{//피해를 입으면 1(중첩당 + 1)의 체력 치유
}

void Item_Seed::Update()
{
	Item::Update();
}

void Item_Seed::Render()
{
	Item::Render();
}
