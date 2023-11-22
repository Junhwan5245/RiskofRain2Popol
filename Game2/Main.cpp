#include "stdafx.h"
#include "Main.h"


Main::Main()
{
	cam1 = Camera::Create();
	cam1->LoadFile("Cam.xml");

	player = Actor::Create("Player");
	player->LoadFile("Player2.xml");

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
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();


	
	item1 = new Item(1);
	item2 = new Item(2);
	item3 = new Item(3);
	item4 = new Item(4);
	item5 = new Item(5);
	item6 = new Item(6);
	item7 = new Item(7);

	itemNormal = new Item_Normal("NormalItem");
	itemRare = new Item_Rare("RareItem");

	itemNormal->add(item1);
	itemNormal->add(item2);
	itemNormal->add(item3);
	itemNormal->add(item4);

	itemRare->add(item5);
	itemRare->add(item6);
	itemRare->add(item7);


	itemBox->add(itemNormal);
}

void Main::Release()
{
}

void Main::Update()
{
	ImGui::Text("isClick : %d", (int)isClick);

	ImGui::Begin("Hierarchy");
	expBox->RenderHierarchy();
	player->RenderHierarchy();
	exp->RenderHierarchy();
	ImGui::End();

	cam1->ControlMainCam();


	player->MoveWorldPos(dir * 2 * DELTA);

	if(INPUT->KeyPress('W'))
	{
		dir += player->GetForward();
	}
	if (INPUT->KeyPress('S'))
	{
		dir += -player->GetForward();
	}
	if (INPUT->KeyPress('A'))
	{
		dir += -player->GetRight();
	}
	if (INPUT->KeyPress('D'))
	{
		dir += player->GetRight();
	}
	dir.Normalize();

	if (not isClick)
	{
		if (INPUT->KeyDown('W'))
		{
			player->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		if (INPUT->KeyDown('S'))
		{
			player->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		if (INPUT->KeyDown('A'))
		{
			player->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		if (INPUT->KeyDown('D'))
		{
			player->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		player->Find("RootNode")->rotation.y = atan2f(-dir.z, dir.x) + HALFPI;
	}
	else
	{
		if (INPUT->KeyDown('W'))
			player->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		if (INPUT->KeyDown('S'))
			player->anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
		if (INPUT->KeyDown('A'))
			player->anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
		if (INPUT->KeyDown('D'))
			player->anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
		player->Find("RootNode")->rotation.y = player->rotation.y;
	}
	

	


	if (INPUT->KeyPress(VK_LBUTTON))
	{
		isClick = true;
	}
	else
	{
		if (TIMER->GetTick(clickTime, 4.0f))
		{
			isClick = false;
		}
	}

	Camera::main->Update();
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
	player->Update();
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
	player->Render();
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
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
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