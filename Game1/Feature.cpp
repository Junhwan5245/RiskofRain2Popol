#include "stdafx.h"

Feature::Feature()
{
	feature = Actor::Create();
}

Feature::~Feature()
{
}

void Feature::Init()
{
	Vector3 hit;
	Ray featureTop;
	featureTop.position = feature->GetWorldPos() + Vector3(0, 1000, 0);
	featureTop.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(featureTop, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
	{
		feature->SetWorldPosY(hit.y);
	}

}

void Feature::Update()
{
	feature->Update();
}

void Feature::Render()
{
	feature->Render();
}

void Feature::Set()
{

}



