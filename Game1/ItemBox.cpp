#include "stdafx.h"

ItemBox::ItemBox()
{
	itemBox = Actor::Create();
}

ItemBox::~ItemBox()
{
}

ItemBox* ItemBox::Create()
{
	ItemBox();
	int num = RANDOM->Int(0,1);

	switch (num)
	{
	case 0:
		return new ItemBox_Normal();
		break;
	
	case 1:
		return new ItemBox_Rare();
		break;
	
	default:
		break;
	}
}

void ItemBox::Init()
{
	Vector3 hit;
	Ray boxTop;
	boxTop.position = itemBox->GetWorldPos() + Vector3(0, 1000, 0);
	boxTop.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(boxTop, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
	{
		itemBox->SetWorldPosY(hit.y);
	}
}

void ItemBox::Update()
{
	if (not isOpen)
		Interaction();
	else
		itemBox->visible = false;

	itemBox->Update();
}

void ItemBox::Render()
{
	itemBox->Render();
}

void ItemBox::Operate()
{
	
}

void ItemBox::Interaction()
{
	if (itemBox->Find("RootNode")->Intersect(GM->player->Find("RootNode")))
	{
		if (INPUT->KeyDown('E'))
		{
			isOpen = true;
			CreateItem();
		}
	}
}

void ItemBox::CreateItem()
{	
}


