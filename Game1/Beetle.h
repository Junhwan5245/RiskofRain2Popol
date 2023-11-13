#pragma once
class Beetle : public Monster
{
public:
	static Beetle* Create(string name = "Beetle");//다른 곳에서 생성자로 접근 불가능하게 하기 위해서

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM();
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	

private:
	Beetle();
	virtual ~Beetle();


};