#include "stdafx.h"

Golem* Golem::Create(string name)
{
	Golem* golem = new Golem();
	golem->LoadFile("mdlGolem.xml");
	golem->type = ObType::Actor;
	golem->IdleAnimations();
	golem->range = 20;
	golem->moveSpeed = 5.0f;
	golem->Find("ROOT")->rootMotion = true;
	

	golem->lazer = GolemLazer::Create("Lazer");
	golem->lazer->LoadFile("GolemLazer.xml");
	golem->lazer->visible = false;
	GM->bulletPool.push_back(golem->lazer);
	
	

	return golem;
}

void Golem::Update()
{
	Monster::Update();

	/*last = root->Find("base")->GetWorldPos();*/

	/*root->Find("frontHp")->scale.x = Hp * 1.7 / 100;*/

	static float laserTimer = 0.0f;

	if (state == MonsterState::MOVE)
	{
		
		if (anim->GetPlayTime() >= 1.0f)
		{
			Vector3 minus = Find("ROOT")->GetWorldPos() - last;
			minus.y = 0.0f;
			SetWorldPos(Find("ROOT")->GetWorldPos());
			Transform::Update();
			last = Find("ROOT")->GetWorldPos();
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 3, 0.0f);
		}

		lazer->visible = false;
	}

	
	if (state == MonsterState::ATTACK)
	{
		
		laserTimer += DELTA;


		
		if (laserTimer <= 3.0f || laserTimer >= 6.0f)
		{
			
			if (!oneTime)
			{
				lazer->SetWorldPos(root->Find("lazerstart")->GetWorldPos());
				oneTime = true;
			}
			
			lazer->visible = true;
			

			Vector3 dir = GM->player->Find("base")->GetWorldPos() - root->Find("lazerstart")->GetWorldPos();
			dir.Normalize();

			lazer->root->SetWorldPos((root->Find("lazerstart")->GetWorldPos() + GM->player->Find("base")->GetWorldPos()) * 0.5f);
			/*lazer->scale.z = (root->Find("lazerstart")->GetWorldPos().z + GM->player->GetWorldPos().z) * 0.5f;*/

			float lazerLength = (root->Find("lazerstart")->GetWorldPos() - GM->player->Find("base")->GetWorldPos()).Length();
			lazer->scale.z = lazerLength*0.5;

			lazer->rotation.x = -asinf(dir.y);
			lazer->rotation.y = atan2f(dir.x, dir.z);
			
			lazer->isFire = true;
			
		}
		else
		{
			oneTime = false;
			lazer->visible = false;
			tempLazerDir = GM->player->Find("base")->GetWorldPos() - root->Find("lazerstart")->GetWorldPos();
			tempLazerDir.Normalize();//레이저 사라지기 직전 방향저장

			// 레이저를 가림
		}
		
		if (laserTimer >= 3.0f && laserTimer < 3.5f)
		{
			// 총알 발사
			GolemBullet* temp = GolemBullet::Create("GolemBullet");
			temp->SetPos(root->Find("lazerstart")->GetWorldPos());
		
			temp->fireDir = tempLazerDir;
			/*temp->rotation.y = atan2f(temp->fireDir.x, temp->fireDir.z);*/
			temp->rotation.x = -asinf(tempLazerDir.y);
			temp->rotation.y = atan2f(temp->fireDir.x, temp->fireDir.z);
			temp->power = 40;
			temp->isFire = true;
			GM->bulletPool.push_back(temp);
		}

		if (laserTimer >= 9.0f)
		{
			laserTimer = 0.0f;
		}

		
	}
	

		/*lazer->RenderHierarchy();
		lazer->Update();*/
	



}

void Golem::Render(shared_ptr<Shader> pShader)
{
	Monster::Render(pShader);
	/*lazer->Render();*/
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
