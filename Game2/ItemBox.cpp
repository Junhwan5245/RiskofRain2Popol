#include "stdafx.h"

ItemBox::ItemBox() 
{

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

void ItemBox::Update()
{
}

void ItemBox::Render()
{
}

void ItemBox::Interection()
{
}
