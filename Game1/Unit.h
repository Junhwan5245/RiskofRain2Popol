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
	float moveSpeed;

	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

