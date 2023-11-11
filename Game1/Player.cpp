#include "stdafx.h"

Player* Player::Create(string name)
{
	///11
	Player* temp = new Player();
	temp->LoadFile("Player.xml");
	temp->type = ObType::Actor;
	temp->playerState = PlayerState::IDLE;
	temp->attackState = PlayerAttackState::IDLE;
	temp->anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
	temp->Find("RootNode")->rotation.y = 180.0f * ToRadian;
	temp->velocity = 2.0f;
	temp->isRoll = false;


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
	//ImGui::Text("attackStopTime : %.2f", attackStopTime);
	//ImGui::Text("attackState : %d", (int)attackState);

	lastRot = rotation.y;

	dir = Vector3();


	if (INPUT->KeyPress('W'))
	{
		dir += Vector3(0, 0, 1);
	}
	else if (INPUT->KeyPress('S'))
	{
		dir += Vector3(0, 0, -1);
	}
	if (INPUT->KeyPress('A'))
	{
		dir += Vector3(1, 0, 0);
	}
	else if (INPUT->KeyPress('D'))
	{
		dir += Vector3(-1, 0, 0);
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
	Unit::Update();
}

void Player::Render(shared_ptr<Shader> pShader)
{
	Unit::Render();
}

void Player::FSM()
{
	// �÷��̾� �̵� FSM
	if (playerState == PlayerState::IDLE)
	{
		velocity = 2.0f;
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
		velocity = 2.0f;

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
		velocity = 4.0f;

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
		velocity = 5.0f;

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
		{
			attackState = PlayerAttackState::ATTACK;
			anim->ChangeAnimation(AnimationState::LOOP, 21, 0.1f);
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
		}

		// ATTACK -> IDLE
		// ���������ʰ� 4�ʰ� �����鼭 ���ݻ��´� IDLE�� �ٲ��, �÷��̾��� �ִϸ��̼ǵ� ����
		if (TIMER->GetTick(attackStopTime, 4.0f))
		{
			attackState = PlayerAttackState::IDLE;

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

		MoveWorldPos(GetForward() * velocity * DELTA);

		if (playerState == PlayerState::IDLE)
			rotation.y = lastRot;
		else if (playerState != PlayerState::ROLL and playerState != PlayerState::IDLE)
			rotation.y = atan2f(Target.z, Target.x) - HALFPI;
	}
	else if (attackState == PlayerAttackState::ATTACK)
	{
		Vector3 Dir;
		//Dir.x = -Target.x;
		//Dir.z = Target.z;
		if (playerState != PlayerState::ROLL)
		{
			Dir.x = -Target.x;
			Dir.z = Target.z;
		}
		else
		{
			Dir.x = -fixDir.x;
			Dir.z = fixDir.z;
		}
		//if (playerState != PlayerState::ROLL)
		MoveWorldPos(Dir * velocity * DELTA);
		//if (playerState != PlayerState::ROLL)
		//	MoveWorldPos(Dir  * DELTA);
		//else if (playerState == PlayerState::ROLL)
		//	MoveWorldPos(Dir * 20.0f *  DELTA);
		rotation.y = 0.0f;
	}
}

void Player::Fire(Vector3 dest, float power)
{
}

void Player::WolrdUpdate()
{
}
