#include "stdafx.h"
#include <queue>

GolemLazer* GolemLazer::Create(string name)
{
	GolemLazer* golemB = new GolemLazer();
	golemB->LoadFile("GolemLazer.xml");
	/*golemB->root->rotation.y = 180.0f * ToRadian;*/

	golemB->power = 2.0f;
	return golemB;
}

GolemLazer::GolemLazer()
{

}

GolemLazer::~GolemLazer()
{
}

void GolemLazer::Update()
{
	Actor::Update();
}

void GolemLazer::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render(pShader);
	
}

void GolemLazer::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}
