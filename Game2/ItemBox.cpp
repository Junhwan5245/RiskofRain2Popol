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
	// �÷��̾�� ��ȣ�ۿ� (���ڸ� ��������)
	for (auto& item : items)
	{
		
	}
}
