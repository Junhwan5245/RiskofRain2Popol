#include "framework.h"
#include "../Game1/Bullet.h"
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
		(*it)->Fire((*it)->fireDir, (*it)->power, Vector3());
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
