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
	MonsterState state;
	
protected:

	
	void    WolrdUpdate();
	void    Find();
	MonsterState     GetState() { return state; }
	 Monster();
	 virtual ~Monster();
	
	
	
	MonsterType  monType;
	

	

};

