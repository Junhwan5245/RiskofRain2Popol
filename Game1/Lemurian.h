#pragma once
class Lemurian : public Monster
{
public:
	static Lemurian* Create(string name = "Lemurian");//다른 곳에서 생성자로 접근 불가능하게 하기 위해서

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM();
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	vector <class LemurianBullet*> bullet;

private:
	Lemurian();
	virtual ~Lemurian();
};

