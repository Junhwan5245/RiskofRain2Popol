#include "framework.h"
#include "../Game1/Unit.h"
#include "../Game1/Bullet.h"
#include "../Game1/Monster.h"
#include "GameManager.h"

GameManager::~GameManager()
{
	
}

void GameManager::Init()
{
}

void GameManager::Release()
{
}

void GameManager::Update()
{
	for (auto it = bulletPool.begin(); it != bulletPool.end(); it++)//�Ѿ� ������Ʈ
	{
		(*it)->Update();
	}
}

void GameManager::LateUpdate()
{
	
	bulletPool.erase(
		std::remove_if(
			bulletPool.begin(), bulletPool.end(),
			[&] (class Bullet* bullet)
			{
				if (bullet->isCollsion)
				{
					delete bullet;
					return true;
				}
			}
		), bulletPool.end()
	);//�Ѿ� ���� ����(isCollsion=true)->�Ѿ��� �÷��̾ ���� collider�� �浹 or �ʿ� �浹

	monsterPool.erase(
		std::remove_if(
			monsterPool.begin(), monsterPool.end(),
			[&](class Monster* monster)
			{
				if (monster->isDead)
				{
					delete monster;
					return true;
				}
		
			}
		), monsterPool.end()
				);


	particlePool.erase(
		std::remove_if(
			particlePool.begin(), particlePool.end(),
			[&](class Pop* particle)
			{
				if (particle->isErasing)
				{
					delete particle;
					return true;
				}

			}
		), particlePool.end()
				);

}

void GameManager::Render()
{

	for (auto it = bulletPool.begin(); it != bulletPool.end(); it++)
	{
		(*it)->Render();
	}
}

void GameManager::ResizeScreen()
{
}


