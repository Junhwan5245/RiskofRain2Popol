#pragma once

enum class MonsterType
{
	BEETLE,
	LEMURIAN
};
enum class MonsterState 
{
	IDLE,//move���� ����
	ATTACK
};

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
	int maxHp = 100;
	int Hp=100;
	
	void Stare();
	
	
protected:
	
	
	virtual void IdleAnimations()=0;
	virtual void AttackAnimations() = 0;
	void    MonFSM();
	MonsterState     GetState() { return state; }
	Monster();
	virtual ~Monster();
	int range=0;
	

};

