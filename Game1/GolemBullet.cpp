#include "stdafx.h"
#include <queue>

GolemBullet* GolemBullet::Create(string name)
{
	GolemBullet* golemB = new GolemBullet();
	golemB->LoadFile("GolemLazer.xml");


	golemB->power = 10.0f;
	return golemB;
}

GolemBullet::GolemBullet()
{

}

GolemBullet::~GolemBullet()
{
}

void GolemBullet::Update()
{
	/*trail->Play();*/


	/*trail->RenderDetail();
	trail->Update();*/

	Bullet::Update();

}

void GolemBullet::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render(pShader);
	/*trail->Render();*/
}

void GolemBullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}

Pop* GolemBullet::InitParticle()
{
	bulletParticle = Pop::Create();
	bulletParticle->LoadFile("ParticleGolemLazer.xml");
	bulletParticle->desc.gravity = 9;
	bulletParticle->velocityScalar = 18;
	bulletParticle->particleCount = 6;

	return bulletParticle;
}
