#pragma once

enum class MonsterType
{
	BEETLE,
	LEMURIAN,
	GOLEM,
	BOSS,
};
enum class MonsterState 
{
	IDLE,//move까지 포함
	MOVE,
	ATTACK,
	DEAD,
};

// 난이도 관련해서 하나 추가해야할듯

class Monster : public Unit
{
public:
	static Monster* Create(string name, MonsterType monType);//다른 곳에서 생성자로 접근 불가능하게 하기 위해서
	void   Update();
	void   Render(shared_ptr<Shader> pShader = nullptr);
	void    WolrdUpdate();
	MonsterState state;
	MonsterType  monsterType;
	float stateChangeTime=0.0f;
	float stateChangeInterval=5.0f;
	Vector3 PlayerDir;//총알발사를 위한 플레이어 고정값
	vector<Vector3> way;
	Vector3 last;
	bool	isDead = false;
	float dieTimer;
	bool	isHpZero = false;
	bool	isHit = false;//딱정벌레 충돌을 위한 bool

	void Stare();
	Monster();
	virtual ~Monster();
	
protected:
	
	virtual void IdleAnimations()=0;
	virtual void AttackAnimations() = 0;
	virtual void MoveAnimations() = 0;
	virtual void DeadAnimations() = 0;

	virtual void    MonFSM();
	void	SetRandomPosition();
	void	SetFirstPos();

	//void	Stare();
	MonsterState     GetState() { return state; }
	
	
	int range=0;
};

