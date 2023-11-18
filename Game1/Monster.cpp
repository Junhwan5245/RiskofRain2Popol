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

    default:
        return temp;
        break;
    }

    temp->SetRandomPosition();
    temp->IdleAnimations();
    temp->Hp = 100;
    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;

   

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

    default:
        return temp;
        break;
    }

    temp->SetRandomPosition();
    temp->IdleAnimations();
    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;

   
    return temp;
}

void Monster::Update()
{
    ImGui::Text("animIdx : %d", anim->nextAnimator.animIdx);

    Stare();

    MonFSM();

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

void Monster::MonFSM()
{
    Vector3 playerVec = Vector3(GM->player->GetWorldPos().x,0, GM->player->GetWorldPos().z);
    Vector3 monVec = Vector3(this->GetWorldPos().x,0, this->GetWorldPos().z);
    //상태 FSM
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
        }
    }

    if (state == MonsterState::MOVE)
    {

        if ((monVec - playerVec).Length() < this->range)
        {
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
        if (anim->GetPlayTime() >= 0.9)
        {
            MoveAnimations();
            state = MonsterState::MOVE;
        }
    }
	
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

void Monster::Stare()
{
    Vector3 tempDir = GM->player->GetWorldPos() - this->GetWorldPos();
    tempDir.Normalize();
    float stareDir = atan2f(tempDir.x, tempDir.z);
    this->rotation.y = stareDir + PI;

}




