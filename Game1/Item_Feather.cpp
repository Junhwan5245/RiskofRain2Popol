#include "stdafx.h"

Item_Feather::Item_Feather()
{
	item->LoadFile("Item_Feather.xml");
	item->name = "Feather";
	itemType = ItemType::RARE;
}

Item_Feather::~Item_Feather()
{
}

void Item_Feather::Operate()
{//최대 점프 횟수 1증가

}

void Item_Feather::Update()
{
	Item::Update();
}

void Item_Feather::Render()
{
	Item::Render();
}
