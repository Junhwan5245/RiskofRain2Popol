#pragma once
class Boss : public Monster
{
public:
	static Boss* Create(string name = "Boss");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM();
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	void	MoveAnimations() override;
	void	DeadAnimations() override;

private:
	Boss();
	virtual ~Boss();


};