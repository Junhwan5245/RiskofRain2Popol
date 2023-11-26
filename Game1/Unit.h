#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);
	int Hp;				// ü��
	float moveSpeed;
	Unit();
	virtual ~Unit();

protected:
	/*Unit();
	virtual ~Unit();*/
	Vector3 dir;


	/** ���� ����*/
		// �̵� �ӵ�

	int maxHp;			// �ִ� ü��
	int defend;			// ��

	float attack;		// ���ݷ�



	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

