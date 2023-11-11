#include "stdafx.h"

Lemurian* Lemurian::Create(string name)
{
	Lemurian* lemurian = new Lemurian();
	lemurian->LoadFile("Lemurian.xml");
	lemurian->type = ObType::Actor;
	lemurian->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
	return lemurian;
}

void Lemurian::Update()
{
	if (state == MonsterState::IDLE)
	{

		if (INPUT->KeyPress('X'))
		{
			anim->ChangeAnimation(AnimationState::ONCE_FIRST, 6, 0.1f);
			/*state = MonsterState::ATTACK;*/
		}
	}
	Monster::Update();
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

void Lemurian::Find(Player* player)
{
}

Lemurian::Lemurian()
{
}

Lemurian::~Lemurian()
{
}