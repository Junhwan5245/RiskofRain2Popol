#pragma once
class InGameUI
{
public:
	static InGameUI* Create(string name = "InGameUI");

private:

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


public:
	InGameUI();
	~InGameUI();

	void Init();
	void Update();
	void Render();
	void ResizeScreen();
};

