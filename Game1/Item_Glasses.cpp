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
{// ���ݽ� 10%(��ø�� +10%)Ȯ���� 'ġ��Ÿ'�߻�. �ι��� ���ظ� ����


}

void Item_Glasses::Update()
{
	Item::Update();
}

void Item_Glasses::Render()
{
	Item::Render();
}
