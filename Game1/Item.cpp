#include "stdafx.h"

Item::Item()
{
	item = Actor::Create();
}

Item::~Item()
{
}

void Item::Update()
{
	item->Update();
}

void Item::Render()
{
	item->Render();
}

void Item::Operate()
{
}

void Item::Interaction()
{
}
