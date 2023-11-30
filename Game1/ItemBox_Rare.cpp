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

	switch(RANDOM->Int(0, size -1))
	{
	case RareItemPool::Feather:
		temp = new Item_Feather();
		break;
	case RareItemPool::Infusion:
		temp = new Item_Infusion();
		break;
	case RareItemPool::Seed:
		temp = new Item_Seed();
		break;
	case RareItemPool::AttackUp:
		temp = new Item_AttackUp();
		break;
	case RareItemPool::DefendUp:
		temp = new Item_DefendUp();
		break;
	
	default:
		break;
	}
	
	temp->item->SetWorldPos(this->itemBox->GetWorldPos());
	GM->items.push_back(temp);
}


