#include "stdafx.h"

Teleport::Teleport()
{
	teleport= Actor::Create();

	teleport->LoadFile("Teleport.xml");
}

Teleport::~Teleport()
{
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


