#pragma once
class GameManager : public Singleton<GameManager>
{

public:
	/*class Player* pl;*/
	vector<class Monster*> monsterPool;
	
	
	

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};


