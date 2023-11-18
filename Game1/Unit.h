#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);


protected:
	Unit();
	virtual ~Unit();
	Vector3 dir;


	/** 공통 스텟*/
	float moveSpeed;	// 이동 속도

	int maxHp;			// 최대 체력
	int Hp;				// 체력
	int defend;			// 방어막

	float attack;		// 공격력



	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

