#include "stdafx.h"

Bullet* Bullet::Create(string name)
{
	Bullet* temp = new Bullet();
	temp->type = ObType::Actor;
	temp->isFire = false;
	temp->isCollsion = false;
	return temp;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::SetPos(Vector3 pos)
{
	SetWorldPos(pos);
}

void Bullet::CollisionWithMap()
{
	for (auto it = GM->bulletPool.begin(); it != GM->bulletPool.end(); it++)
	{
		Vector3 hit;
		(*it)->BulletRay.position = (*it)->GetWorldPos();
		(*it)->BulletRay.direction =(*it)->GetForward();
		if (Utility::RayIntersectMap((*it)->BulletRay, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
		{
			if ((hit - (*it)->GetWorldPos()).Length() < 1.0f)
			{
				(*it)->isCollsion = true;
			}
		}
	}

}

void Bullet::Update()
{
	if (!isFire) return;
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	CollisionWithMap();

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

void Bullet::Render(shared_ptr<Shader> pShader)
{
	if (!isFire) return;

	
	Actor::Render();
}

void Bullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	isFire = true;
	this->power = power;
	this->fireDir = dir;
	Vector3 rot = dir - GetWorldPos();
	this->rotation.x = rotation.y - HALFPI;
}