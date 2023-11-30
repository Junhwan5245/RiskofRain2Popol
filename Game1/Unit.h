#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);
	int hp;				// ü��					// Get�Լ��� ����
	float attack;		// ���ݷ�				// Get�Լ��� ����
	float moveSpeed;
	Unit();
	virtual ~Unit();

protected:
	/*Unit();
	virtual ~Unit();*/
	Vector3 dir;


	/** ���� ����*/
		// �̵� �ӵ�
	int lv;				// ���� (�÷��̾� : ����ġ��, ���� : �ð�����?)
	int maxHp;			// �ִ� ü��
	int exp;			// ����ġ (�÷��̾� : ���� óġ�� ��� �Ǵ� exp, ���� : ������ �÷��̾�� �ְ� �Ǵ� exp)
	int gold;			// ���� ���
	int luna;			// ���� �糪


	int defend;			// ��



	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

