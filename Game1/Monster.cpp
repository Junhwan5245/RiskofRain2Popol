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

    temp->maxHp = 100;  // 몬스터마다의 체력으로 변경
    temp->hp = 100;     // 몬스터마다의 체력으로 변경

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
    //상태 FSM
   
    
    if (hp > 0)
    {
        if (state == MonsterState::IDLE)
        {
            /*stateChangeTime += DELTA;*/


            //if (stateChangeTime > stateChangeInterval)
            //{
            //    MoveAnimations();//move애니메이션 넣기
            //    state = MonsterState::MOVE;
            //}
            if (TIMER->GetTick(stateChangeTime, 5.0f))
            {
                MoveAnimations();//move애니메이션 넣기
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


        //공격 FSM
        //if (monAttState == MonsterAttackState::IDLE)
        //{
        //   AttackAnimations();//공격 애니메이션
        //}
        if (state == MonsterState::ATTACK)
        {
            if (anim->GetPlayTime() >= 0.98)
            {
                MoveAnimations();
                state = MonsterState::MOVE;  // 수정된 부분
            }
        }
    }


    else 
    { 
        state = MonsterState::DEAD;
        static int count = 0;

        // 몬스터가 죽었을때의 위치에서 적용해주기
        //auto iter = GM->player->GetItemInven()->GetItemList().find("Infusion");
        //if (iter != GM->player->GetItemInven()->GetItemList().end())
        //{//있다면 적 처치당 maxHp + 1 (중첩 +1) 최대 100(중첩 +100)
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


    //float distance = minDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxDistance - minDistance)));//min~max까지 랜덤한 거리
    float distance = minDistance + RANDOM->Float(0, maxDistance - minDistance);
    /*float angle = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 360.0f))*/;//0~360까지 랜덤 각도
    float angle = RANDOM->Float(0, 360);
    // 각도를 라디안으로 변환
    float radianAngle = angle * PI / 180.0f;

    // 몬스터의 위치 설정 (플레이어 기준으로)
    float offsetX = distance * 5 * cos(radianAngle);
    float offsetZ = distance * 5 * sin(radianAngle);

    this->SetWorldPosX(GM->player->GetWorldPos().x + offsetX);
    this->SetWorldPosZ(GM->player->GetWorldPos().z + offsetZ);
}