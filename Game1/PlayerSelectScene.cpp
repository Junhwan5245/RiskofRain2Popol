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
    ui->RenderHierarchy();
    ImGui::End();


    Camera::main->Update();
    bg->Update();
    ui->Update();
    playerSelectBox->Update();
    optionSelectBox->Update();
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
    ui->Render();
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
