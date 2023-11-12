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
    Vector3 playerVec = Vector3(GM->player->GetWorldPos().x, 0, GM->player->GetWorldPos().z);
    Vector3 monVec = Vector3(this->GetWorldPos().x, 0, this->GetWorldPos().z);
    float lenght = (monVec - playerVec).Length();

    ImGui::Text("lenght : %.2f", lenght);

    if (state == MonsterState::IDLE)
    {
        if (lenght < 10)
        {
            anim->ChangeAnimation(AnimationState::LOOP, 6, 0.1f);
            state = MonsterState::ATTACK;
        }
    }

    if (state == MonsterState::ATTACK)
    {
        if (lenght >= 10)
        {
            anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
            state = MonsterState::IDLE;
        }
    }

	
    Unit::Update();
}
 
void Monster::Render(shared_ptr<Shader> pShader)
{
    Unit::Render(pShader);
}

void Monster::WolrdUpdate()
{
}

void Monster::Find()
{
    Vector3 playerVec = Vector3(GM->player->GetWorldPos().x,0, GM->player->GetWorldPos().z);
    Vector3 monVec = Vector3(this->GetWorldPos().x,0, this->GetWorldPos().z);

    

    if ((monVec - playerVec).Length() < 50)
    {
        anim->ChangeAnimation(AnimationState::LOOP, 6, 0.1f);
        state = MonsterState::ATTACK;
    }
    else
    {
        anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
        state = MonsterState::IDLE;
    }
	
}




