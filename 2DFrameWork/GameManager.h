#pragma once
class GameManager : public Singleton<GameManager>
{

public:
	/*class Player* pl;*/
	vector<class Monster*> monsterPool;
	class Player* player;
	vector<class Bullet*> bulletPool;
	class Terrain* map;

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};


