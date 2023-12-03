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

	//switch (num)
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
	int tempX = RANDOM->Int(-70, 50);
	int tempY = RANDOM->Int(100, 200);
	int tempZ = RANDOM->Int(-70, 50);

	itemBox->SetWorldPosX(tempX);
	itemBox->SetWorldPosY(tempY);
	itemBox->SetWorldPosZ(tempZ);

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
		if (itemBox->anim->GetPlayTime() >= 0.99)
		{
			CreateItem();
			isFirst = false;
		}
	}
}

void ItemBox::CreateItem()
{	
}


