#pragma once
class Lemurian : public Monster
{
public:
	static Lemurian* Create(string name = "Lemurian");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

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

