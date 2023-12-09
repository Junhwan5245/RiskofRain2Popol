#include "stdafx.h"
#include "StartScene.h"
#include "Scene1.h"

extern int     loadCount;

StartScene::StartScene()
{
    cam1 = Camera::Create();

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

    // idSelect = UI::Create("idSelect");
    //id = UI::Create("id");
    //newID = UI::Create("newId");


    loadCount++;
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
    Camera::main = cam1;

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    ((UI*)playerSelect)->mouseDown = [&]
    {
        //cout << "playerSelect 클릭" << endl;
        SCENE->ChangeScene("PlayerSelect");
        //SCENE->ChangeScene("SC1");
    };
    ((UI*)option)->mouseDown = [&]
    {
        cout << "option 클릭" << endl;
    };
    ((UI*)exit)->mouseDown = [&]
    {
        //cout << "exit 클릭" << endl;
        PostQuitMessage(0);
    };
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    ImGui::Begin("Hierarchy");
    //idSelect->RenderHierarchy();
    //id->RenderHierarchy();
    //newID->RenderHierarchy();
    ImGui::End();



    Camera::main->Update();
    bg->Update();
    logo->Update();
    playerSelect->Update();
    option->Update();
    exit->Update();
    //idSelect->Update();
    //id->Update();
    //newID->Update();
}

void StartScene::LateUpdate()
{
}

void StartScene::PreRender()
{
}

void StartScene::Render()
{
    cam1->Set();
    LIGHT->Set();
    bg->Render();
    logo->Render();
    playerSelect->Render();
    option->Render();
    exit->Render();


    //idSelect->Render();
    //id->Render();
    //newID->Render();
}

void StartScene::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
}
