#include "stdafx.h"
#include "Main.h"


Main::Main()
{
	cam1 = Camera::Create();
	cam1->LoadFile("Cam.xml");
	//투명 이미지출력


	upper = UI::Create();
	upper->LoadFile("UI_InGame_Upper.xml");
	leftBottom = UI::Create();
	leftBottom->LoadFile("UI_InGame_LeftBottom.xml");
	rightBottom = UI::Create();
	rightBottom->LoadFile("UI_InGame_RightBottom.xml");
}

Main::~Main()
{

}
void Main::Init()
{
	Camera::main = cam1;
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();

	leftBottom->Find("LeftBottom_Exp")->scale.x = 0;

	SetStageLevel(2);
}

void Main::Release()
{
}

void Main::Update()
{
	ImGui::Text("WorldTime : %.2f", TIMER->GetWorldTime());
	ImGui::Text("playerattack : %.2f", playerattack);
	             

	ImGui::Begin("Hierarchy");
	upper->RenderHierarchy();
	leftBottom->RenderHierarchy();
	rightBottom->RenderHierarchy();
	ImGui::End();

	

	if (playerexp >= playerMaxexp)
	{
		playerexp = 0;
		leftBottom->Find("LeftBottom_Exp")->scale.x = 0;
		playerlv++;
		playermaxhp = playermaxhp + (33 * (playerlv - 1));
		playerhp = playermaxhp;	// 레벨업시 최대채력의 10%회복
		playerMaxexp = playerMaxexp * (1 + 0.1f * (playerlv - 1));
		playerattack = playerattack + 2.4f;
	}



	if (INPUT->KeyDown('K')) // 체력이 까일때마다 hpUI의 스케일값 조정하기 
	{
		playerhp -= 13; // 13 : 몬스터의 attack값

		float scale = leftBottom->Find("LeftBottom_PlayerHpBar")->scale.x * (float)playerhp / (float)playermaxhp;
		leftBottom->Find("LeftBottom_PlayerHp")->scale.x = scale;
	}

	if (INPUT->KeyDown('J')) // 몬스터를 잡고나서 얻는 경험치로 expUI스케일값 조정하기
	{
		playerexp += 11; // 11 : 몬스터가 가지고 있을 Exp값

		float scale = leftBottom->Find("LeftBottom_ExpBarscale")->scale.x * playerexp / (float)playerMaxexp;
		leftBottom->Find("LeftBottom_Exp")->scale.x = scale;
		isGoalClear = !isGoalClear;
	}

	if (isGoalClear)
	{
		upper->Find("UpperRightBottom_GoalClear")->visible = true;
		upper->Find("UpperRightBottom_GoalList")->visible = false;
	}
	else
	{
		upper->Find("UpperRightBottom_GoalClear")->visible = false;
		upper->Find("UpperRightBottom_GoalList")->visible = true;
	}

	if (INPUT->KeyDown(VK_RBUTTON))
	{
		coolTime_M2 = 4;
	}
	if (INPUT->KeyDown(VK_LSHIFT))
	{
		coolTime_LShift = 5;
	}
	if (INPUT->KeyDown('R'))
	{
		coolTime_R = 10;
	}

	coolTime_M2 = max(coolTime_M2, 0);
	coolTime_LShift = max(coolTime_LShift, 0);
	coolTime_R = max(coolTime_R, 0);

	coolTime_M2 -= DELTA;
	coolTime_LShift -= DELTA;
	coolTime_R -= DELTA;

	

	cam1->ControlMainCam();

	Camera::main->Update();
	upper->Update();
	leftBottom->Update();
	rightBottom->Update();
}

void Main::LateUpdate()
{


}
void Main::PreRender()
{
}

void Main::Render()
{
	Camera::main->Set();
	LIGHT->Set();

	upper->Render();
	leftBottom->Render();
	rightBottom->Render();

	RenderFont();
}

void Main::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}

void Main::SetStageLevel(int stageLv)
{

	switch (stageLv) // 1 : esay,  2 : normal  3 : hard
	{
	case 1:
		upper->Find("UpperRight_LevelImage_easy")->visible = true;
		upper->Find("UpperRight_LevelImage_normal")->visible = false;
		upper->Find("UpperRight_LevelImage_hard")->visible = false;
		break;
	case 2:
		upper->Find("UpperRight_LevelImage_easy")->visible = false;
		upper->Find("UpperRight_LevelImage_normal")->visible = true;
		upper->Find("UpperRight_LevelImage_hard")->visible = false;
		break;
	case 3:
		upper->Find("UpperRight_LevelImage_easy")->visible = false;
		upper->Find("UpperRight_LevelImage_normal")->visible = false;
		upper->Find("UpperRight_LevelImage_hard")->visible = true;
		break;
	default:
		break;
	}
}

