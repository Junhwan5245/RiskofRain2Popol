#include "stdafx.h"

Item_Infusion::Item_Infusion()
{
	item->LoadFile("Itme_Infusion.xml");
	item->name = "Infusion";
	itemType = ItemType::RARE;
}

Item_Infusion::~Item_Infusion()
{
}

void Item_Infusion::Operate()
{
}

void Item_Infusion::Update()
{
	Item::Update();
}

void Item_Infusion::Render()
{
	Item::Render();
}
