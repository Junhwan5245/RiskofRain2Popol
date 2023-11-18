#include "stdafx.h"

Beetle* Beetle::Create(string name)
{
	Beetle* beetle = new Beetle();
	beetle->LoadFile("Beetle.xml");
	beetle->type = ObType::Actor;
	beetle->IdleAnimations();
	beetle->range = 3;
	return beetle;
}        

void Beetle::Update()
{
	Monster::Update();

	root->Find("frontHp")->scale.x = Hp * 1.7 / 100;
}

void Beetle::Render(shared_ptr<Shader> pShader)
{
	Monster::Render(pShader);
}

void Beetle::Move(Vector3 Target)
{
}

void Beetle::WolrdUpdate()
{
}

void Beetle::MonFSM()
{
	Monster::MonFSM();
}

void Beetle::IdleAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
}

void Beetle::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 6, 0.1f);
}

void Beetle::MoveAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
}

void Beetle::DeadAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
}

Beetle::Beetle()
{
}

Beetle::~Beetle()
{
}
