#include "stdafx.h"

Player* Player::Create(string name)
{
	///11
	Player* temp = new Player();
	temp->LoadFile("Player.xml");
	temp->type = ObType::Actor;
	temp->playerState = PlayerState::IDLE;
	temp->attackState = PlayerAttackState::IDLE;
	temp->skillState = SkillState::NONE;
	temp->anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
	temp->Find("mdlCommandoDualies")->rotation.y = 180.0f * ToRadian;

	/** ����*/
	temp->moveSpeed = 7.0f;

	temp->maxHp = 110; // ������� + 33
	temp->Hp = 110;
	temp->attack = 12; // ������� + 2.4
	temp->defend = 0;
	/** ����*/

	temp->isRight = false;
	temp->isRoll = false;
	temp->isLButton = false;
	temp->isRButton = false;
	temp->isRSkill = false;
	return temp;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Update()
{
	//cout << GetForward().x << endl;
	//cout << GetForward().y << endl;
	//cout << GetForward().z << endl;

	Vector3 Rot;
	Rot.x = INPUT->movePosition.y * 0.003f;
	Rot.y = INPUT->movePosition.x * 0.005f;
	mouseDir = Rot;
	rotation.y += mouseDir.y;
	Find("PlayerCam")->rotation.x += mouseDir.x;


	lastRot = Find("RootNode")->rotation.y;
	lastRot_root = rotation.y;
	dir = Vector3();

	if (INPUT->KeyPress('W'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += GetForward();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(1,0,0);
	}
	else if (INPUT->KeyPress('S'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += -GetForward();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(-1, 0, 0);
	}
	if (INPUT->KeyPress('A'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += -GetRight();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(0, 0, -1);
	}
	else if (INPUT->KeyPress('D'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += GetRight();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(0, 0, 1);
	}
	dir.Normalize();


	if (isRoll) //������ ������
	{
		fixDir = dir;
		isRoll = false;
	}

	if (INPUT->KeyPress('W') or INPUT->KeyPress('S') or
		INPUT->KeyPress('A') or INPUT->KeyPress('D'))
	{
		Move(dir);
	}

	FSM();


	for (auto it = bullet.begin(); it != bullet.end(); it++)
	{
		(*it)->Update();
	}

	Unit::Update();
}

void Player::Render(shared_ptr<Shader> pShader)
{
	for (auto it = bullet.begin(); it != bullet.end(); it++)
	{
		(*it)->Render();
	}

	Unit::Render();
}

void Player::FSM()
{
	// �÷��̾� �̵� FSM
	if (playerState == PlayerState::IDLE)
	{
		moveSpeed = 7.0f;
		// IDLE-> WALK Ű�� ������ ��
		if (INPUT->KeyPress('W') or INPUT->KeyPress('S') or
			INPUT->KeyPress('A') or INPUT->KeyPress('D'))
		{
			playerState = PlayerState::WALK;
			AinmChange(playerState);
		}
	}
	else if (playerState == PlayerState::WALK)
	{
		moveSpeed = 7.0f;

		if (attackState == PlayerAttackState::ATTACK)
		{
			// Ű�� �������� �ִϸ��̼� ��ȯ
			if (INPUT->KeyDown('W'))
				anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
			if (INPUT->KeyDown('S'))
				anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
			if (INPUT->KeyDown('A'))
				anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
			if (INPUT->KeyDown('D'))
				anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
		}

		// WALK -> IDLE Ű�� �ƹ��͵� ������ �ʾ�����
		if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
			INPUT->KeyPress('A') or INPUT->KeyPress('D')))
		{
			playerState = PlayerState::IDLE;
			AinmChange(playerState);
		}

		// WALK ->RUN // L��Ʈ���� ������ ��
		if (INPUT->KeyDown(VK_LCONTROL))
		{
			playerState = PlayerState::RUN;
			AinmChange(playerState);
		}

		// WALK ->ROLL // L����Ʈ�� ������ ��
		if (INPUT->KeyDown(VK_LSHIFT))
		{
			playerState = PlayerState::ROLL;
			isRoll = true;
			AinmChange(playerState);
		}
	}
	else if (playerState == PlayerState::RUN)
	{
		moveSpeed = 10.0f;

		// RUN -> WALK
		if (not INPUT->KeyPress('W') or INPUT->KeyPress('S') or INPUT->KeyPress(VK_LBUTTON))
		{
			playerState = PlayerState::WALK;
			AinmChange(playerState);
		}

		// RUN -> IDLE
		if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
			INPUT->KeyPress('A') or INPUT->KeyPress('D')))
		{
			playerState = PlayerState::IDLE;
			AinmChange(playerState);
		}
	}
	else if (playerState == PlayerState::ROLL)
	{
		moveSpeed = 12.0f;

		// ������ �ִϸ��̼��� ������ ROLL-> WALK or IDLE�� ���� ����
		if (anim->GetPlayTime() >= 0.99)
		{
			//ROLL -> WALK
			playerState = PlayerState::WALK;
			AinmChange(playerState);


			// ROLL -> IDLE
			if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
				INPUT->KeyPress('A') or INPUT->KeyPress('D')))
			{
				playerState = PlayerState::IDLE;
				AinmChange(playerState);
			}
		}
	}
	// �÷��̾� �̵� FSM


	// �÷��̾� ���� FSM
	if (attackState == PlayerAttackState::IDLE)
	{
		//IDLE -> ATTACK
		if (INPUT->KeyPress(VK_LBUTTON))
			//or INPUT->KeyPress(VK_RBUTTON) 
			//or INPUT->KeyPress('R'))
		{
			attackState = PlayerAttackState::ATTACK;
			//anim->ChangeAnimation(AnimationState::LOOP, 21, 0.1f);
			attackStopTime = 0.0f;

			// �÷��̾��� ���ݻ��°� �������� �ٲ�鼭 �÷��̾ �ȴ� �����϶�; ����Ű�� ������ ���� �ִϸ��̼� �������ֱ�
			if (playerState == PlayerState::WALK)
			{
				if (INPUT->KeyDown('W'))
					anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
				if (INPUT->KeyDown('S'))
					anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
				if (INPUT->KeyDown('A'))
					anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
				if (INPUT->KeyDown('D'))
					anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
			}
		}
	}
	else if (attackState == PlayerAttackState::ATTACK)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			attackStopTime = 0.0f;
			skillState = SkillState::LBUTTON;
			isLButton = true;
		}
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			isLButton = false;
		}
		if (isLButton)
		{
			if (TIMER->GetTick(LButtonFireTime, attackSpeed))
			{
				isRight = !isRight;
				
				PlayerBullet* temp = PlayerBullet::Create();
				Vector3 pos;
				
				if (isRight)
					pos = Find("gun.r.muzzle")->GetWorldPos();
				else pos = Find("gun.l.muzzle")->GetWorldPos();
				
				temp->SetPos(pos);
				
				bullet.push_back(temp);
				
				for (auto it = bullet.begin(); it != bullet.end(); it++)
				{
					if (not (*it)->isFire)
					{
						(*it)->Fire(GetForward(), 1.0f, rotation);
						break;
					}
				}
			}
		}

		//if (INPUT->KeyPress(VK_RBUTTON))
		//{
		//	attackStopTime = 0.0f;
		//	attack = Attack::RBUTTON;
		//	isRButton = true;
		//}
		//if (INPUT->KeyPress('R'))
		//{
		//	attackStopTime = 0.0f;
		//	attack = Attack::R;
		//	isRSkill = true;
		//}



		// ATTACK -> IDLE
		// ���������ʰ� 4�ʰ� �����鼭 ���ݻ��´� IDLE�� �ٲ��, �÷��̾��� �ִϸ��̼ǵ� ����
		if (TIMER->GetTick(attackStopTime, 4.0f))
		{
			attackState = PlayerAttackState::IDLE;
			skillState = SkillState::NONE;


			if (playerState == PlayerState::WALK)
				anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
	}
	// �÷��̾� ���� FSM
}

