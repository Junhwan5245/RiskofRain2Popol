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
{// 적 처치시 체력이 영구적으로 1(중첩당 +1)증가, 최대 100(중첩당 +100)증가
}

void Item_Infusion::Update()
{
	Item::Update();
}

void Item_Infusion::Render()
{
	Item::Render();
}
