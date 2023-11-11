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
	
	
protected:

	
	void    WolrdUpdate();
	void    Find(class Player* player);
	MonsterState     GetState() { return state; }
	 Monster();
	 virtual ~Monster();
	
	
	MonsterState state;
	MonsterType  monType;
	

	

};

