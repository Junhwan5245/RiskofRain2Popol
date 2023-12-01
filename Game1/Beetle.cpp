#include "stdafx.h"

Beetle* Beetle::Create(string name)
{
	Beetle* beetle = new Beetle();
	beetle->LoadFile("Beetle.xml");
	beetle->type = ObType::Actor;
	beetle->monsterType = MonsterType::BEETLE;
	beetle->IdleAnimations();
	beetle->range = 1;
	
	beetle->moveSpeed = 10.0f; // 증가계수 24
	beetle->maxHp = 80; // 증가계수 24
	beetle->hp = 80;
	beetle->defend = 0;

	beetle->attack = 12.0f;	//증가계수 2.4

	beetle->Find("ROOT")->rootMotion = true;
	
	return beetle;
}        

void Beetle::Update()
{
	Monster::Update();

	root->Find("frontHp")->scale.x = hp * 1.7 / 100;


	if (state == MonsterState::MOVE)
	{

		if (anim->GetPlayTime() >= 1.0f)
		{
			Vector3 minus = root->Find("ROOT")->GetWorldPos() - last;
			minus.y = 0.0f;
			SetWorldPos(root->Find("ROOT")->GetWorldPos());
			Transform::Update();
			last = root->Find("ROOT")->GetWorldPos();
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 1, 0.0f);
		}
	}

	if (state == MonsterState::ATTACK)
	{
		
		if (Find("Head")->Intersect(GM->player->Find("RootNode")))
		{
			if (!isHit)
			{
				GM->player->hp -= 10;
				isHit = true;
			}
		}

	}

	

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
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 3, 0.0f);
}

void Beetle::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 6, 0.0f);
}

void Beetle::MoveAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 1, 0.0f);
}

void Beetle::DeadAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 4, 0.0f);
}

Beetle::Beetle()
{
}

Beetle::~Beetle()
{
}
