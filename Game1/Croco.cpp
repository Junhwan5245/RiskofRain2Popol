#include "stdafx.h"
#include "Unit.h"
#include "Monster.h"
#include "Croco.h"

Croco* Croco::Create(string name)
{
	Croco* croco = new Croco();
	croco->LoadFile("")
}

void Croco::Update()
{
}

void Croco::Render(shared_ptr<Shader> pShader)
{
}

void Croco::Move(Vector3 Target)
{
}

void Croco::WolrdUpdate()
{
}

void Croco::Find(Player* player)
{
}

Croco::Croco()
{
}

Croco::~Croco()
{
}
