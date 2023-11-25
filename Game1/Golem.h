#pragma once
class Golem : public Monster
{
public:
	static Golem* Create(string name = "Golem");//다른 곳에서 생성자로 접근 불가능하게 하기 위해서

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM();
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	void	MoveAnimations() override;
	void	DeadAnimations() override;
	Vector3 tempLazerDir;
	class GolemLazer* lazer;
	bool oneTime = false;

private:
	Golem();
	virtual ~Golem();


};
