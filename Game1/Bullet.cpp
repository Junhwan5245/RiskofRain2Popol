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

void Bullet::CollisionWithMap()//맵과 총알 충돌
{
	
	Vector3 hit;
	BulletRay.position = GetWorldPos();
	BulletRay.direction =GetForward();
	if (Utility::RayIntersectMap(BulletRay, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
	{
		if ((hit - GetWorldPos()).Length() < 1.0f)
		{
			isCollsion = true;
		}
	}
	

}

void Bullet::Update()
{
	if (!isFire) return;
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	CollisionWithMap();

	//if (this->Intersect(GM->player->Find("RootNode"))) //총알과 플레이어 충돌
	//{
	//	//소멸 시키고
	//	this->isCollsion = true;
	//	GM->player->hp -= 7;//플레이어 피깎기
	//}

	for (auto& monster : GM->monsterPool)//총알과 몬스터와의 충돌
	{
		if (this->Intersect(GM->player->Find("RootNode"))) //총알과 플레이어 충돌
		{
			//소멸 시키고
			this->isCollsion = true;
			GM->player->hp -= monster->attack;//플레이어 피깎기
		}

		if (this->Intersect(monster->Find("RootNode")))
		{
			this->isCollsion = true;
			monster->hp -= GM->player->attack;//플레이어 피깎기
		}
	}


	
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
	this->rotation.x = HALFPI;
	this->rotation.y = rotation.y;
}