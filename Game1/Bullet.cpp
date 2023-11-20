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
		if (Utility::RayIntersectMap((*it)->BulletRay, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
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

	if (this->Intersect(GM->player->Find("RootNode"))) //�Ѿ˰� �÷��̾� �浹
	{
		//�Ҹ� ��Ű��
		this->isCollsion = true;
		GM->player->Hp -= 7;//�÷��̾� �Ǳ��

	}
	//for (auto& monster : GM->monsterPool)//�Ѿ˰� ���Ϳ��� �浹
	//{
	//	if (this->Intersect(monster->Find("RootNode")))
	//	{
	//		this->isCollsion = true;
	//		monster->Hp -= 7;//�÷��̾� �Ǳ��
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