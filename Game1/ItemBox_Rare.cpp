#include "stdafx.h"

ItemBox_Rare::ItemBox_Rare()
{
	itemBox->LoadFile("Chest2.xml");
	ItemBox::Init();
}

ItemBox_Rare::~ItemBox_Rare()
{
}

void ItemBox_Rare::Update()
{
	ItemBox::Update();
}

void ItemBox_Rare::Render()
{
	ItemBox::Render();
}

void ItemBox_Rare::CreateItem()
{
	Item* temp=nullptr;

	int size = RareItemPool::SizeRare;

	switch(RANDOM->Int(1, size))
	{
	case 1:
		temp = new Item_Syringe();
		break;
	
	default:
		break;
	}
	
	temp->item->SetWorldPos(this->itemBox->GetWorldPos());
	GM->items.push_back(temp);
}


