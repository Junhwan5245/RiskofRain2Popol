#include "stdafx.h"
#include "Main.h"


Main::Main()
{
	cam1 = Camera::Create();
	cam1->LoadFile("Cam.xml");

	itemListUpperBox = UI::Create();
	itemListUpperBox->LoadFile("UI_InGame_ItemListUpperBox.xml");

	resourceBox = UI::Create();
	resourceBox->LoadFile("UI_InGame_ResourceBox.xml");

	stageBax = UI::Create();
	stageBax->LoadFile("UI_InGame_StageBox.xml");

	tab_Image = UI::Create();
	tab_Image->LoadFile("UI_InGame_Tab_Image.xml");
	tab_Font = UI::Create();
	tab_Font->LoadFile("UI_InGame_Tab_Font.xml");

	ctrl_Image = UI::Create();
	ctrl_Image->LoadFile("UI_InGame_Ctrl_Image.xml");
	ctrl_Font = UI::Create();
	ctrl_Font->LoadFile("UI_InGame_Ctrl_Font.xml");

	m1_Image = UI::Create();
	m1_Image->LoadFile("UI_InGame_M1_Image.xml");
	m1_Font = UI::Create();
	m1_Font->LoadFile("UI_InGame_M1_Font.xml");


	m2_Image = UI::Create();
	m2_Image->LoadFile("UI_InGame_M2_Image.xml");
	m2_Font = UI::Create();
	m2_Font->LoadFile("UI_InGame_M2_Font.xml");

	shift_Image = UI::Create();
	shift_Image->LoadFile("UI_InGame_Shift_Image.xml");
	shift_Font = UI::Create();
	shift_Font->LoadFile("UI_InGame_Shift_Font.xml");

	r_Image = UI::Create();
	r_Image->LoadFile("UI_InGame_R_Image.xml");
	r_Font = UI::Create();
	r_Font->LoadFile("UI_InGame_R_Font.xml");

	q_Image = UI::Create();
	q_Image->LoadFile("UI_InGame_Q_Image.xml");
	q_Font = UI::Create();
	q_Font->LoadFile("UI_InGame_Q_Font.xml");

	hPBox = UI::Create();
	hPBox->LoadFile("UI_InGame_PlayerHpBar_Image.xml");
	hp = UI::Create();
	hp->LoadFile("UI_InGame_PlayerHp_Image.xml");


	expBox = UI::Create();
	expBox->LoadFile("UI_InGame_PlayerExpBar_Image.xml");
	exp = UI::Create();
	exp->LoadFile("UI_InGame_PlayerExp_Image.xml");

	level = UI::Create();


	//투명 이미지출력
}

Main::~Main()
{
	
}
void Main::Init()
{
	
	Camera::main = cam1;
	cam1->viewport.x = 0.0f;
	cam1->viewport.y = 0.0f;
	cam1->viewport.width = App.GetWidth();
	cam1->viewport.height = App.GetHeight();
	cam1->width = App.GetWidth();
	cam1->height = App.GetHeight();


}

void Main::Release()
{
}

void Main::Update()

{
	ImGui::Begin("Hierarchy");
	expBox->RenderHierarchy();
	exp->RenderHierarchy();
	ImGui::End();

	cam1->ControlMainCam();


	cam1->Update();
	itemListUpperBox->Update();
	resourceBox->Update();
	stageBax->Update();

	tab_Image->Update();
	tab_Font->Update();
	ctrl_Image->Update();
	ctrl_Font->Update();
	m1_Image->Update();
	m1_Font->Update();
	m2_Image->Update();
	m2_Font->Update();
	shift_Image->Update();
	shift_Font->Update();
	r_Image->Update();
	r_Font->Update();
	q_Image->Update();
	q_Font->Update();

	hPBox->Update();
	hp->Update();
	expBox->Update();
	exp->Update();
}

void Main::LateUpdate()
{
	

}
void Main::PreRender()
{
}

void Main::Render()
{
	cam1->Set();
	LIGHT->Set();
	itemListUpperBox->Render();
	resourceBox->Render();
	stageBax->Render();

	tab_Image->Render();
	tab_Font->Render();
	ctrl_Image->Render();
	ctrl_Font->Render();
	m1_Image->Render();
	m1_Font->Render();
	m2_Image->Render();
	m2_Font->Render();
	shift_Image->Render();
	shift_Font->Render();
	r_Image->Render();
	r_Font->Render();
	q_Image->Render();
	q_Font->Render();

	hPBox->Render();
	hp->Render();
	expBox->Render();
	exp->Render();
}

void Main::ResizeScreen()
{
	cam1->viewport.x = 0.0f;
	cam1->viewport.y = 0.0f;
	cam1->viewport.width = App.GetWidth();
	cam1->viewport.height = App.GetHeight();
	cam1->width = App.GetWidth();
	cam1->height = App.GetHeight();
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