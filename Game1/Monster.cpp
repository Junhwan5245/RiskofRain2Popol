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

    return temp;
}
	/*temp->type = (MonsterType)RANDOM->Int(0, 1);*/


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

    return temp;
}

void Monster::Update()
{
    Unit::Update();
	//if (state == MonsterState::IDLE)
	//{
	//	//Find(플레이어);	
	//}
	
}
 
void Monster::Render(shared_ptr<Shader> pShader)
{
    Unit::Render(pShader);
}

void Monster::WolrdUpdate()
{
}

void Monster::Find(class Player* p)
{
    
	//플레이어 거리와 몬스터 거리 가까워지면 공격 상태나누기
}




