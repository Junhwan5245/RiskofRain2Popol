#include "stdafx.h"

PlayerBullet* PlayerBullet::Create(string name)
{
	PlayerBullet* temp = new PlayerBullet();
	temp->LoadFile("PlayerBullet.xml");

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
