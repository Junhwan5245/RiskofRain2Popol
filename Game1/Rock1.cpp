#include "stdafx.h"

Rock1::Rock1()
{
	feature->LoadFile("Rock.xml");
	
	SetPosition();
}

Rock1::~Rock1()
{
	
}

void Rock1::Update()
{
	Feature::Update();
}

void Rock1::Render()
{
	Feature::Render();
}
