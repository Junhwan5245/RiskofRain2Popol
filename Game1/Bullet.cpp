#include "stdafx.h"

Bullet* Bullet::Create(string name)
{
	Bullet* temp = new Bullet();
	temp->type = ObType::Actor;
	temp->isFire = false;
	temp->isCollsion = false;
	temp->extinctionTime = 0.0f;
	
	/*switch (temp->bulletParticle->poptype)
	{
	case PopType::LEMURIANBULLET :
		temp->bulletParticle->LoadFile("Particle_Fire.xml");
		break;
	case PopType::PLAYERBULLET:
		temp->bulletParticle->LoadFile("Particle_Fire.xml");
		break;
	case PopType::GOLEMLAZER:
		temp->bulletParticle->LoadFile("Particle_Fire.xml");
		break;
	case PopType::BOSSBULLET1:
		temp->bulletParticle->LoadFile("Particle_Fire.xml");
		break;
	case PopType::BOSSBULLET2:
		temp->bulletParticle->LoadFile("Particle_Fire.xml");
		break;
	default:
		break;
	
	}*/
	
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

void Bullet::CollisionWithMap()//�ʰ� �Ѿ� �浹
{
	
	Vector3 hit;
	BulletRay.position = GetWorldPos();
	BulletRay.direction =GetForward();
	if (Utility::RayIntersectMap(BulletRay, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
	{
		if ((hit - GetWorldPos()).Length() < 1.0f)
		{
			bulletParticle->SetWorldPos(hit);
			GM->particlePool.push_back(bulletParticle);
			isCollsion = true;
		}
	}
	

}

void Bullet::Update()
{
	if (!isFire) return;
	Actor::Update();

	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	CollisionWithMap();


	if (TIMER->GetTick(extinctionTime, 10.0f))
	{
		this->isCollsion = true;
	}

	//if (this->Intersect(GM->player->Find("RootNode"))) //�Ѿ˰� �÷��̾� �浹
	//{
	//	//�Ҹ� ��Ű��
	//	this->isCollsion = true;
	//	GM->player->hp -= 7;//�÷��̾� �Ǳ��
	//}

	for (auto& monster : GM->monsterPool)//�Ѿ˰� ���Ϳ��� �浹
	{
		if (this->Intersect(GM->player->Find("RootNode"))) //�Ѿ˰� �÷��̾� �浹
		{
			bulletParticle->SetWorldPos(GM->player->Find("RootNode")->GetWorldPos());
			GM->particlePool.push_back(bulletParticle);

			//�Ҹ� ��Ű��
			this->isCollsion = true;
			GM->player->hp -= monster->attack;//�÷��̾� �Ǳ��
			GM->player->DecreaseHP();
		}

		//if (this->Intersect(monster->Find("RootNode")))
		//{
		//	this->isCollsion = true;
		//	monster->Hp -= 20;//�÷��̾� �Ǳ��
		//}
	}

	for (auto& feature : GM->featurePool)
	{
		if (this->Intersect(feature->feature->Find("RootNode"))) //�Ѿ˰� ���� �浹
		{
			bulletParticle->SetWorldPos(feature->feature->Find("RootNode")->GetWorldPos());
			GM->particlePool.push_back(bulletParticle);
		
			//�Ҹ� ��Ű��
			this->isCollsion = true;

		}
	}
	
	
	
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
	this->rotation.x = HALFPI;
	this->rotation.y = rotation.y;
}