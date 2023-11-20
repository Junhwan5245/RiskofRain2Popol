#include "stdafx.h"

Lemurian* Lemurian::Create(string name)
{
	Lemurian* lemurian = new Lemurian();
	lemurian->LoadFile("Lemurian.xml");
	lemurian->type = ObType::Actor;
	lemurian->IdleAnimations();
	/*lemurian->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);*/
	lemurian->moveSpeed = 6.0f; // 증가계수 24
	lemurian->maxHp = 80; // 증가계수 24
	lemurian->Hp = 80;
	lemurian->defend = 0;

	lemurian->attack = 12.0f;	//증가계수 2.4
	lemurian->range = 10;

	lemurian->Find("base")->rootMotion = true;
	
	return lemurian;
}

void Lemurian::Update()
{
	last = root->Find("base")->GetWorldPos();
	Monster::Update();


	root->Find("frontHp")->scale.x = Hp * 1.7 / 100;



	if (state == MonsterState::MOVE)
	{
		if (anim->GetPlayTime() >= 1.0f)
		{
			Vector3 minus = root->Find("base")->GetWorldPos() - last;
			minus.y = 0.0f;
			MoveWorldPos(minus);
			Transform::Update();
			last = root->Find("base")->GetWorldPos();
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 3, 0.0f);
		}
	}

	if (state == MonsterState::ATTACK)//attack 상태일때 총알 발사하기
	{
		if (TIMER->GetTick(bulletCreateTime, 5.0f))//5초마다 GM->bulletPool에 푸쉬
		{
			/*PlayerDir = GM->player->GetWorldPos();*/
			LemurianBullet* temp = LemurianBullet::Create("LemurianBullet");
			temp->SetPos(root->Find("neck_ik")->GetWorldPos());
			temp->fireDir = GM->player->GetWorldPos()-this->GetWorldPos();
			temp->fireDir.Normalize();
			GM->bulletPool.push_back(temp);
			
		}

	}

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
	Monster::MonFSM();
}

void Lemurian::IdleAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 14, 0.1f);
}

void Lemurian::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 17, 0.1f);
}

void Lemurian::MoveAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
}

void Lemurian::DeadAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 6, 0.1f);
}

Lemurian::Lemurian()
{
}

Lemurian::~Lemurian()
{
}
