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
    ui->RenderHierarchy();
    ImGui::End();


    Camera::main->Update();
    ui->Update();
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
    ui->Render();
}

void PlayerSelectScene::ResizeScreen()
{
}
