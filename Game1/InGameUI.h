#pragma once
class InGameUI
{
public:
	static InGameUI* Create(string name = "InGameUI");

private:

	/** 인게임 UI */
	UI* itemListUpperBox;			// 상단 아이템 목록 보는 박스
	UI* resourceBox;				// 좌상단 골드및 루나코인 있는 박스
	UI* stageBax;					// 우상단 스테이지 및 시간 난이도 있는 박스
	UI* goalBox;					// 목표 박스

	UI* hPBox;						// HP 뒤 박스
	UI* hp;							// HP
	UI* expBox;						// 경험치 표시 박시
	UI* exp;
	UI* level;						// 플레이어 레벨


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

