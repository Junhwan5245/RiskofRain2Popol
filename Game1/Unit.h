#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);
	int Hp;				// ü��
	float moveSpeed;

protected:
	Unit();
	virtual ~Unit();
	Vector3 dir;


	/** ���� ����*/
		// �̵� �ӵ�
	int lv;				// ���� (�÷��̾� : ����ġ��, ���� : �ð�����?)
	int maxHp;			// �ִ� ü��
	int exp;			// ����ġ (�÷��̾� : ���� óġ�� ��� �Ǵ� exp, ���� : ������ �÷��̾�� �ְ� �Ǵ� exp)



	float attack;		// ���ݷ�
	int defend;			// ��



	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

