#pragma once
class Main : public Scene
{

private:
	Camera* cam1;

	Actor* player;

	/** 인게임 UI */
	UI* upper;

	UI* leftBottom;
	UI* rightBottom;




	wstring wplayerHp;
	wstring whpSlash;
	wstring wplayerMaxHp;
	wstring wlv;
	wstring wplayerLv;

	wstring wstage;
	wstring wmonsterLv;
	wstring wtimer_tsecond;
	wstring wtimer_second;
	wstring wtimer_minute;

	wstring wcoolTime_M2;
	wstring wcoolTime_LShift;
	wstring wcoolTime_R;

	// 임시
	int playerlv = 1;
	int playerhp = 120;
	int playermaxhp = 120;
	float playerattack = 12;

	int playerexp = 0;
	int playerMaxexp = 150;

	bool isGoalClear = false;

	float coolTime_M2 = 0;
	float coolTime_LShift = 0;
	float coolTime_R = 0;

	RECT rect;
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

	void SetStageLevel(int stageLv);
	void RenderFont();

	void move();
};
