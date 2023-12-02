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
{//공격속도 15%(중첩당+15%)증가
	GM->player->attackSpeed += GM->player->attackSpeed * 0.15f;
}

void Item_Syringe::Update()
{
	Item::Update();
}

void Item_Syringe::Render()
{
	Item::Render();
}
