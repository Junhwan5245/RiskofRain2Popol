#pragma once
class Lemurian : public Monster
{
public:
	static Lemurian* Create(string name = "Lemurian");//다른 곳에서 생성자로 접근 불가능하게 하기 위해서

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM() override;
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	void	MoveAnimations() override;
	void	DeadAnimations() override;
	Vector3 last;
	float bulletCreateTime = 0.0f;

private:
	Lemurian();
	virtual ~Lemurian();
};

