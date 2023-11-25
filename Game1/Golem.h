#pragma once
class Golem : public Monster
{
public:
	static Golem* Create(string name = "Golem");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

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
