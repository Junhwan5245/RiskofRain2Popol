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
{//15%(��ø�� +15%)Ȯ���� ������ ���� �߻�. �⺻���� 240%

}

void Item_TriTipDagger::Update()
{
	Item::Update();
}

void Item_TriTipDagger::Render()
{
	Item::Render();
}
