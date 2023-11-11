#pragma once
class Lemurian : public Monster
{
public:
	static Lemurian* Create(string name = "Lemurian");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    Find(class Player* player);

private:
	Lemurian();
	virtual ~Lemurian();
};

