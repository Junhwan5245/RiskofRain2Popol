#include "stdafx.h"

Bullet* Bullet::Create(string name)
{
	Bullet* temp = new Bullet();

	return temp;
}

Bullet::Bullet()
{
	int rand = RANDOM->Int();
	type = (BulletType)rand;	// �ҷ� Ÿ�� ����ֱ�
	isFire = false;
}

Bullet::~Bullet()
{
}

void Bullet::SetPos(Vector3 pos)
{
	SetWorldPos(pos);
}

void Bullet::Update()
{
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	rotation.z = atan2f(fireDir.z, fireDir.x);

	Actor::Update();
}

void Bullet::Render(shared_ptr<Shader> pShader)
{
	Actor::Render();
}

void Bullet::Fire(Vector3 dir, float power)
{
	isFire = true;
	this->power = power;
	this->fireDir = dir;
}