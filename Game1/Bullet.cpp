#include "stdafx.h"

Bullet* Bullet::Create(string name)
{
	Bullet* temp = new Bullet();
	temp->type = ObType::Actor;
	temp->isFire = false;
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

void Bullet::Update()
{
	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	Actor::Update();
}

void Bullet::Render(shared_ptr<Shader> pShader)
{
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