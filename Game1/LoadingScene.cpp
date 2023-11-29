#include "stdafx.h"
#include "LoadingScene.h"
#include "StartScene.h"
#include "PlayerSelectScene.h"
#include "Scene1.h"

wstring loadObejct;
int     loadCount = 0;

void CreateScene1()
{
    SCENE->AddScene("SC1", new Scene1);
    SCENE->AddScene("PlayerSelect", new PlayerSelectScene);
    SCENE->AddScene("StartScene", new StartScene);
}

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init()
{
    grid = Grid::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");
    Camera::main = cam1;

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    bg = UI::Create();
    bg->LoadFile("UI_LoadingScene_BackGround.xml");

    t1 = new thread(CreateScene1);
}

void LoadingScene::Release()
{
    //t1->join();
    //delete t1;
}

void LoadingScene::Update()
{
    Camera::main->ControlMainCam();
    Camera::main->Update();

    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    bg->RenderHierarchy();
    ImGui::End();
    grid->Update();
    cam1->Update();
    bg->Update();


    loadingPersent = min(min(17 * loadCount, 99), loadingPersent += 0.025f);
    ImGui::Text("loadCount : %d", loadCount);

    if (loadCount == 7)
    {
        loadingPersent = 100;
        //Render();
        //Sleep(1000);
        SCENE->ChangeScene("StartScene");
    }


}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
    wstring persent = to_wstring((int)loadingPersent) + L"%";
    RECT rect;
    rect.left = App.GetWidth() - 100;
    rect.top = App.GetHeight() - 100;
    rect.right = App.GetWidth();
    rect.bottom = App.GetHeight();

    DWRITE->RenderText(persent, rect, 50, L"¹ÙÅÁÃ¼", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
    cam1->Set();
    LIGHT->Set();
    grid->Render();
    bg->Render();
}

void LoadingScene::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
}
