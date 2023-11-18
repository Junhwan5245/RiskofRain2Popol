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

	ctrl_Image = UI::Create();
	ctrl_Image->LoadFile("UI_InGame_Ctrl_Image.xml");


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
	ctrl_Image->RenderHierarchy();
	ImGui::End();

	cam1->ControlMainCam();


	cam1->Update();
	itemListUpperBox->Update();
	resourceBox->Update();
	stageBax->Update();

	tab_Image->Update();
	ctrl_Image->Update();
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
	ctrl_Image->Render();
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