#include "stdafx.h"

Feature::Feature()
{
	feature = Actor::Create();
}

Feature::~Feature()
{
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



