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
    temp->hp = 100;     // ���͸����� ü������ ����

    temp->SetFirstPos();
    temp->IdleAnimations();
    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;
    temp->dieTimer = 0.0f;
   

    return temp;
}

void Monster::Update()
{
    ImGui::Text("animIdx : %d", anim->nextAnimator.animIdx);
    ImGui::Text("animPlaytime : %.2f", anim->GetPlayTime());

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
    this->rotation.y = stareDir;
}

void Monster::MonFSM()
{
    Vector3 playerVec = Vector3(GM->player->GetWorldPos().x,0, GM->player->GetWorldPos().z);
    Vector3 monVec = Vector3(this->GetWorldPos().x,0, this->GetWorldPos().z);
    //���� FSM
   
    
    if (hp > 0)
    {
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
                Vector3 temp = way.back() - GetWorldPos();
                temp.Normalize();
                MoveWorldPos(temp * moveSpeed * DELTA);

                float distanceThreshold = 0.1f;

                if ((way.back() - GetWorldPos()).Length() < distanceThreshold)
                {
                    way.pop_back();
                }
            }



            if ((monVec - playerVec).Length() < this->range)
            {
                isHit = false;
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
            if (anim->GetPlayTime() >= 0.98)
            {
                MoveAnimations();
                state = MonsterState::MOVE;  // ������ �κ�
            }
        }
    }


    else 
    { 
        state = MonsterState::DEAD;
        static int count = 0;

        // ���Ͱ� �׾������� ��ġ���� �������ֱ�
        //auto iter = GM->player->GetItemInven()->GetItemList().find("Infusion");
        //if (iter != GM->player->GetItemInven()->GetItemList().end())
        //{//�ִٸ� �� óġ�� maxHp + 1 (��ø +1) �ִ� 100(��ø +100)
        //    if (count < 100 * iter->second)
        //    {
        //        GM->player->maxHp += 1;
        //        count++;
        //    }
        //}
    }
    
    if (state == MonsterState::DEAD)
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

void Monster::SetFirstPos()
{
    this->SetWorldPosX(RANDOM->Int(-30,30));
    this->SetWorldPosZ(RANDOM->Int(-30,30));
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