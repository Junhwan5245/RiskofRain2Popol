#include "stdafx.h"
#include <sstream>
#include <iomanip>

InGameUI* InGameUI::Create(string name)
{
	InGameUI* temp = new InGameUI();

	return temp;
}

InGameUI::InGameUI()
{
	upper = UI::Create();
	upper->LoadFile("UI_InGame_Upper.xml");
	leftBottom = UI::Create();
	leftBottom->LoadFile("UI_InGame_LeftBottom.xml");
	rightBottom = UI::Create();
	rightBottom->LoadFile("UI_InGame_RightBottom.xml");
}

InGameUI::~InGameUI()
{
}

void InGameUI::Init()
{
	leftBottom->Find("LeftBottom_Exp")->scale.x = 0;
}

void InGameUI::Update()
{
	Vector3 mousePos = Utility::MouseToNDC();



	upper->Update();
	leftBottom->Update();
	rightBottom->Update();
}

void InGameUI::Render()
{
	upper->Render();
	leftBottom->Render();
	rightBottom->Render();

	RenderFont();
}

void InGameUI::ResizeScreen()
{
}

void InGameUI::RenderFont()
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

		wplayerLv = to_wstring(GM->player->GetLv());
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


		wplayerHp = to_wstring((int)GM->player->hp);
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() - 45;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerHp, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wplayerMaxHp = to_wstring((int)GM->player->GetMaxHp());
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



		if ((4 - (int)GM->player->GetM2CoolTime()) <= 3.9)
		{
			wcoolTime_M2 = to_wstring(4 - (int)GM->player->GetM2CoolTime());
			rect.left = (rightBottom->Find("Skill_M2")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_M2")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_M2, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}


		if (GM->player->GetLShiftCoolTime() > 0)
		{
			wcoolTime_LShift = to_wstring((int)GM->player->GetLShiftCoolTime());
			rect.left = (rightBottom->Find("Skill_LShift")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_LShift")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_LShift, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}

		if ((10 - (int)GM->player->GetRCoolTime()) <= 9.9)
		{
			wcoolTime_R = to_wstring(10 - (int)GM->player->GetRCoolTime());
			rect.left = (rightBottom->Find("Skill_R")->GetWorldPos().x + 1) * App.GetHalfWidth() - 20;
			rect.top = (1 - rightBottom->Find("Skill_R")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_R, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}
	}
}
