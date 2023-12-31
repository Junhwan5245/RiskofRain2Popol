#include "stdafx.h"

Teleport::Teleport()
{
	teleport= Actor::Create();

	teleport->LoadFile("Teleport.xml");
}

Teleport::~Teleport()
{
}

void Teleport::Init()
{
	int tempX = RANDOM->Int(-70, 50);
	int tempY = RANDOM->Int(100, 200);
	int tempZ = RANDOM->Int(-70, 50);

	teleport->SetWorldPosX(tempX);
	teleport->SetWorldPosY(tempY);
	teleport->SetWorldPosZ(tempZ);

	Vector3 hit;
	Ray Top;
	Top.position = teleport->GetWorldPos() + Vector3(0, 1000, 0);
	Top.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(Top, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
	{
		teleport->SetWorldPosY(hit.y+10);
	}
}

void Teleport::Update()
{
	

	//if (teleport->Find("RootNode")->Intersect(GM->player->Find("RootNode")))
	//{
	//	if (INPUT->KeyDown('E'))
	//	{
	//		Boss* boss = Boss::Create("Boss");
	//		GM->monsterPool.push_back(boss);
	//		//게이지 채우는 것 시작
	//	}
	//}

	teleport->Update();
	
}

void Teleport::Render()
{
	teleport->Render();
}


