#include "stdafx.h"

Golem* Golem::Create(string name)
{
	Golem* golem = new Golem();
	golem->LoadFile("Lemurian.xml");
	golem->type = ObType::Actor;
	golem->IdleAnimations();
	golem->range = 10;

	/*golem->Find("base")->rootMotion = true;*/
	return golem;
}

void Golem::Update()
{
	Monster::Update();

	//last = root->Find("base")->GetWorldPos();

	/*root->Find("frontHp")->scale.x = Hp * 1.7 / 100;*/



	//if (state == MonsterState::MOVE)
	//{
	//	if (anim->GetPlayTime() >= 1.0f)
	//	{
	//		Vector3 minus = root->Find("base")->GetWorldPos() - last;
	//		minus.y = 0.0f;
	//		MoveWorldPos(minus);
	//		Transform::Update();
	//		last = root->Find("base")->GetWorldPos();
	//		anim->ChangeAnimation(AnimationState::ONCE_LAST, 3, 0.0f);
	//	}
	//}


}

void Golem::Render(shared_ptr<Shader> pShader)
{
	Monster::Render(pShader);
}

void Golem::Move(Vector3 Target)
{
}

void Golem::WolrdUpdate()
{
}

void Golem::MonFSM()
{
	Monster::MonFSM();
}

void Golem::IdleAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 14, 0.1f);
}

void Golem::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 17, 0.1f);
}

void Golem::MoveAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
}

void Golem::DeadAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 6, 0.1f);
}

Golem::Golem()
{
}

Golem::~Golem()
{
}
