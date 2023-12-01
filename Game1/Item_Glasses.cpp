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
{// 공격시 10%(중첩당 +10%)확률로 '치명타'발생. 두배의 피해를 입힘


}

void Item_Glasses::Update()
{
	Item::Update();
}

void Item_Glasses::Render()
{
	Item::Render();
}
