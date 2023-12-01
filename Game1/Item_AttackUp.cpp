#include "stdafx.h"

Item_AttackUp::Item_AttackUp()
{
	item->LoadFile("Item_AttackUp.xml");
	item->name = "AttackUp";
	itemType = ItemType::RARE;
}

Item_AttackUp::~Item_AttackUp()
{
}

void Item_AttackUp::Operate()
{// 공격력 증가
}

void Item_AttackUp::Update()
{
	Item::Update();
}

void Item_AttackUp::Render()
{
	Item::Render();
}
