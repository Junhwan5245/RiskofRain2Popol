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

    temp->maxHp = 100;  // 몬스터마다의 체력으로 변경
    temp->Hp = 100;     // 몬스터마다의 체력으로 변경

    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;

    temp->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);

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

    temp->state = MonsterState::IDLE;
    temp->type = ObType::Actor;

    temp->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
    return temp;
}

void Monster::Update()
{
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

    if (state == MonsterState::IDLE)
    {
        if ((monVec - playerVec).Length() < this->range)
        {
            AttackAnimations();
            state = MonsterState::ATTACK;
        }
    }

    if (state == MonsterState::ATTACK)
    {
        if ((monVec - playerVec).Length() >= this->range)
        {
            IdleAnimations();
            state = MonsterState::IDLE;
        }
    }
	
}




