#pragma once
class GameManager : public Singleton<GameManager>
{

public:
	/*class Player* pl;*/
	class InGameUI* ui;
	vector<class Item*> items;//������ ��Ƴ��� ����
	vector<class Monster*> monsterPool;//���� ��Ƴ��� ����
	class Player* player;//�÷��̾�
	vector<class Bullet*> bulletPool;//�Ѿ� ��� ����
	vector<class Feature*> featurePool;//������ ��� ����
	vector<class Pop*> particlePool;
	class Terrain* map; 

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
	
};


