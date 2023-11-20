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
	
	for (auto it = bulletPool.begin(); it != bulletPool.end(); it++)//총알 업데이트
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
	);//총알 삭제 조건(isCollsion=true)->총알이 플레이어나 몬스터 collider에 충돌 or 맵에 충돌

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
