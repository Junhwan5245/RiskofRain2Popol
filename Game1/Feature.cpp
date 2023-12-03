#include "stdafx.h"

Feature::Feature()
{
	feature = Actor::Create();
}

Feature::~Feature()
{
}

void Feature::Update()
{
	/*if (feature->Find("RootNode")->Intersect(GM->player->Find("RootNode")))
	{
		GM->player->MoveBack(feature);
	}*/
	
	feature->Update();
}

void Feature::Render()
{
	feature->Render();
}

void Feature::SetPosition()
{
	int tempX = RANDOM->Int(-70, 50);
	int tempY = RANDOM->Int(100, 200);
	int tempZ = RANDOM->Int(-70, 50);

	feature->SetWorldPosX(tempX);
	feature->SetWorldPosY(tempY);
	feature->SetWorldPosZ(tempZ);

	
}




