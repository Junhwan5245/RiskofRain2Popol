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
	Vector3 hit;
	Ray Top;
	Top.position = teleport->GetWorldPos() + Vector3(0, 1000, 0);
	Top.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(Top, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
	{
		teleport->SetWorldPosY(hit.y);
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
	//		//������ ä��� �� ����
	//	}
	//}

	teleport->Update();
	
}

void Teleport::Render()
{
	teleport->Render();
}


