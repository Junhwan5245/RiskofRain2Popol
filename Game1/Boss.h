#pragma once
enum class BossState
{
	IDLE,//move까지 포함
	MOVE,
	ATTACK,
	ATTACK2,
	DEAD,
};


class Boss : public Monster
{
public:
	static Boss* Create(string name = "Boss");//다른 곳에서 생성자로 접근 불가능하게 하기 위해서

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    MonFSM() override;
	void	IdleAnimations() override;
	void	AttackAnimations() override;
	void	MoveAnimations() override;
	void	DeadAnimations() override;
	void	Attack2Animations();
	BossState bState;
	float	attackTimer;
	float	bulletTimer1;
	float	bulletTimer2;

private:
	Boss();
	virtual ~Boss();


};