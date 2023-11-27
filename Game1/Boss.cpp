#include "stdafx.h"

Boss* Boss::Create(string name)
{
	Boss* boss = new Boss();
	boss->LoadFile("Boss.xml");
	boss->type = ObType::Actor;
	boss->IdleAnimations();
	boss->range = 20;

	boss->moveSpeed = 5.0f; // 증가계수 24
	boss->maxHp = 800; // 증가계수 24
	boss->hp = 800;
	boss->defend = 0;

	boss->attack = 12.0f;	//증가계수 2.4

	boss->Find("ROOT")->rootMotion = true;

	return boss;
}

void Boss::Update()
{
	Monster::Update();
}

void Boss::Render(shared_ptr<Shader> pShader)
{
}

void Boss::Move(Vector3 Target)
{
}

void Boss::WolrdUpdate()
{
}

void Boss::MonFSM()
{
}

void Boss::IdleAnimations()
{
}

void Boss::AttackAnimations()
{
}

void Boss::MoveAnimations()
{
}

void Boss::DeadAnimations()
{
}

Boss::Boss()
{
}

Boss::~Boss()
{
}
