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
	Item* temp=nullptr;
	int size = NormalItemPool::SizeNoraml;
	switch (RANDOM->Int(1, size))
	{
	case 1:
		temp = new Item_Syringe();
		break;
		

	defalut: 
		break;

	}

	temp->item->SetWorldPos(this->itemBox->GetWorldPos());
	GM->items.push_back(temp);
}


