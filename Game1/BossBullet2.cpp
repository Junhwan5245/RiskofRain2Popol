#include "stdafx.h"
#include <queue>


BossBullet2* BossBullet2::Create(string name)
{
	BossBullet2* bossBullet2 = new BossBullet2();
	bossBullet2->LoadFile("BossBullet2.xml");

	bossBullet2->bulletParticle->poptype = PopType::BOSSBULLET2;
	bossBullet2->root->rotation.y = 180.0f * ToRadian;
	bossBullet2->power = 10.0f;
	bossBullet2->exploreTime = 0.0f;
	bossBullet2->dotTime = 0.0f;
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

	
	if ((GM->player->Find("RootNode")->GetWorldPos() - GetWorldPos()).Length() < 20)
	{
		scale.x += 10 * DELTA;
		scale.y += 10 * DELTA;
		scale.z += 10 * DELTA;
		root->collider->scale.x += 4 * DELTA;
		root->collider->scale.y += 4 * DELTA;
		root->collider->scale.z += 4 * DELTA;
	}

	if (root->Intersect(GM->player->Find("RootNode")))
	{
		if (TIMER->GetTick(dotTime, 0.5f))
		{
			GM->player->hp -= 10;
		}
	}

	if (this->scale.x >70)
	{
		this->isCollsion = true;
	}

	Actor::Update();
}

void BossBullet2::Render(shared_ptr<Shader> pShader)
{
	BLEND->Set(true);
	Bullet::Render(pShader);
	BLEND->Set(false);
}

void BossBullet2::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}

Pop* BossBullet2::InitParticle()
{
	
	bulletParticle = Pop::Create();
	bulletParticle->LoadFile("Particle_Boss1Bullet.xml");
	bulletParticle->particleCount = 0;

	return bulletParticle;
	
}


