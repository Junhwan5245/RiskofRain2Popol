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
	// �÷��̾�� ��ȣ�ۿ� (���ڸ� ��������)
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
