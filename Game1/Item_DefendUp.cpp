#include "stdafx.h"

Item_DefendUp::Item_DefendUp()
{
	item->LoadFile("Item_DefendUp.xml");
	item->name = "DefendUp";
	itemType = ItemType::RARE;
}

Item_DefendUp::~Item_DefendUp()
{
}

void Item_DefendUp::Operate()
{// 방어력 증가
}

void Item_DefendUp::Update()
{
	Item::Update();
}

void Item_DefendUp::Render()
{
	Item::Render();
}
