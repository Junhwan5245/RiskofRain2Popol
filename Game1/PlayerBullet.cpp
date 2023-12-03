#include "stdafx.h"

PlayerBullet* PlayerBullet::Create(string name)
{
	PlayerBullet* temp = new PlayerBullet();
	temp->LoadFile("PlayerBullet.xml");
	//temp->bulletType = BulletType::PLAYER;

	return temp;
}

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{
	Attack();

	Bullet::Update();
}

void PlayerBullet::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render();
}

void PlayerBullet::SetPos(Vector3 pos)
{
	Bullet::SetPos(pos);
}

void PlayerBullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}

void PlayerBullet::Attack()
{
	//총알과 몬스터와의 충돌
	for (auto& monster : GM->monsterPool)
	{
		if (this->Intersect(monster->Find("RootNode")))
		{
			this->isCollsion = true;

			int damage = GM->player->attack;

			// TriTipDagger
			//auto iter = GM->player->GetItemInven()->GetItemList().find("TritipDagger");
			//if (iter != GM->player->GetItemInven()->GetItemList().end())
			//{//있다면 출혈데미지 추가
			//	damage += GM->player->attack * iter->second;
			//}

			//iter = GM->player->GetItemInven()->GetItemList().find("APRound");
			//if (iter != GM->player->GetItemInven()->GetItemList().end())
			//{//있다면 보스에게 20%(중첩 +20%) 추가 피해
			//	if (monster->monsterType == MonsterType::BOSS)
			//	{
			//		damage += GM->player->attack * (0.2f * iter->second);
			//	}
			//}

			
			
			monster->hp -= damage;//플레이어 피깎기
		}
	}
}

void PlayerBullet::PlayerToBossAttack(Boss* boss)
{
	if (this->Intersect(boss))
	{
		this->isCollsion = true;

		int damage = GM->player->attack;

		boss->hp -= damage;//플레이어 피깎기
	}
}

Pop* PlayerBullet::InitParticle()
{
	bulletParticle = Pop::Create();
	bulletParticle->LoadFile("Particle_PlayerBullet.xml");
	bulletParticle->desc.gravity = 21;
	bulletParticle->velocityScalar = 27;
	bulletParticle->particleCount = 5;

	return bulletParticle;
}
