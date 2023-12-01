#include "stdafx.h"

EscapeShip* EscapeShip::Create(string name)
{
	EscapeShip* temp = new EscapeShip();
    temp->LoadFile("EscapeShip.xml");
	return temp;
}

EscapeShip::EscapeShip()
{
}

EscapeShip::~EscapeShip()
{
}

void EscapeShip::Update()
{
    Actor::Update();
}

void EscapeShip::Render(shared_ptr<Shader> pShader)
{
    Actor::Render();
}

void EscapeShip::SetPos()
{
	float randX = RANDOM->Float(-50.0f, 50.0f);
	float randZ = RANDOM->Float(-50.0f, 50.0f);
    
    Vector3 pos = Vector3(randX, 0, randZ);
    //Vector3 pos = Vector3(0, 0, 0);

    Ray escapeRay;
    escapeRay.position = pos + Vector3(0, 10, 0);
    escapeRay.direction = Vector3(0, -1, 0);

    Vector3 hit;
    if (Utility::RayIntersectMap(escapeRay, GM->map, hit))//맵과 몬스터 레이 이용해 플레이어 y값 잡기
    {
        pos.y = hit.y;
    }


    SetWorldPos(pos);

    anim->ChangeAnimation(AnimationState::ONCE_LAST, 0, 0.1f);
}
