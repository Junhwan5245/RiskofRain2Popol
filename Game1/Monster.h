#pragma once

enum class MonsterType
{
	BEETLE,
	LEMURIAN,
	GOLEM,
	BOSS
};
enum class MonsterState 
{
	IDLE,//move���� ����
	MOVE,
	ATTACK,
	DEAD,
};

// ���̵� �����ؼ� �ϳ� �߰��ؾ��ҵ�

class Monster : public Unit
{
public:
	static Monster* Create(string name, MonsterType monType);//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�
	static Monster* Create(Monster* src, MonsterType monType);
	void   Update();
	void   Render(shared_ptr<Shader> pShader = nullptr);
	void    WolrdUpdate();
	MonsterState state;
	MonsterType  monType;
	float stateChangeTime=0.0f;
	float stateChangeInterval=5.0f;
	int maxHp = 100;
	int Hp=100;
	Vector3 PlayerDir;//�Ѿ˹߻縦 ���� �÷��̾� ������
	vector<Vector3> way;
	Vector3 last;
	float dieTimer;
	
	void Stare();
	
	
protected:
	
	virtual void IdleAnimations()=0;
	virtual void AttackAnimations() = 0;
	virtual void MoveAnimations() = 0;
	virtual void DeadAnimations() = 0;

	virtual void    MonFSM();
	void	SetRandomPosition();
	//void	Stare();
	MonsterState     GetState() { return state; }
	Monster();
	virtual ~Monster();
	int range=0;
};