void Main::RenderFont()
{
	// LeftBottom Font (Player Lv, Hp..)
	{
		Vector3 playerHpBarPos = leftBottom->Find("LeftBottom_PlayerHpFont")->GetWorldPos(); // 플레이어체력바 Pos
		Vector3 playerHpBarScale = leftBottom->Find("LeftBottom_PlayerHpFont")->scale; // 플레이어체력바 Scale

		Vector3 playerExpBarPos = leftBottom->Find("LeftBottom_LvFont")->GetWorldPos();
		Vector3 playerExpBarScale = leftBottom->Find("LeftBottom_LvFont")->scale;

		wlv = L"Lv : ";
		rect.left = (playerExpBarPos.x + 1) * App.GetHalfWidth() - 20;
		rect.top = (1 - playerExpBarPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wlv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wplayerLv = to_wstring(playerlv);
		rect.left = (playerExpBarPos.x + 1) * App.GetHalfWidth() + 10;
		rect.top = (1 - playerExpBarPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerLv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		whpSlash = L" / ";
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() - 10;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(whpSlash, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


		wplayerHp = to_wstring(playerhp);
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() - 45;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerHp, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wplayerMaxHp = to_wstring(playermaxhp);
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() + 10;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerMaxHp, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
	}

	// RightTop Font (Stage, Monster Lv, Timer)
	{
		Vector3 stagePos = upper->Find("UpperRight_StageFont")->GetWorldPos(); // 플레이어체력바 Pos
		Vector3 stageScale = upper->Find("UpperRight_StageFont")->scale; // 플레이어체력바 Scale

		Vector3 timerPos = upper->Find("UpperRight_TimeBox")->GetWorldPos();
		Vector3 timerScale = upper->Find("UpperRight_TimeBox")->scale;

		wstage = L"Stage 1";
		rect.left = (stagePos.x + 1) * App.GetHalfWidth() - 25;
		rect.top = (1 - stagePos.y) * App.GetHalfHeight() - 20;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wstage, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wmonsterLv = L"Level 1";
		rect.left = (stagePos.x + 1) * App.GetHalfWidth() - 25;
		rect.top = (1 - stagePos.y) * App.GetHalfHeight();
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wmonsterLv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


		float floatVal = TIMER->GetWorldTime();
		float fractionalPart;	// 소수점부분 (t초)
		float second;			// 정수부분 (초)

		// 소수점 이하 부분 추출
		fractionalPart = modf(floatVal, &second);

		// 소수점 이하 부분을 문자열로 변환
		wstringstream wss;
		wss << std::fixed << std::setprecision(2) << fractionalPart;
		wtimer_tsecond = wss.str();
		// 소수점 이하 부분에서 0. 부분 제거
		size_t pos = wtimer_tsecond.find(L"0");
		if (pos != wstring::npos) {
			wtimer_tsecond.erase(pos, 2);
		}

		rect.left = (timerPos.x + 1) * App.GetHalfWidth() + 30;
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_tsecond, rect, 10, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		int second_print = (int)second % 60;

		if (second_print < 10)
			wtimer_second = L"0" + to_wstring((int)second_print);
		else
			wtimer_second = to_wstring((int)second_print);
		rect.left = (timerPos.x + 1) * App.GetHalfWidth();
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_second, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		int minute = (int)second / 60;
		if (minute < 10)
			wtimer_minute = L"0" + to_wstring((int)minute) + L" :";
		else
			wtimer_minute = to_wstring((int)minute) + L" :";
		rect.left = (timerPos.x + 1) * App.GetHalfWidth() - 40;
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_minute, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);



		if (coolTime_M2 > 0)
		{
			wcoolTime_M2 = to_wstring((int)coolTime_M2);
			rect.left = (rightBottom->Find("Skill_M2")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_M2")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_M2, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}

		
		if (coolTime_LShift > 0)
		{
			wcoolTime_LShift = to_wstring((int)coolTime_LShift);
			rect.left = (rightBottom->Find("Skill_LShift")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_LShift")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_LShift, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}

		if (coolTime_R > 0)
		{
			wcoolTime_R = to_wstring((int)coolTime_R);
			rect.left = (rightBottom->Find("Skill_R")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_R")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_R, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}
	}
}

void Main::move()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();

	int wParam = (int)WIN->Run(main);


	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}