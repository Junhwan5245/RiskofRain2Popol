#include "stdafx.h"

ItemBox::ItemBox()
{
}

void ItemBox::Init()
{
	//switch (itemLevel)
	//{
	//case 1:
	//	Item_Normal * normal = new Item_Normal();
	//	add(normal);
	//
	//case 2:
	//
	//default:
	//	break;
	//}
}

void ItemBox::add(ItemComponent* item)
{
	items.push_back(item);
}

void ItemBox::list() const
{
	// 플레이어와 상호작용 (상자를 열었을때)
	for (auto& item : items)
	{
		
	}
}
