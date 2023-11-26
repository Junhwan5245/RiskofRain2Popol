#include "stdafx.h"
#include <queue>

BossBullet1* BossBullet1::Create(string name)
{
	BossBullet1* bossBullet1 = new BossBullet1();
	bossBullet1->LoadFile("BossBullet1.xml");
	bossBullet1->root->rotation.y = 180.0f * ToRadian;
	bossBullet1->power = 10.0f;
	
	return bossBullet1;
}

BossBullet1::BossBullet1()
{
}

BossBullet1::~BossBullet1()
{
}

void BossBullet1::Update()
{
	/*Bullet::Update();*/
	if (!isFire) return;
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	if (this->Intersect(GM->player->Find("RootNode"))) //총알과 플레이어 충돌
	{
		//소멸 시키고
		this->isCollsion = true;
		GM->player->Hp -= 7;//플레이어 피깎기

	}
	//for (auto& monster : GM->monsterPool)//총알과 몬스터와의 충돌
	//{
	//	if (this->Intersect(monster->Find("RootNode")))
	//	{
	//		this->isCollsion = true;
	//		monster->Hp -= 7;//플레이어 피깎기
	//	}
	//}
	Actor::Update();
}

void BossBullet1::Render(shared_ptr<Shader> pShader)
{
	
	Bullet::Render(pShader);
	
}

void BossBullet1::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}
