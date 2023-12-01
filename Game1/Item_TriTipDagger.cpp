#include "stdafx.h"

Item_TriTipDagger::Item_TriTipDagger()
{
	item->LoadFile("Item_TritipDagger.xml");
	item->name = "TritipDagger";
	itemType = ItemType::NORMAL;
}

Item_TriTipDagger::~Item_TriTipDagger()
{
}

void Item_TriTipDagger::Operate()
{//15%(중첩당 +15%)확률로 적에게 출혈 발생. 기본피해 240%

}

void Item_TriTipDagger::Update()
{
	Item::Update();
}

void Item_TriTipDagger::Render()
{
	Item::Render();
}
