#include "stdafx.h"
#include <queue>


BossBullet2* BossBullet2::Create(string name)
{
	BossBullet2* bossBullet2 = new BossBullet2();
	bossBullet2->LoadFile("BossBullet1.xml");
	bossBullet2->root->rotation.y = 180.0f * ToRadian;
	bossBullet2->power = 10.0f;
	bossBullet2->exploreTime = 0.0f;
	return bossBullet2;
}

BossBullet2::BossBullet2()
{
}

BossBullet2::~BossBullet2()
{
}

void BossBullet2::Update()
{
	if (!isFire) return;
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	/*if (TIMER->GetTick(exploreTime, 1.0f))
	{
		this->scale.x += 0.2f;
		this->scale.y += 0.2f;
		this->scale.z += 0.2f;
	}*/
	
	scale.x += 10* DELTA;
	scale.y += 10* DELTA;
	scale.z += 10* DELTA;


	if (this->scale.x >50)
	{
		this->isCollsion = true;
	}

	Actor::Update();
}

void BossBullet2::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render(pShader);
}

void BossBullet2::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}
