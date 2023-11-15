#include "stdafx.h"

Lemurian* Lemurian::Create(string name)
{
	Lemurian* lemurian = new Lemurian();
	lemurian->LoadFile("Lemurian.xml");
	lemurian->type = ObType::Actor;
	/*lemurian->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);*/
	lemurian->moveSpeed = 6.0f; // 증가계수 24
	lemurian->maxHp = 80; // 증가계수 24
	lemurian->Hp = 80;
	lemurian->defend = 0;

	lemurian->attack = 12.0f;	//증가계수 2.4
	lemurian->range = 10;
	return lemurian;
}

void Lemurian::Update()
{
	Monster::Update();

	root->Find("frontHp")->scale.x = Hp * 1.7 / 100;
}

void Lemurian::Render(shared_ptr<Shader> pShader)
{
	Monster::Render(pShader);
}

void Lemurian::Move(Vector3 Target)
{
}

void Lemurian::WolrdUpdate()
{
}

void Lemurian::MonFSM()
{
  
}

void Lemurian::IdleAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
}

void Lemurian::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 17, 0.1f);
}

Lemurian::Lemurian()
{
}

Lemurian::~Lemurian()
{
}
