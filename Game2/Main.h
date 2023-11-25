#pragma once
class Main : public Scene
{

private:
	Camera* cam1;

	Actor* player;
	Vector3 dir;

	bool isClick;
	float	clickTime;


	/** �ΰ��� UI */
	UI* itemListUpperBox;			// ��� ������ ��� ���� �ڽ�
	UI* resourceBox;				// �»�� ���� �糪���� �ִ� �ڽ�
	UI* stageBax;					// ���� �������� �� �ð� ���̵� �ִ� �ڽ�
	UI* goalBox;					// ��ǥ �ڽ�

	UI* hPBox;						// HP �� �ڽ�
	UI* hp;							// HP
	UI* expBox;						// ����ġ ǥ�� �ڽ�
	UI* exp;						
	UI* level;						// �÷��̾� ����


	UI* tab_Image;
	UI* tab_Font;

	UI* ctrl_Image;
	UI* ctrl_Font;

	UI* m1_Image;
	UI* m1_Font;

	UI* m2_Image;
	UI* m2_Font;

	UI* shift_Image;
	UI* shift_Font;

	UI* r_Image;
	UI* r_Font;

	UI* q_Image;
	UI* q_Font;


	wstring playerHp;
	wstring hpSlash;
	wstring playerMaxHp;
	wstring lv;
	wstring playerLv;

	int playerhp = 100;
	int playermaxhp = 100;

	RECT rect;
public:
	void ReadMtl(string file);
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void RenderFont();

	void move();
};
