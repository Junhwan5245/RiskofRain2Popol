#pragma once
class Beetle : public Monster
{
public:
	static Beetle* Create(string name = "Beetle");//�ٸ� ������ �����ڷ� ���� �Ұ����ϰ� �ϱ� ���ؼ�

	void	Update() override;
	void	Render(shared_ptr<Shader> pShader = nullptr) override;

	void    Move(Vector3 Target);
	void    WolrdUpdate();
	void    Find(class Player* player);

private:
	Beetle();
	virtual ~Beetle();


};