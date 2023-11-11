#pragma once
class Croco : public Monster
{
public:
	static Croco* Create(string name = "Croco");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    Find(class Player* player);
	
private:
	Croco();
	virtual ~Croco();

	
};

