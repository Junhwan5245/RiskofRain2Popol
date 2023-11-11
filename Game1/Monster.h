#pragma once

enum class MonsterType
{
	BEETLE,
	LEMURIAN
};
enum class MonsterState 
{
	IDLE,//move까지 포함
	ATTACK
};

class Monster : public Unit
{
public:
	static Monster* Create(string name, MonsterType monType);//다른 곳에서 생성자로 접근 불가능하게 하기 위해서
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

