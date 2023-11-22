#pragma once
class Main : public Scene
{

private:
	Camera* cam1;

	Actor* player;
	Vector3 dir;

	bool isClick;
	float	clickTime;


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


	Item* item1;
	Item* item2;
	Item* item3;
	Item* item4;
	Item* item5;
	Item* item6;
	Item* item7;

	Item_Normal* itemNormal;
	Item_Rare* itemRare;
	ItemBox* itemBox;



public:
	void ReadMtl(string file);
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;


	void move();
};
