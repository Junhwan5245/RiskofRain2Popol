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
	if (Utility::RayIntersectMap(boxTop, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
	{
		itemBox->SetWorldPosY(hit.y);
	}
	isOpen = false;
	isFirst = false;
}

void ItemBox::Update()
{
	Interaction();

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
		if (!isOpen)
		{
			if (INPUT->KeyDown('E'))
			{
				itemBox->anim->ChangeAnimation(AnimationState::ONCE_LAST, 0, 0.0f);
				isOpen = true;
				isFirst = true;
			}
		}
	}

	if (isFirst)
	{
		if (TIMER->GetTick(openTime, 2.0f))
		{
			CreateItem();
			isFirst = false;
		}
	}
}

void ItemBox::CreateItem()
{	
}

