#include "stdafx.h"
#include <queue>

GolemBullet* GolemBullet::Create(string name)
{
	GolemBullet* golemB = new GolemBullet();
	golemB->LoadFile("GolemLazer.xml");
	
	/*golemB->root->rotation.y = 180.0f * ToRadian;*/

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
