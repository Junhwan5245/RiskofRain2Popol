#include "stdafx.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

Monster* Monster::Create(string name,MonsterType monType)
{
    Monster* temp = nullptr;
    
    switch (monType)
    {
    case MonsterType::BEETLE:
        temp = Beetle::Create(name);
        break;

    case MonsterType::LEMURIAN:
        temp = Lemurian::Create(name);
        break;

    case MonsterType::GOLEM:
        temp = Golem::Create(name);
        break;
      
    default:
        return temp;
        break;
    }

    temp->maxHp = 100;  // ���͸����� ü������ ����
    temp->Hp = 100;     // ���͸����� ü������ ����

    temp->SetRandomPosition();
    temp->IdleAnimations();
    temp->Hp = 100;
    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;
    temp->dieTimer = 0.0f;
   

    return temp;
}
	


Monster* Monster::Create(Monster* src, MonsterType monType)
{
    Monster* temp = nullptr;

    switch (monType)
    {
    case MonsterType::BEETLE:
        temp = Beetle::Create();
        break;

    case MonsterType::LEMURIAN:
        temp = Lemurian::Create();
        break;

    case MonsterType::GOLEM:
        temp = Golem::Create();
        break;

    default:
        return temp;
        break;
    }

    temp->SetRandomPosition();
    temp->IdleAnimations();
    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;
    temp->dieTimer = 0.0f;
   
    return temp;
}

void Monster::Update()
{
    ImGui::Text("animIdx : %d", anim->nextAnimator.animIdx);

    if (Hp <= 0)
    {
        DeadAnimations();
        state == MonsterState::DEAD;
    }

    Stare();

    MonFSM();
    Stare();
    Unit::Update();
}
 
void Monster::Render(shared_ptr<Shader> pShader)
{
    Unit::Render(pShader);
}

void Monster::WolrdUpdate()
{
    GameObject::Update();
}

void Monster::Stare()
{
    Vector3 tempDir = GM->player->GetWorldPos() - this->GetWorldPos();
    tempDir.Normalize();
    float stareDir = atan2f(tempDir.x, tempDir.z);
    this->rotation.y = stareDir + PI;
}

void Monster::MonFSM()
{
    Vector3 playerVec = Vector3(GM->player->GetWorldPos().x,0, GM->player->GetWorldPos().z);
    Vector3 monVec = Vector3(this->GetWorldPos().x,0, this->GetWorldPos().z);
    //���� FSM
    if (state == MonsterState::IDLE)
    {
        /*stateChangeTime += DELTA;*/


        //if (stateChangeTime > stateChangeInterval)
        //{
        //    MoveAnimations();//move�ִϸ��̼� �ֱ�
        //    state = MonsterState::MOVE;
        //}
        if (TIMER->GetTick(stateChangeTime, 5.0f))
        {
            MoveAnimations();//move�ִϸ��̼� �ֱ�
            state = MonsterState::MOVE;
            return;
        }
    }

    if (state == MonsterState::MOVE)
    {
        if (!way.empty())
        {
            Vector3 temp=way.back() - GetWorldPos();
            temp.Normalize();
            MoveWorldPos(temp*moveSpeed*DELTA);

            float distanceThreshold = 0.1f;
           
            if ((way.back() - GetWorldPos()).Length() < distanceThreshold)
            {
                way.pop_back();
            }
        }



        if ((monVec - playerVec).Length() < this->range)
        {
            AttackAnimations();
            state = MonsterState::ATTACK;
        }
    }
    
    //���� FSM
    //if (monAttState == MonsterAttackState::IDLE)
    //{
    //   AttackAnimations();//���� �ִϸ��̼�
    //}
    if (state == MonsterState::ATTACK)
    {
        if (anim->GetPlayTime() >= 0.9)
        {
            MoveAnimations();
            state = MonsterState::MOVE;
        }
    }

    if (state == MonsterState::DEAD)
    {
       
        DeadAnimations();

        if (anim->GetPlayTime() >= 0.9)
        {
           //5�ʸ� ��� ���ֱ� �Ҹ� ���¸� �����?

            dieTimer += DELTA;

            if (dieTimer >= 5.0f)
            {
                //����
            }
        }
    }

	
}

void Monster::SetRandomPosition()
{
    int minDistance = 1;
    int maxDistance = 5;


    //float distance = minDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxDistance - minDistance)));//min~max���� ������ �Ÿ�
    float distance = minDistance + RANDOM->Float(0, maxDistance - minDistance);
    /*float angle = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.0f))*/;//0~360���� ���� ����
    float angle = RANDOM->Float(0, 360);
    // ������ �������� ��ȯ
    float radianAngle = angle * PI / 180.0f;

    // ������ ��ġ ���� (�÷��̾� ��������)
    float offsetX = distance * 5 * cos(radianAngle);
    float offsetZ = distance * 5 * sin(radianAngle);

    this->SetWorldPosX(GM->player->GetWorldPos().x + offsetX);
    this->SetWorldPosZ(GM->player->GetWorldPos().z + offsetZ);
}