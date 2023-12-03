#include "stdafx.h"

Boss* Boss::Create(string name)
{
	Boss* boss = new Boss();
	boss->LoadFile("Boss.xml");
	boss->type = ObType::Actor;
	boss->IdleAnimations();
	boss->range = 20;

	boss->moveSpeed = 2.0f; // 증가계수 24
	boss->maxHp = 5000; // 증가계수 24
	boss->hp = 5000;
	boss->gold = 60;
	boss->exp = 80;
	boss->defend = 0;

	boss->attack = 12.0f;	//증가계수 2.4

	/*boss->Find("ROOT")->rootMotion = true;*/

	return boss;
}

void Boss::Update()
{
	/*Monster::Update();*/
	//ImGui::Text("BossState : %d", bState);
	
	Stare();
	
	MonFSM();
	
	Actor::Update();
	if (bState == BossState::MOVE)
	{
		if (anim->GetPlayTime() >= 1.0f)
		{
			Vector3 minus = root->Find("DetatchedHull")->GetWorldPos() - last;
			minus.y = 0.0f;
			SetWorldPos(root->Find("DetatchedHull")->GetWorldPos());
			Transform::Update();
			last = root->Find("DetatchedHull")->GetWorldPos();
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 1, 0.0f);
		}
	}
	
	
}

void Boss::Render(shared_ptr<Shader> pShader)
{
	Monster::Render();
}

void Boss::Move(Vector3 Target)
{

}

void Boss::WolrdUpdate()
{
}

void Boss::MonFSM()
{
	Vector3 playerVec = Vector3(GM->player->GetWorldPos().x, 0, GM->player->GetWorldPos().z);
	Vector3 bossVec = Vector3(this->GetWorldPos().x, 0, this->GetWorldPos().z);

	if (hp > 0)
	{
		if (bState == BossState::IDLE)
		{
			/*stateChangeTime = 0.0f;*/
			if (TIMER->GetTick(stateChangeTime, 5.0f))//초가 지나게 되면
			{
				MoveAnimations();//move애니메이션 넣기
				anim->aniScale = 0.1f;
				bState = BossState::MOVE;
				return;
			}
		}

		if (bState == BossState::MOVE)//move일때 길찾기와 attack으로 넘어가는 상태 
		{
			anim->aniScale = 1.0f;

			if (!way.empty())
			{
				Vector3 temp = way.back() - GetWorldPos();
				temp.Normalize();
				MoveWorldPos(temp * moveSpeed * DELTA);

				float distanceThreshold = 0.1f;

				if ((way.back() - GetWorldPos()).Length() < distanceThreshold)
				{
					way.pop_back();
				}
			}

			if ((bossVec - playerVec).Length() < this->range)
			{
				//거리로 비교한뒤에 만약 attack상태에 들어오면 int num이란 값 두고 이게 공격발사하고 1이되야만 move로 이동
				AttackAnimations();
				bState = BossState::ATTACK;
			}
		}

		if (bState == BossState::ATTACK)
		{

			//attack2 애니메이션
			if (TIMER->GetTick(bulletTimer1, 5.0f))
			{
				for (int i = 0; i < 3; i++)
				{
					BossBullet1* temp = BossBullet1::Create("BossBullet1");

					if (i == 0)
					{
						temp->SetPos(root->Find("Tentacle1.008_end")->GetWorldPos());
						temp->fireDir = GM->player->GetWorldPos() - root->Find("Tentacle1.008_end")->GetWorldPos();
					}
					else if (i == 1)
					{
						temp->SetPos(root->Find("Tentacle2.008_end")->GetWorldPos());
						temp->fireDir = GM->player->GetWorldPos() - root->Find("Tentacle2.008_end")->GetWorldPos();
					}
					else if (i == 2)
					{
						temp->SetPos(root->Find("Tentacle3.008_end")->GetWorldPos());
						temp->fireDir = GM->player->GetWorldPos() - root->Find("Tentacle3.008_end")->GetWorldPos();
					}


					temp->fireDir.Normalize();
					temp->power = 10;
					temp->isFire = true;
					GM->bulletPool.push_back(temp);

					Attack2Animations();
					bState = BossState::ATTACK2;
				}

			}


			//if ((GetWorldPos() - GM->player->GetWorldPos()).Length() > this->range)
			//{
			//	//기존에 하던 공격은 마저 하고 move상태로 전환하기 총알 발사시에 bool 값으로 총알 발사 뒤 인지 체크하고
			//	MoveAnimations();
			//	bState = BossState::MOVE;
			//}
		}

		if (bState == BossState::ATTACK2)
		{
			if (TIMER->GetTick(bulletTimer2, 5.0f))//5초마다 GM->bulletPool에 푸쉬
			{

				BossBullet2* temp = BossBullet2::Create("BossBullet2");
				temp->SetPos(Find("bullet2start")->GetWorldPos());
				temp->fireDir = GM->player->Find("RootNode")->GetWorldPos() - Find("bullet2start")->GetWorldPos();
				temp->fireDir.Normalize();
				temp->power = 3;
				temp->isFire = true;
				GM->bulletPool.push_back(temp);

				AttackAnimations();
				bState = BossState::ATTACK;
			}
		}

	}
	else
	{
		bState == BossState::DEAD;
	}

	if (bState == BossState::DEAD)
	{

		if (!isHpZero)
		{
			isHpZero = true;
			DeadAnimations();
		}
		if (TIMER->GetTick(dieTimer, 5.0f))
		{
			isDead = true;
		}


		return;
	}


		
}

void Boss::IdleAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 6, 0.0f);
}

void Boss::AttackAnimations()
{
	anim->ChangeAnimation(AnimationState::LOOP, 3, 0.0f);
}

void Boss::MoveAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 2, 0.0f);
}

void Boss::DeadAnimations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 4, 0.0f);
}

void Boss::Attack2Animations()
{
	anim->ChangeAnimation(AnimationState::ONCE_LAST, 4, 0.0f);
}

void Boss::DecreaseHP(float dam)
{
	hp -= dam;
	float scale = GM->ui->bossHPbar->Find("bossHPBar")->scale.x * (float)hp / (float)maxHp;
	GM->ui->bossHPbar->Find("bossHP")->scale.x = scale;
}

Boss::Boss()
{
}

Boss::~Boss()
{
}
