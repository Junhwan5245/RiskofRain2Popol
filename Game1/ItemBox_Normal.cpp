#include "stdafx.h"
#include "ItemBox_Normal.h"

ItemBox_Normal::ItemBox_Normal()
{
	itemBox->LoadFile("Lemurian.xml");
	ItemBox::Init();
}

ItemBox_Normal::~ItemBox_Normal()
{
}

void ItemBox_Normal::Update()
{
	ItemBox::Update();
}


void ItemBox_Normal::Render()
{
	ItemBox::Render();
}


void ItemBox_Normal::CreateItem()
{
	Item* temp = nullptr;
	int size = NormalItemPool::SizeNoraml;
	//switch (0)
	switch (RANDOM->Int(0, size - 1))
	{
	case NormalItemPool::Syringe:
		temp = new Item_Syringe();
		break;
	case NormalItemPool::APRound:
		temp = new Item_APRound();
		break;
	case NormalItemPool::Glasses:
		temp = new Item_Glasses();
		break;
	case NormalItemPool::TriTipDagger:
		temp = new Item_TriTipDagger();
		break;
		

	defalut: 
		break;

	}

	temp->item->SetWorldPos(this->itemBox->GetWorldPos());
	GM->items.push_back(temp);
}


