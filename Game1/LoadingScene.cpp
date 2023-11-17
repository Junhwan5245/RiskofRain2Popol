#include "stdafx.h"
#include "LoadingScene.h"
#include "StartScene.h"
#include "PlayerSelectScene.h"
#include "Scene1.h"

wstring loadObejct;
int     loadCount = 0;

void CreateScene1()
{
    SCENE->AddScene("StartScene", new StartScene);
    SCENE->AddScene("PlayerSelect", new PlayerSelectScene);
    SCENE->AddScene("SC1", new Scene1);
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

    bono = UI::Create();
    bono->LoadFile("UI.xml");

    t1 = new thread(CreateScene1);
}

void LoadingScene::Release()
{
    t1->join();
    delete t1;
}

void LoadingScene::Update()
{
    Camera::main->ControlMainCam();
    Camera::main->Update();

    ImGui::Begin("Hierarchy");
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    bono->RenderHierarchy();
    ImGui::End();
    grid->Update();
    cam1->Update();
    bono->Update();

    //lodingPersent += 500 * DELTA;
    loadingPersent = min(min(17 * loadCount, 99), loadingPersent += 0.025f);
    ImGui::Text("loadCount : %d", loadCount);

    //if (loadCount == 1)
    //{
    //    lodingPersent = min(lodingPersent, 19);
    //}
    //else if (loadCount == 2)
    //{
    //    //lodingPersent += DELTA;
    //    lodingPersent = min(lodingPersent, 49);
    //}
    //else if (loadCount == 3)
    //{
    //    //lodingPersent += DELTA;
    //    lodingPersent = min(lodingPersent, 74);
    //}
    //else if (loadCount == 4)
    //{
    //    //lodingPersent += DELTA;
    //    lodingPersent = min(lodingPersent, 99);
    //}
    //else 
    if (loadCount == 7)
    {
        loadingPersent = 100;
        Render();
        //Sleep(1000);
        for (int i = 0; i < 1000; i++)
        {

        }
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
    DWRITE->RenderText(persent, RECT{0,0,1000,300}, 50, L"¹ÙÅÁÃ¼", Color(1, 0, 0, 1));
    cam1->Set();
    LIGHT->Set();
    grid->Render();
    bono->Render();
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
