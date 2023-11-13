#include "stdafx.h"
#include "StartScene.h"
#include "Scene1.h"

void StartScene::Init()
{
    cam1 = Camera::Create();
    Camera::main = cam1;

    //ui = Actor::Create();

    bg = UI::Create();
    bg->LoadFile("UI_StartScene_BackGround.xml");

    logo = UI::Create();
    logo->LoadFile("UI_StartScene_Logo.xml");
    
    playerSelect = UI::Create();
    playerSelect->LoadFile("UI_StartScene_PlayerSelect.xml");
    
    option = UI::Create();
    option->LoadFile("UI_StartScene_Option.xml");
    
    exit = UI::Create();
    exit->LoadFile("UI_StartScene_Exit.xml");
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    ImGui::Begin("Hierarchy");
    //ui->RenderHierarchy();
    bg->RenderHierarchy();
    logo->RenderHierarchy();
    playerSelect->RenderHierarchy();
    option->RenderHierarchy();
    exit->RenderHierarchy();
    ImGui::End();

    Camera::main->Update();
    bg->Update();
    logo->Update();
    playerSelect->Update();
    option->Update();
    exit->Update();
    //ui->Update();
}

void StartScene::LateUpdate()
{
}

void StartScene::PreRender()
{
}

void StartScene::Render()
{
    //DWRITE->RenderText(loadObejct, RECT{ 0,0,1000,300 }, 50, L"¹ÙÅÁÃ¼", Color(1, 0, 0, 1));
    cam1->Set();
    LIGHT->Set();
    bg->Render();
    logo->Render();
    playerSelect->Render();
    option->Render();
    exit->Render();

    //ui->Render();
}

void StartScene::ResizeScreen()
{
}
