#include "stdafx.h"

Beetle* Beetle::Create(string name)
{
	Beetle* beetle = new Beetle();
	beetle->LoadFile("Beetle.xml");
	beetle->type = ObType::Actor;
	beetle->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
	return beetle;
}        

void Beetle::Update()
{
	
	//if (state == MonsterState::IDLE)
	//{
	//	
	//	if (INPUT->KeyPress('X'))
	//	{
	//		anim->ChangeAnimation(AnimationState::ONCE_FIRST, 6, 0.1f);
	//		/*state = MonsterState::ATTACK;*/
	//	}
	//}
	//
	Monster::Update();
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

void Beetle::Find(Player* player)
{
}

Beetle::Beetle()
{
}

Beetle::~Beetle()
{
}
