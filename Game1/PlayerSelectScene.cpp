#include "stdafx.h"
#include "PlayerSelectScene.h"

void PlayerSelectScene::Init()
{
	cam1 = Camera::Create();
	Camera::main = cam1;

    bg = UI::Create();
    bg->LoadFile("UI_StartScene_BackGround.xml");

    playerSelectBox = UI::Create();
    playerSelectBox->LoadFile("UI_SelectScene_playerSelectBox.xml");

    optionSelectBox = UI::Create();
    optionSelectBox->LoadFile("UI_SelectScene_optionBox.xml");

    playerExplain = UI::Create();
    playerExplain->LoadFile("UI_SelectScene_Font.xml");
    playerExplain->visible = false;


    for (int i = 0; i < 4; i++)
    {
        playerSkill[i] = UI::Create();
    }




	ui = UI::Create();
}

void PlayerSelectScene::Release()
{
}

void PlayerSelectScene::Update()
{
    ImGui::Begin("Hierarchy");
    //ui->RenderHierarchy();
    bg->RenderHierarchy();
    playerSelectBox->RenderHierarchy();
    optionSelectBox->RenderHierarchy();
    playerExplain->RenderHierarchy();

    for (int i = 0; i < 4; i++)
    {
        playerSkill[i]->RenderHierarchy();
    }

    ImGui::End();


    Camera::main->Update();
    bg->Update();
    playerSelectBox->Update();
    optionSelectBox->Update();
    playerExplain->Update();
    for (int i = 0; i < 4; i++)
    {
        playerSkill[i]->Update();
    }
}

void PlayerSelectScene::LateUpdate()
{
}

void PlayerSelectScene::PreRender()
{
}

void PlayerSelectScene::Render()
{
    cam1->Set();
    LIGHT->Set();
    bg->Render();
    playerSelectBox->Render();
    optionSelectBox->Render();
    playerExplain->Render();
    for (int i = 0; i < 4; i++)
    {
        playerSkill[i]->Render();
    }
}

void PlayerSelectScene::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