void Player::AinmChange(PlayerState state)
{
	if (state == PlayerState::IDLE)
	{
		anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
	}
	else if (state == PlayerState::WALK)
	{
		if (attackState == PlayerAttackState::IDLE)
		{
			anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		else if (attackState == PlayerAttackState::ATTACK)
		{
			if (INPUT->KeyPress('W'))
				anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
			if (INPUT->KeyPress('S'))
				anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
			if (INPUT->KeyPress('A'))
				anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
			if (INPUT->KeyPress('D'))
				anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
		}
	}
	else if (state == PlayerState::RUN)
	{
		anim->ChangeAnimation(AnimationState::LOOP, 7, 0.1f);
	}
	else if (state == PlayerState::ROLL)
	{
		if (attackState == PlayerAttackState::IDLE)
		{
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 11, 0.1f);
		}
		else if (attackState == PlayerAttackState::ATTACK)
		{
			if (INPUT->KeyPress('W'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 11, 0.1f);
			if (INPUT->KeyPress('S'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 12, 0.1f);
			if (INPUT->KeyPress('A'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 9, 0.1f);
			if (INPUT->KeyPress('D'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 10, 0.1f);
		}
	}
}

void Player::Move(Vector3 Target)
{
	if (attackState == PlayerAttackState::IDLE)
	{
		Vector3 Dir;

		MoveWorldPos(Find("RootNode")->GetForward() * moveSpeed * DELTA);
		//MoveWorldPos(Target * velocity * DELTA);

		if (playerState == PlayerState::IDLE)
			Find("RootNode")->rotation.y = lastRot;

		else if (playerState != PlayerState::ROLL and playerState != PlayerState::IDLE)
			Find("RootNode")->rotation.y = atan2f(Target.z, Target.x);
	}
	else if (attackState == PlayerAttackState::ATTACK)
	{
		Vector3 Dir;
		if (playerState != PlayerState::ROLL)
		{
			Dir = Target;
		}
		else
		{
			Dir = fixDir;
		}

		MoveWorldPos(Dir * moveSpeed * DELTA);
		//Find("RootNode")->rotation.y = atan2f(GetForward().z, GetForward().x) - HALFPI;
	}
}

void Player::Fire(Vector3 dest, float power)
{
}

void Player::WolrdUpdate()
{
	GameObject::Update();
}

void Player::PlayerRenderHierarchy()
{
	this->RenderHierarchy();
	for (auto it = bullet.begin(); it != bullet.end(); it++)
	{
		(*it)->RenderHierarchy();
	}
}
