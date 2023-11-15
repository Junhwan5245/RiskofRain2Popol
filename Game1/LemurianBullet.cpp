#include "stdafx.h"

LemurianBullet* LemurianBullet::Create(string name)
{
	LemurianBullet* lemurianB = new LemurianBullet();
	lemurianB->LoadFile("PlayerBullet.xml");

	return lemurianB;
}

LemurianBullet::LemurianBullet()
{
}

LemurianBullet::~LemurianBullet()
{
}

void LemurianBullet::Update()
{
	Bullet::Update();
}

void LemurianBullet::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render(pShader);
}

void LemurianBullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}
