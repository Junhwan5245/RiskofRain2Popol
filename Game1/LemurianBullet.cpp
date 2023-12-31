#include "stdafx.h"
#include <queue>

LemurianBullet* LemurianBullet::Create(string name)
{
	LemurianBullet* lemurianB = new LemurianBullet();
	lemurianB->LoadFile("LemurianBulletmesh.xml");
	//lemurianB->InitParticle();
	//lemurianB->bulletParticle->poptype = PopType::LEMURIANBULLET;
	/*lemurianB->trail = new LemurianBulletTrail();
	lemurianB->trail->Top = lemurianB->Find("start");
	lemurianB->trail->Bottom = lemurianB->Find("end");

	lemurianB->trail->interval = 0.2f;
	lemurianB->trail->maxTrail = 50;6
	lemurianB->trail->material->diffuseMap = RESOURCE->textures.Load("FireTrail.png");
	lemurianB->trail->material->diffuse.w = 1.0f;

	lemurianB->trail->material->diffuse.x = 1.0f;
	lemurianB->trail->material->diffuse.y = 0.0f;
	lemurianB->trail->material->diffuse.z = 0.0f;
	lemurianB->trail->isPlaying = true;*/
	lemurianB->root->rotation.y = 180.0f * ToRadian;
	lemurianB->power = 20.0f;
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
	/*trail->Play();*/
	

	/*trail->RenderDetail();
	trail->Update();*/
	Bullet::Update();

	
}

void LemurianBullet::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render(pShader);
	/*trail->Render();*/
}

void LemurianBullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}

Pop* LemurianBullet::InitParticle()
{
	bulletParticle = Pop::Create();
	bulletParticle->LoadFile("Particle_Fire.xml");
	bulletParticle->desc.gravity = 21;
	bulletParticle->velocityScalar = 22;
	bulletParticle->particleCount = 15;

	return bulletParticle;
}
