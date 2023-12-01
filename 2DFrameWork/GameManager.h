#pragma once
class GameManager : public Singleton<GameManager>
{

public:
	/*class Player* pl;*/
	vector<class Item*> items;//������ ��Ƴ��� ����
	vector<class Monster*> monsterPool;//���� ��Ƴ��� ����
	class Player* player;//�÷��̾�
	vector<class Bullet*> bulletPool;//�Ѿ� ��� ����
	vector<class Feature*> featurePool;//������ ��� ����
	class Terrain* map; 

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
	
};


